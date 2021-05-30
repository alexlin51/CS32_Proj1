#include "Table.h"
#include <iostream>
#include <functional>
#include <cassert>

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
	for (int i = 0; i != BUCKETS; i++) {
		if (m_dict[i].size() != 0) {
			cerr << m_dict[i].size() << endl;
		}
	}
	return 0;
}

int main() {
	vector<string> cols = {
		"customer", "product", "price", "location"
	};
	Table t("customer", cols);
	assert(t.good());
	assert(t.insert("Patel 12345 42.54 Westwood"));
	assert(t.insert("O'Reilly 34567     4.99 Westwood   "));
	assert(t.insert("   Hoang  12345 30.46 'Santa Monica' "));
	assert(t.insert("Patel\t67890\t142.75  \t \t\t  \tHollywood"));
	assert(!t.insert("Figueroa 54321 59.95"));
	vector<vector<string>> v;
	t.find("Patel", v);
	assert(v.size() == 2);
	vector<vector<string>> expected = {
		{ "Patel", "12345", "42.54", "Westwood" },
		{ "Patel", "67890", "142.75", "Hollywood" }
	};
	assert((v[0] == expected[0] && v[1] == expected[1]) ||
		(v[0] == expected[1] && v[1] == expected[0]));

	t.find("O'Reilly", v);
	assert(v.size() == 1);
	expected = {
		{ "O'Reilly", "34567", "4.99", "Westwood" }
	};
	assert(v[0] == expected[0]);

	t.find("Hoang", v);
	assert(v.size() == 1);
	expected = {
		{ "Hoang", "12345", "30.46", "Santa Monica" }
	};
	assert(v[0] == expected[0]);

	t.find("Figueroa", v);
	expected = {};
	assert(v.size() == 0 && expected.size() == 0);
	// t.select("", v);

	vector<string> cols2 = { "N", "Z" };
	Table t2("Z", cols2);
	assert(t2.good());
	assert(t2.insert("UCLA 90095"));
	assert(t2.insert("Caltech 91125"));
	vector<vector<string>> v2;
	t2.find("90095", v2);
	assert(v2.size() == 1);
	assert(v2[0][0] == "UCLA" && v2[0][1] == "90095");

	cerr << "All Tests Passed!" << endl;
}