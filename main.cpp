#include "LexicalAnalyzer.cpp"

using namespace std;

int main(int argc, char **argv)
{
	// string str;
	LexicalAnalyzer *la = LexicalAnalyzer::getInstance();
	// while (cin >> str)
	// 	la->analyzeWord(str);

	string mypath = argv[1];
	// LexicalAnalyzer *la = LexicalAnalyzer::getInstance();
	la->run(mypath);
	la->outputResults();
	return 0;
}
