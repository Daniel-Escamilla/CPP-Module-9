/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:54:02 by descamil          #+#    #+#             */
/*   Updated: 2025/06/18 19:25:18 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

btc::btc()
    : _database("DataBase/data.csv"), _filename(NULL)
{
    
}

btc::btc(std::string filename)
    : _database("DataBase/data.csv"), _filename(filename)
{
    
}

btc::~btc()
{

}

btc::btc(const btc &copy)
{

}

btc& btc::operator=(const btc &copy)
{
    
}
