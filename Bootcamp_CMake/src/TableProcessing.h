#pragma once
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "Employee.h"

class TableParsing
{
	public:
		TableParsing(std::string _inPath, std::string _outPath) : inPath(_inPath), outPath(_outPath) {};
		void run();
	private:
		std::string outPath;
		std::string inPath;
		std::vector<int> element;
		std::vector<std::string> names;
		std::vector<std::string> dates;
		std::vector<std::string> tags = { "Name", "date", "logged hours " };
		std::vector<int> hours;
		std::vector<std::unique_ptr<Employee>> employees;
		std::string getMonth(int number);
		void findPosition(std::string& word, int column);
		void string_parser(std::string& word);
		void needed_tables(std::string& line);
		void tablesForming(const std::string& path);
		void tablesParsing();
		void tablesWriting(std::string &path);
};