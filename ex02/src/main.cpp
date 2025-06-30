/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:07:52 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/06/30 17:59:44 by descamil         ###   ########.fr       */
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
		struct timeval start, end;

		gettimeofday(&start, NULL);
		list.orderListNumbers(std::string(argv[1]));
		gettimeofday(&end, NULL);
		list.listTime = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1e3;
		
		gettimeofday(&start, NULL);
		list.orderDequeNumbers(std::string(argv[1]));
		list.dequeJacobOrder();
		gettimeofday(&end, NULL);
		list.dequeTime = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1e3;
		
		
		list.printInfo();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
