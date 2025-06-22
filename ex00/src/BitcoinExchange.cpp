/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:54:02 by descamil          #+#    #+#             */
/*   Updated: 2025/06/22 21:31:28 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
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

std::string to_string(int value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void checkDate(std::string date)
{
	char number = 0;
	int year = 0;
	int month = 0;
	int day = 0;
	
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		throw std::logic_error(std::string("Incorret format, expected: YYYY-MM-DD") + date);
	for (size_t i = 0; i < 10; ++i)
	{
		number = date[i];
		if (i == 4 || i == 7)
				continue;
		if (!std::isdigit(static_cast<unsigned char>(number)))
			throw std::invalid_argument(std::string("Bad input -> ") + date);
		int digit = number - '0';
		if (i < 4)
			year = year * 10 + digit;
		else if (i >= 5 && i <= 6)
			month = month * 10 + digit;
		else if (i >= 8 && i <= 9)
			day = day * 10 + digit;
	}
	if (year < 1)
		throw std::out_of_range("Invalid year: " + to_string(year));
	if (month < 1 || month > 12)
		throw std::out_of_range("Invalid month: " + to_string(month));
	static const int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int maxDay = daysInMonth[month - 1];
	if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
		++maxDay;
	if (day < 1 || day > maxDay)
		throw std::out_of_range("Invalid day: " + std::to_string(day) + " for month " + std::to_string(month));
}



void BitcoinExchange::fillDatabase(const std::string &file)
{
	std::string line;
	std::ifstream infile(file.c_str());
	std::pair<std::string, std::string> splitLine;

	if (infile.is_open())
		throw std::runtime_error("Inflie is open");
	while (getline(infile, line))
	{
		try
		{
			splitLine = splitValues(line, ',');
			if (splitLine.second == "")
				throw std::logic_error(std::string("Bad input") + line);
			checkDate(splitLine.first);
			// checkValue(splitLine.second);
			_database.push_back(splitLine);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << '\n';
		}
	}
	
}
