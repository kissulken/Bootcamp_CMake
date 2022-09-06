#pragma once
#include <string>

class Employee
{
	private:
		std::string Name;
		std::string date;
		int hours;
	public:
		Employee(std::string _Name, std::string _date, int _hours) : Name(_Name), date(_date), hours(_hours) {};
		std::string getName() const { return Name; };
		std::string getDate() const { return date; };
		int getHours() const { return hours; };
};