/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:53 by descamil          #+#    #+#             */
/*   Updated: 2025/06/18 19:37:09 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <iostream>
# include <fstream> 
# include <algorithm>

class btc
{
    private:
        const std::string   _database;
        const std::string   _filename;
    public:
        btc();
        btc(std::string filename);
        ~btc();
        btc(const btc &copy);
        btc& operator=(const btc &copy);
        
        std::string line;
};

#endif // BITCOINEXCHANGE_HPP
