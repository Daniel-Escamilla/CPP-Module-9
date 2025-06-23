/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:53 by descamil          #+#    #+#             */
/*   Updated: 2025/06/23 14:08:30 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <ctime>
# include <cmath>
# include <limits>
# include <string>
# include <vector>
# include <cstdlib>
# include <fstream>
# include <iomanip>
# include <sstream>
# include <utility>
# include <iostream>
# include <algorithm>
# include <stdexcept>

class BitcoinExchange
{
	public:
		typedef typename std::map<std::string, std::string> map;
	private:
		map _infile;
		map	_database;
		
	public:
		BitcoinExchange() {};
		~BitcoinExchange() {};
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);

		void	findValue(std::string day, std::string value);
		void	loadAndCompare(BitcoinExchange& btc, char *file);
		void	checkValue(std::string value, map& target);
		void	fillDatabase(map& target, const std::string &file, char delimiter);
};

typedef struct	s_Date
{
		int day;
		int month;
		int year;
}		t_Date;

#endif // BITCOINEXCHANGE_HPP
