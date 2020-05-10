#include "LexicalAnalyzer.h"

LexicalAnalyzer *LexicalAnalyzer::myInstance = NULL;

template <class T>
bool checkInSet(set<T> argset, T elem) // 模板工具函数，检查元素elem是否在set中
{
	if (argset.find(elem) != argset.end())
		return true;
	else
		return false;
}

LexicalAnalyzer::LexicalAnalyzer()
{
	const string letters_ = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	const string digit = "0123456789";
	const string decimalDigitsExceptZero = "123456789";
	const string octoDigitsExceptZero = "1234567";
	const string hexDigitsExceptZero = "abcdefABCDEF";
	const string delimiters = ",[]{}();";
	for (auto i : digit)
		digitSet.insert(i);
	for (auto i : letters_)
		letterSet.insert(i);
	for (auto i : keywords)
		keywordSet.insert(i);
	for (auto i : decimalDigitsExceptZero)
		decimalDigitSetExceptZero.insert(i);
	for (auto i : octoDigitsExceptZero)
		octoDigitSetExceptZero.insert(i);
	for (auto i : hexDigitsExceptZero)
		hexDigitSet.insert(i);
	for (auto i : delimiters)
		delimiterSet.insert(i);
}

LexicalAnalyzer *LexicalAnalyzer::getInstance()
{
	if (!myInstance)
		myInstance = new LexicalAnalyzer();
	return myInstance;
}

bool LexicalAnalyzer::isKeyword(const string &str)
{
	if (checkInSet(keywordSet, str))
		return true;
	else
		return false;
}

bool LexicalAnalyzer::isIdentifier(const string &str)
{
	int statusTable[3][3] = {
		{0, 0, 0},
		{0, 2, 0},
		{0, 2, 2}};
	int status = 1;
	for (auto i : str)
	{
		int inputStatus = 0;
		if (checkInSet(letterSet, i))
			inputStatus = 1;
		else if (checkInSet(digitSet, i))
			inputStatus = 2;
		status = statusTable[status][inputStatus];
	}
	if (status == 2)
		return true;
	else
		return false;
}

bool LexicalAnalyzer::isArithmeticOperator(const string &str)
{
	int statusTable[7][4] = {
		{0, 0, 0, 0},
		{0, 2, 3, 4},
		{0, 5, 0, 0},
		{0, 0, 6, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}};
	int status = 1;
	for (auto i : str)
	{
		int inputStatus = 0;
		if (i == '+')
			inputStatus = 1;
		else if (i == '-')
			inputStatus = 2;
		else if (i == '*' || i == '/' || i == '%' || i == '=')
			inputStatus = 3;
		status = statusTable[status][inputStatus];
	}
	if (status == 2 || status == 3 || status == 4 || status == 5 || status == 6)
		return true;
	else
		return false;
}

bool LexicalAnalyzer::isLogicalOperator(const string &str)
{
	if (str == "||" || str == "&&")
		return true;
	int statusTable[5][3] = {
		{0, 0, 0},
		{0, 2, 3},
		{0, 0, 4},
		{0, 0, 4},
		{0, 0, 0}};
	int status = 1;
	for (auto i : str)
	{
		int inputStatus = 0;
		if (i == '!' || i == '>' || i == '<')
			inputStatus = 1;
		else if (i == '=')
			inputStatus = 2;
		status = statusTable[status][inputStatus];
	}
	if (status == 2 || status == 4)
		return true;
	else
		return false;
}

bool LexicalAnalyzer::isOperator(const string &str)
{
	return isArithmeticOperator(str) || isLogicalOperator(str);
}

bool LexicalAnalyzer::isComment(const string &str)
{
	int statusTable[6][4] = {
		{0, 0, 0, 0},
		{0, 2, 0, 0},
		{0, 0, 3, 0},
		{0, 0, 4, 3},
		{0, 5, 4, 3},
		{0, 0, 0, 0}};
	int status = 1;
	for (auto i : str)
	{
		int inputStatus = 0;
		if (i == '/')
			inputStatus = 1;
		else if (i == '*')
			inputStatus = 2;
		else
			inputStatus = 3;
		status = statusTable[status][inputStatus];
	}
	if (status == 5)
		return true;
	else
		return false;
}

bool LexicalAnalyzer::isUnsigned(const string &str)
{
	int statusTable[8][5] = {
		{0, 0, 0, 0, 0},
		{0, 2, 0, 0, 0},
		{0, 2, 3, 5, 0},
		{0, 4, 0, 0, 0},
		{0, 4, 0, 5, 0},
		{0, 7, 0, 0, 6},
		{0, 7, 0, 0, 0},
		{0, 7, 0, 0, 0}};
	int status = 1;
	for (auto i : str)
	{
		int inputStatus = 0;
		if (checkInSet(digitSet, i))
			inputStatus = 1;
		else if (i == '.')
			inputStatus = 2;
		else if (i == 'E' | i == 'e')
			inputStatus = 3;
		else if (i == '+' | i == '-')
			inputStatus = 4;
		status = statusTable[status][inputStatus];
	}
	if (status == 2 || status == 4 || status == 7)
		return true;
	else
		return false;
}

bool LexicalAnalyzer::isIntenger(const string &str)
{
	int statusTable[7][6] = {
		{0, 0, 0, 0, 0, 0},
		{0, 3, 2, 0, 0, 0},
		{0, 2, 2, 0, 0, 0},
		{0, 0, 0, 4, 5, 0},
		{0, 0, 6, 0, 0, 6},
		{0, 5, 0, 0, 5, 0},
		{0, 6, 6, 0, 0, 6}};
	int status = 1;
	for (auto i : str)
	{
		int inputStatus = 0;
		if (i == '0')
			inputStatus = 1;
		else if (checkInSet(decimalDigitSetExceptZero, i))
			inputStatus = 2;
		else if (i == 'x')
			inputStatus = 3;
		else if (checkInSet(octoDigitSetExceptZero, i))
			inputStatus = 4;
		else if (checkInSet(hexDigitSet, i))
			inputStatus = 5;
		status = statusTable[status][inputStatus];
	}
	if (status == 2 || status == 3 || status == 5 || status == 6)
		return true;
	else
		return false;
}

bool LexicalAnalyzer::isConstant(const string &str)
{
	return isUnsigned(str);
}

bool LexicalAnalyzer::isDelimiter(const string &str)
{
	if (str.length() > 1)
		return false;
	else
		return checkInSet(delimiterSet, str[0]);
}

bool LexicalAnalyzer::isDelimiter(const char &ch)
{
	for (auto i : delimiterSet)
	{
		if (ch == i)
			return true;
	}
	return false;
}

/**
 * 功能：分析单词，返回类型
 * @param str 单词
 */
int LexicalAnalyzer::analyze(const string &str)
{
	if (str == "")
		return 0;
	if (isKeyword(str))
		return 1;
	else if (isIdentifier(str))
		return 2;
	else if (isOperator(str))
		return 3;
	else if (isDelimiter(str))
		return 4;
	else if (isConstant(str))
		return 5;
	else if (isComment(str))
		return 6;
	else
		return 0;
}

void LexicalAnalyzer::run(const string &path)
{
	string content = fileProcessWithSpaces(path);

	int index;
	string buffer;

	while (content.size() > 0)
	{
		bool flag = false;
		index = content.size() - 1;
		buffer = content;

		// 寻找可以被接受的字符串
		for (; analyze(buffer) == 0 && index > 0; index--)
			buffer.pop_back();

		if (index == 0 && analyze(buffer) == 0)
		{
			content.erase(0, 1);  // 如果没找到可以被接受的字符串，删除首个字符重新开始识别
			continue;
		}
		else
		{
			results.push_back(token(analyze(buffer), buffer));
			content.erase(0, index + 1);
		}
	}
}

/**
 * 功能：将文件读取并转换为没有空格的字符串
 * @param path 文件路径
 * @return 返回读取文件的字符串
*/
string LexicalAnalyzer::fileProcessWithoutSpaces(const string &path)
{
	string result = "";
	fstream myfile;
	myfile.open(path, ios::in);
	while (!myfile.eof())
	{
		char tmp;
		myfile >> tmp;
		if (tmp != ' ' && !myfile.eof())
			result += tmp;
	}
	myfile.close();
	return result;
}

string LexicalAnalyzer::fileProcessWithSpaces(const string &path)
{
	string result = "";
	fstream myfile;
	myfile.open(path, ios::in);
	myfile >> noskipws;
	while (!myfile.eof())
	{
		char tmp;
		myfile >> tmp;
		if (!myfile.eof() && tmp != '\r' && tmp != '\n')
			result += tmp;
	}
	myfile.close();
	return result;
}

void LexicalAnalyzer::outputResults()
{
	const string typeStrings[] = {
		"Error",
		"Keyword",
		"Identifier",
		"Operator",
		"Delimiter",
		"Constant",
		"Comment"};
	const string typeStringsCHN[] = {
		"错误",
		"关键字",
		"标识符",
		"操作符",
		"分隔符",
		"常量",
		"注释"};
	for (auto i : results)
	{
		const string res = "( " + typeStringsCHN[i.type] + " , \"" + i.content + "\" )";
		cout << res << endl;
	}
	return;
}

void LexicalAnalyzer::analyzeWord(const string &word)
{
	const string typeStringsCHN[] = {
		"错误",
		"关键字",
		"标识符",
		"操作符",
		"分隔符",
		"常量",
		"注释"};
	int i = analyze(word);
	const string res = "( " + typeStringsCHN[i] + " , \"" + word + "\" )";
	cout << res << endl;
	return;
}