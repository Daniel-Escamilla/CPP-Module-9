/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:54:02 by descamil          #+#    #+#             */
/*   Updated: 2025/06/21 20:48:30 by daniel-esca      ###   ########.fr       */
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

std::string trim(std::string s)
{
    while (!s.empty() && std::isspace(s[0]))
        s.erase(0, 1);
    while (!s.empty() && std::isspace(s[s.size() - 1]))
        s.erase(s.size() - 1, 1);
    return s;
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
// if (value.second == "")
// 	throw std::logic_error(std::string("Bad input") + line);

void BitcoinExchange::fillDatabase(const std::string &file)
{
	std::string line;
	std::ifstream infile(file.c_str());

	if (infile.is_open())
		throw std::runtime_error("Inflie is open");
	try
	{
		while (getline(infile, line))
		{
			
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	
}
