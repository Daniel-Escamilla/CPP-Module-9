/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:53 by descamil          #+#    #+#             */
/*   Updated: 2025/06/21 20:26:32 by daniel-esca      ###   ########.fr       */
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
		std::pair<std::string, std::string> database;
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);

		void	fillDatabase(const std::string& file);
};

#endif // BITCOINEXCHANGE_HPP
