#ifndef TABLE
#define TABLE

#include <string>
#include <list>
#include <vector>

const int BUCKETS = 1000;

class Table
{
public:
	Table(std::string keyColumn, const std::vector<std::string>& columns);
	~Table();
	bool good() const;
	bool insert(const std::string& recordString);
	void find(std::string key, std::vector<std::vector<std::string>>& records) const;
	int select(std::string query, std::vector<std::vector<std::string>>& records) const;

	// We prevent a Table object from being copied or assigned by
	// making the copy constructor and assignment operator unavailable.
	Table(const Table&) = delete;
	Table& operator=(const Table&) = delete;
private:
	int keyIdx = 0;
	bool m_good;
	std::string m_key;
	std::list<std::vector<std::string>> m_dict[BUCKETS];
	std::vector<std::string> m_colNames;
	int m_colNum = 0;
};

class StringParser
{
public:
	StringParser(std::string text = "")
	{
		setString(text);
	}

	void setString(std::string text)
	{
		m_text = text;
		m_start = 0;
	}

	bool getNextField(std::string& field);

private:
	std::string m_text;
	size_t m_start;
};


#endif 

