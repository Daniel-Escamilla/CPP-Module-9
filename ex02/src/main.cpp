/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:07:52 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/06/28 08:04:48 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw std::invalid_argument("Incorrect number of arguments");
		if (std::string(argv[1]).find_first_not_of(' ') == std::string::npos
			|| std::string(argv[1]).find_first_not_of('\n') == std::string::npos
			|| std::string(argv[1]).find_first_not_of('\t') == std::string::npos)
			throw std::invalid_argument("Argument Empty");
		PmergeMe list;
		list.readNumbers(std::string(argv[1]));
		list.insertNumbers();
		list.printTest();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
