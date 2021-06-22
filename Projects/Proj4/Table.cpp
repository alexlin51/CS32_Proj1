#include "Table.h"
#include <iostream>
#include <functional>
#include <cassert>
#include <cctype>

using namespace std;

// StringParser Class Method
bool StringParser::getNextField(std::string& fieldText)
{
	m_start = m_text.find_first_not_of(" \t\r\n", m_start);
	if (m_start == std::string::npos)
	{
		m_start = m_text.size();
		fieldText = "";
		return false;
	}
	if (m_text[m_start] != '\'')
	{
		size_t end = m_text.find_first_of(" \t\r\n", m_start + 1);
		fieldText = m_text.substr(m_start, end - m_start);
		m_start = end;
		return true;
	}
	fieldText = "";
	for (;;)
	{
		m_start++;
		size_t end = m_text.find('\'', m_start);
		fieldText += m_text.substr(m_start, end - m_start);
		m_start = (end != std::string::npos ? end + 1 : m_text.size());
		if (m_start == m_text.size() || m_text[m_start] != '\'')
			break;
		fieldText += '\'';
	}
	return true;
}

// Table Class Methods

Table::Table(std::string keyColumn, const std::vector<std::string>& columns)
{
	if (keyColumn == "") {
		m_good = false;
		return;
	}
	
	int includesKey = 0;

	m_colNum = columns.size();
	// Has to have at least 2 entries, one key and one data point.
	if (m_colNum <= 1) {
		m_good = false;
		return;
	}

	// We want to check the given inputs for duplicates or empty strings
	// also counts the number of times key appears in vector
	for (int i = 0; i != columns.size();i++) {
		if (columns[i] == "") {
			m_good = false;
			return;
		}
		if (columns[i] == keyColumn) {
			includesKey += 1;
			keyIdx = i;
		}
		for (int j = 0; j != columns.size();j++) {
			if (i != j) {
				if (columns[i] == columns[j]) {
					m_good = false;
					return;
				}
			}
		}
	}

	if (includesKey != 1) {
		m_good = false;
		return;
	}
	
	// All column names are valid, there is a valid key
	m_good = true;
	for (int i = 0; i != columns.size();i++) {
		m_colNames.push_back(columns[i]);
	}
	return;
}

Table::~Table()
{
}

bool Table::good() const
{
	return m_good;
}

bool Table::insert(const std::string& recordString)
{
	if (!good()) {
		return false;
	}

	StringParser input(recordString);
	string s;
	int count = 0;
	vector<string> tracker;

	while (input.getNextField(s)){
		tracker.push_back(s);
		count += 1;
	}

	if (tracker.size() != m_colNum) {
		return false;
	}

	unsigned int spot = hash<string>()(tracker[keyIdx]) % BUCKETS;

	m_dict[spot].push_back(tracker);

	/*
	cerr << "Input array is";
	for (int i = 0; i != tracker.size(); i++) {
		cerr << " " << tracker[i];
	}
	cerr << " at " << spot << " with key " << tracker[keyIdx] << " idx at " << keyIdx << endl;
	*/

	return true;
}

void Table::find(std::string key, std::vector<std::vector<std::string>>& records) const
{
	unsigned int spot = hash<string>()(key) % BUCKETS;
	//cerr << key << " lives at " << spot << endl;
	
	vector<vector<string>> v;

	for (auto it = m_dict[spot].begin(); it != m_dict[spot].end(); it++) {
		if ((*it)[keyIdx] == key) {
			vector<string> temp;
			for (int i = 0; i != (*it).size(); i++) {
				temp.push_back((*it)[i]);
			}
			v.push_back(temp);
		}
	}

	// cerr << "Size at " << spot << " is " << m_dict[spot].size() << endl;
	records = v;
}

int Table::select(std::string query, std::vector<std::vector<std::string>>& records) const
{
	if (!good()) {
		return false;
	}

	StringParser input(query);
	string s;
	int count = 0;
	vector<string> tracker;
	vector<vector<string>> output;
	string oper[13] = { "<","<=",">",">=","!=","==","=","LT","LE","GT","GE","NE","EQ" };

	while (input.getNextField(s)) {
		tracker.push_back(s);
		count += 1;
	}

	// Validations
	// Correct number of inputs
	if (tracker.size() != 3) {
		records = output;
		return -1;
	}
	// Checking Column Names
	bool name = false;
	int col = -1;
	for (int i = 0; i != m_colNames.size(); i++) {
		if (m_colNames[i] == tracker[0]) {
			name = true;
			col = i;
			break;
		}
	}
	if (!name) {
		records = output;
		return -1;
	}
	// checking comparison operator
	bool sign = false;
	bool num = false;
	for (auto& x : tracker[1]) {
		x = toupper(x);
	}
	for (int i = 0; i != sizeof(oper); i++) {
		if (oper[i] == tracker[1]) {
			sign = true;
			if (tracker[1] == "LT" || tracker[1] == "LE" || tracker[1] == "GT" || tracker[1] == "GE" || tracker[1] == "EQ" || tracker[1] == "NQ") {
				num = true;
			}
			if (tracker[1] == "=") {
				tracker[1] = "==";
			}
			break;
		}
	}
	if (!sign) {
		records = output;
		return -1;
	}
	// checking second parameter
	if (tracker[2] == "") {
		records = output;
		return -1;
	}
	if (num) {
		for (int i = 0; i != tracker[2].length(); i++) {
			if (!isdigit(tracker[2][i])) {
				if (tracker[2][i] != '.') {
					records = output;
					return -1;
				}
			}
		}
	}

	// Good Query String, now we query
	int badcount = 0;
	for (int i = 0; i != BUCKETS; i++) {
		if (m_dict[i].size() != 0) {
			for (auto it = m_dict[i].begin(); it != m_dict[i].end(); it++) {
				bool found = false;
				if (num) {
					bool cont = true;
					for (int i = 0; i != (*it)[col].length(); i++) {
						if (!isdigit((*it)[col][i])) {
							if ((*it)[col][i] != '.') {
								cont = false;
								badcount += 1;
								break;
							}
						}
					}

					if (cont) {
						if (tracker[1] == "LT" && stof((*it)[col]) < stof(tracker[2])) {
							found = true;
						}
						else if (tracker[1] == "LE" && stof((*it)[col]) <= stof(tracker[2])) {
							found = true;
						}
						else if (tracker[1] == "GT" && stof((*it)[col]) > stof(tracker[2])) {
							found = true;
						}
						else if (tracker[1] == "GE" && stof((*it)[col]) >= stof(tracker[2])) {
							found = true;
						}
						else if (tracker[1] == "NE" && stof((*it)[col]) != stof(tracker[2])) {
							found = true;
						}
						else if (tracker[1] == "EQ" && stof((*it)[col]) == stof(tracker[2])) {
							found = true;
						}
					}
				}
				else {
					if (tracker[1] == "<" && (*it)[col] < tracker[2]) {
						found = true;
					}
					else if (tracker[1] == "<=" && (*it)[col] <= tracker[2]) {
						found = true;
					}
					else if (tracker[1] == ">" && (*it)[col] > tracker[2]) {
						found = true;
					}
					else if (tracker[1] == ">=" && (*it)[col] >= tracker[2]) {
						found = true;
					}
					else if ((tracker[1] == "==" || tracker[1] == "=") && (*it)[col] == tracker[2]) {
						found = true;
					}
				}

				if (found) {
					vector<string> temp;
					for (int i = 0; i != (*it).size(); i++) {
						temp.push_back((*it)[i]);
					}
					output.push_back(temp);
				}
			}
		}
	}
	records = output;
	return badcount;
}