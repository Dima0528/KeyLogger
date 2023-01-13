#pragma once
#include <fstream>
#include <string>

class FileReader
{
private:
	std::string filename;
public:
	FileReader(std::string filename) : filename(filename) {}
public:
	std::string readLines() {
		std::ifstream fin(filename);

		std::string lines = "";

		if (!fin.bad()) {

			std::string buff = "";
			while (getline(fin, buff)) {
				lines += buff + "\n";
			}
		}

		fin.close();

		return lines;
	}
};

