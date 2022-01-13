#include <set>
#include <iostream>
#include <regex>
#include <sstream>
#include <fstream>
#include <tuple>
#include <filesystem>
#include <vector>
#include <memory>
#include "Properties.h"
//#include "../lib/WordsExercise.h"

using namespace std;

const int INVALID_PARAMETERS = 1000 + 1;

void showHelp(char* arg)
{
	std::cout << "Usage:" << arg << " fileName\n";
}

std::tuple<bool, std::string> parseArguments(int argc, char** argv)
{
	if (argc != 2)
	{
		showHelp(argv[0]);
		return std::make_tuple(false, "");
	}
	return std::make_tuple(true, argv[1]);
}

class Dialog
{
	PROPERTY(int, serial, setSerial )
	PROPERTY(std::string, time, setTime)
	//PROPERTY(std::vector<std::string>, lines, setLines)
	public:
	void addLine(const std::string& line)
	{
		lines_.emplace_back(line);
	}
	std::vector<std::string> lines()
	{
		return lines_;
	}
	private:
	std::vector<std::string> lines_;
};



std::shared_ptr<Dialog> parseDialog(const std::vector<std::string>& v)
{
	auto p = std::make_shared<Dialog>();
	p->setSerial(stoi(v[0]));
	p->setTime(v[1]);
	//for(size_t i = 2; i != v.size(); ++i)
	//	p->addLine(v[i]);
	return p;
}

std::vector<std::shared_ptr<Dialog>> parseFile(const string& stream)
{
	ifstream file(stream);
	string line;
	vector<string> temp;
	vector<shared_ptr<Dialog>> dialogs;
	while(std::getline(file, line))
	{
		if (line.size() == 0)
		{
			dialogs.emplace_back(parseDialog(temp));
			temp.clear();
		}
		else
			temp.emplace_back(line);
	}
	return dialogs;
}

vector<string> getLines(const vector<shared_ptr<Dialog>>& dialogs)
{
	vector<string> v;
	cout << "dialogs:" << dialogs.size() << endl;
	for(auto i : dialogs)
		cout << "size:" << i->lines().size() << endl;
		//copy(i->lines().begin(), i->lines().end(), back_inserter(v));
	return v;
}

std::vector<std::string> parseLine(const std::string& line)
{
	std::vector<std::string> v;
	std::string word;
	for(auto c : line)
	{
		cout << "char:" << c << endl;
		if ((c == ' ' || c == '\n' || c == '\r') && word.size() > 0)
		{
			v.emplace_back(word);
			word.clear();
		}
		else
			word.push_back(c);
	}
	return v;
}

std::set<string> getWords(const std::vector<std::string>& lines)
{
	cout << "lines:" << lines.size() << endl;
	std::set<string> s;
	for(auto i : lines)
	{
		auto v = parseLine(i);
		for(auto w : v)
			s.emplace(w);
	}
	return s;
}

int main(int argc, char** argv)
{
	bool succeeded = false;
	std::string fileName;
	std::tie(succeeded, fileName) = parseArguments(argc, argv);
	if (!succeeded)
		return -1;
	auto v = parseFile(fileName);
	auto lines = getLines(v);
	auto s = getWords(lines);
	cout << s.size() << endl;
	return 0;
}
