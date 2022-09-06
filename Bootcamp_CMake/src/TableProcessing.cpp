#include "TableProcessing.h"


void TableParsing::run()
{
	tablesForming(inPath);
	tablesParsing();
	tablesWriting(outPath);
}


void TableParsing::findPosition(std::string& word, int column)
{
    for (int i = 0; i < tags.size(); i++)
    {
        if(word == tags[i])
            element.push_back(column);
    }
}

void TableParsing::string_parser(std::string& word)
{
    std::string temp = "";
    for (int i = 0; i < word.size(); ++i)
    {
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= '0' && word[i] <= '9') || word[i] == ' ')
        {
            temp += word[i];
        }
    }
    word = temp;
}

void TableParsing::needed_tables(std::string& line)
{
    std::string data;
    int column = 0;
    std::stringstream s(line);
    while (getline(s, data, ';'))
    {
        string_parser(data);
        findPosition(data, column);
        column++;
    }
}

void TableParsing::tablesForming(const std::string& path)
{
    std::fstream fin;
    fin.open(path, std::ios::in);
    int start_row = 0, column = 0;
    std::string data, line;
    while (getline(fin, line))
    {
        std::stringstream s(line);
        if (start_row != 0)
        {
            column = 0;
            while (getline(s, data, ';'))
            {
                string_parser(data);
                if (column == element[0])
                {
                    names.push_back(data);
                }
                if (column == element[1])
                {
                    dates.push_back(data);
                }
                if (column == element[2])
                {
                    hours.push_back(stoi(data));
                }
                column++;
            }
        }
        else
        {
            needed_tables(line);
            start_row++;
        }
    }
    fin.close();
}

std::string TableParsing::getMonth(int number)
{
    switch (number)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    default:
        return "Incorrect Month";
    }
}

void TableParsing::tablesParsing()
{
    while (names.size() > 0)
    {
        std::string current_name = names[0];
        std::string current_date = dates[0].substr(0, 6);
        int current_hours = 0;
        for (int i = 0; i < names.size(); i++)
        {
            if (current_name == names[i] && current_date == dates[i].substr(0, 6))
            {
                current_hours += hours[i];
                names.erase(names.begin() + i);
                dates.erase(dates.begin() + i);
                hours.erase(hours.begin() + i);
                i--;
            }
        }
        std::string month_segment = current_date.substr(4, 2);
        std::string year_segment = current_date.substr(0, 4);
        current_date = getMonth(stoi(month_segment)) + ' ' + year_segment;
        employees.push_back(std::make_unique<Employee>(current_name, current_date, current_hours));
    }
}

void TableParsing::tablesWriting(std::string &path)
{
    std::fstream f;
    f.open(path, std::ios::out);
    f << "Name" << ';' << "Month" << ';' << "Total Hours" << std::endl;
    for (int i = 0; i < employees.size(); i++)
    {
        f << employees[i]->getName() << ';' << employees[i]->getDate() << ';' << employees[i]->getHours() << std::endl;
    }
    f.close();
}