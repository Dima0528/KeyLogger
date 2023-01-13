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
	void write(std::string text);
};

