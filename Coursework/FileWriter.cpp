#include "FileWriter.h"

void FileWriter::logTail(std::string text)
{
	std::ofstream fout(filename, std::fstream::app);

	if (!fout.bad()) {
		fout << text;
	}

	fout.close();
}
