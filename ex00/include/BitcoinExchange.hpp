/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:53 by descamil          #+#    #+#             */
/*   Updated: 2025/06/22 19:39:27 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <ctime>
# include <cmath>
# include <limits>
# include <string>
# include <vector>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <utility>
# include <iostream>
# include <algorithm>
# include <stdexcept>

class BitcoinExchange
{
	private:
		std::vector<std::pair<std::string, std::string> > _database;
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);

		void	fillDatabase(const std::string& file);
};

#endif // BITCOINEXCHANGE_HPP
