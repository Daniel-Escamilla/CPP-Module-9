/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:54:06 by descamil          #+#    #+#             */
/*   Updated: 2025/06/18 19:38:37 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    std::ifstream inputFile(argv[1]);
    if (inputFile.is_open())
    {
        btc input;
        while (std::getline(inputFile, input.line))
        {
            if (std::find(input.line.begin(), input.line.end(), '|') != input.line.end())
                (void)input; // Guardar la linea
            else
                (void)input; // Salir con error especifico
        }
    }
    else
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    
}
