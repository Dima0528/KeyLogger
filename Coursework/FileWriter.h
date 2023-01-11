#pragma once

#include <string>
#include <fstream>

class FileWriter
{
private:
	std::string filename;
public:
	FileWriter(std::string filename) : filename(filename) {}
public:
	void logTail(std::string text);
};

