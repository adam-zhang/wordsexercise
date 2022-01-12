#include <iostream>
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
	PROPERTY(std::string, lines, setLines)
};


std::stringstream readContent(const std::string& fileName)
{
	std::ifstream file(fileName);
	string stream;
	file >> stream;
	return std::stringstream(stream);
}

std::vector<std::shared_ptr<Dialog>> parseContent(const stringstream& stream)
{
	return std::vector<std::shared_ptr<Dialog>>();
}

std::vector<std::shared_ptr<Dialog>> parseFile(const std::string& fileName)
{
	auto content = readContent(fileName);
	cout << content << endl;
	return parseContent(content);
}

int main(int argc, char** argv)
{
	bool succeeded = false;
	std::string fileName;
	std::tie(succeeded, fileName) = parseArguments(argc, argv);
	if (!succeeded)
		return -1;
	return 0;
}
