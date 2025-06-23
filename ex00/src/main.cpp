/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:54:06 by descamil          #+#    #+#             */
/*   Updated: 2025/06/23 11:35:51 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: invalid number of arguments" << std::endl;
        return 1;
    }
    try 
    {
        BitcoinExchange btc;
        btc.loadAndCompare(btc, argv[1]);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

	return 0;
}
