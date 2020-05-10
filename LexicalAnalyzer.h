#ifndef LEXICALANALYZER
#define LEXICALANALYZER

#include <iostream>
#include <string>
#include <set>
#include <utility>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "keywords.cpp"

using namespace std;

struct token
{
	int type;
	string content;
	token(int t, string str)
	{
		type = t;
		content = str;

		// 提取注释
		if (t == 6)
			content = content.substr(2, content.size() - 4);
	}
};

class LexicalAnalyzer
{
private:
	set<char> letterSet;
	set<char> digitSet;
	set<char> decimalDigitSetExceptZero;
	set<char> octoDigitSetExceptZero;
	set<char> hexDigitSet;
	set<string> keywordSet;
	set<char> delimiterSet;

	vector<token> results;

	static LexicalAnalyzer *myInstance;

	LexicalAnalyzer();
	bool isKeyword(const string &str);
	bool isIdentifier(const string &str);
	bool isArithmeticOperator(const string &str);
	bool isLogicalOperator(const string &str);
	bool isOperator(const string &str);
	bool isComment(const string &str);
	bool isUnsigned(const string &str);
	bool isIntenger(const string &str);
	bool isConstant(const string &str);
	bool isDelimiter(const string &str);
	bool isDelimiter(const char &ch);
	int analyze(const string &str);

	string fileProcessWithoutSpaces(const string &path);
	string fileProcessWithSpaces(const string &path);
public:
	static LexicalAnalyzer *getInstance();
	void run(const string &path);
	void outputResults();

	void analyzeWord(const string &word);
};

#endif
