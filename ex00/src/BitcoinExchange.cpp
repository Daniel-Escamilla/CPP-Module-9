/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:54:02 by descamil          #+#    #+#             */
/*   Updated: 2025/06/23 14:08:05 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
	: _infile(copy._infile), _database(copy._database)
{
	
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this != &copy)
	{
		_infile = copy._infile;
		_database = copy._database;
	}
	return *this;
}

std::string trim(std::string str)
{
    while (!str.empty() && std::isspace(str[0]))
        str.erase(0, 1);
    while (!str.empty() && std::isspace(str[str.size() - 1]))
        str.erase(str.size() - 1, 1);
    return str;
}


std::pair<std::string, std::string> splitValues(std::string line, char delimiter)
{
	std::pair<std::string, std::string> value;
	std::string::size_type pos = line.find(delimiter);
	std::string::size_type posLast = line.rfind(delimiter);

	if (pos != std::string::npos && pos == posLast)
	{
		value.first = trim(line.substr(0, pos));
		value.second = trim(line.substr(pos + 1));
	}
	else
	{
		value.first = line;
		value.second = "";
	}
	return value;
}

double toDouble(const std::string& str)
{
    std::istringstream iss(str);
    double number;
    iss >> number;
    return number;
}

t_Date extractYMD(std::string date, int i, t_Date day)
{
	char number = 0;
	number = date[i];
	if (i == 4 || i == 7)
		return day;
	if (!std::isdigit(static_cast<unsigned char>(number)))
		throw std::invalid_argument(std::string("Bad input: ") + date);
	int digit = number - '0';
	if (i < 4)
		day.year = day.year * 10 + digit;
	else if (i >= 5 && i <= 6)
		day.month = day.month * 10 + digit;
	else if (i >= 8 && i <= 9)
		day.day = day.day * 10 + digit;
	return (day);
}

void checkDate(std::string date)
{
	t_Date day = {0, 0, 0};
	
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		throw std::logic_error(std::string("Incorret format, expected: YYYY-MM-DD -> ") + date);
	for (size_t i = 0; i < 10; ++i)
		day = extractYMD(date, i, day);
	if (day.year < 1)
		throw std::out_of_range(std::string("Bad input (year): ") + date);
	if (day.month < 1 || day.month > 12)
		throw std::out_of_range(std::string("Bad input (month): ") + date);
	static const int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int maxDay = daysInMonth[day.month - 1];
	if (day.month == 2 && (day.year % 4 == 0 && (day.year % 100 != 0 || day.year % 400 == 0)))
		++maxDay;
	if (day.day < 1 || day.day > maxDay)
		throw std::out_of_range(std::string("Bad input (day): ") + date);
}

void BitcoinExchange::checkValue(std::string value, map& target)
{
	for (std::size_t i = 0; i < value.size(); ++i)
	{
		if (!std::isdigit(static_cast<unsigned char>(value[i])) && value[i] != '.' && value[i] != '-')
			throw std::runtime_error(std::string("Not a number: ") + value);
	}
	std::istringstream floatStream(value);
	double d_number;
	floatStream >> d_number;
	if (floatStream.fail() || !floatStream.eof())
		throw std::logic_error(std::string("Not a number: ") + value);
	if (target == _database)
		return ;
	if (d_number > 1000)
		throw std::logic_error(std::string("Too large number: ") + value);
	if (d_number < 0)
		throw std::logic_error(std::string("Not a positive number: ") + value);
}

void BitcoinExchange::loadAndCompare(BitcoinExchange& btc, char *file)
{
	btc.fillDatabase(btc._database, "DataBase/data.csv", ',');
    btc.fillDatabase(btc._infile, file, '|');
}

std::string formatDouble(double number, int precision = 6)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(precision) << number;
	std::string str = oss.str();

	std::string::size_type dot = str.find('.');
	if (dot != std::string::npos)
	{
		std::string::size_type last = str.size() - 1;
		while (last > dot && str[last] == '0')
			--last;
		if (str[last] == '.') --last;
		str.erase(last + 1);
	}
	return str;
}

void BitcoinExchange::findValue(std::string day, std::string value)
{
	std::map <std::string, std::string>::iterator it = _database.lower_bound(day);
	double amount;

	if (it != _database.end() && it->first == day)
		amount = toDouble(it->second) * toDouble(value);
	else if (it != _database.begin())
	{
		it--;
		amount = toDouble(it->second) * toDouble(value);
	}
	else
		throw std::runtime_error(std::string("No valid date defore: ") + day);
	std::cout << day << " => " << value << " = " << formatDouble(amount) << std::endl;
}

void BitcoinExchange::fillDatabase(map& target, const std::string &file, char delimiter)
{
	std::string line;
	std::ifstream infile(file.c_str());
	std::pair<std::string, std::string> splitLine;

	if (!infile.is_open())
		throw std::runtime_error(std::string("Inflie is open: ") + file);
	while (getline(infile, line))
	{
		try
		{
			splitLine = splitValues(line, delimiter);
			if (splitLine.second == "")
				throw std::logic_error(std::string("Bad input: ") + line);
			checkDate(splitLine.first);
			checkValue(splitLine.second, target);
			if (target == _database)
				target.insert(splitLine);
			else
				findValue(splitLine.first, splitLine.second);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << '\n';
		}
	}
}
