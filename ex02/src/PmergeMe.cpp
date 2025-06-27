/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:07:55 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/06/26 12:39:19 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

PmergeMe::~PmergeMe()
{

}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	(void) copy;
}

PmergeMe PmergeMe::operator=(const PmergeMe &copy)
{
	(void) copy;
	return *this;
}

bool validChar(const char& character)
{
	if (character == '-' || character == '+')
		throw std::logic_error("Invalid signed numbers");
	if (isspace(character) || isdigit(character))
		return true;
	return false;
}

unsigned int PmergeMe::nextNumber(const std::string& array, size_t& i)
{
	while (isspace(array[i]))
		i++;
	unsigned long number = 0;
	while (array[i] && isdigit(array[i]))
		number = number * 10 + (array[i++] - '0');
	if (number > std::numeric_limits<unsigned int>::max())
		throw std::overflow_error("Number too big");
	for (std::list<unsigned int>::iterator it = _list.begin(); it != _list.end(); it++)
		if (number == *it)
			throw std::logic_error("Found duplicate numbers");
	return static_cast<unsigned int>(number);
}

void PmergeMe::readNumbers(const std::string& array)
{
	unsigned int number1;
	unsigned int number2;

	for (size_t i = 0; array[i] &&  i < array.size(); i++)
		if (validChar(array[i]) == false)
			throw std::invalid_argument(std::string("Invalid character: ") + array[i]);
	for (size_t i = 0; array[i] && i < array.size();)
	{
		number1 = nextNumber(array, i);
		if ((array).find_first_not_of(' ', i) == std::string::npos)
		{
			_list.push_back(number1);
			break ;
		}
		number2 = nextNumber(array, i);
		_list.push_back(std::max(number1, number2));
		_deque.push_back(std::min(number1, number2));
	}
	_list.sort();
}

void PmergeMe::printTest()
{
	std::cout << '\n' << "LIST" << '\n';
	while (!_list.empty())
	{
		std::cout << _list.front() << '\n';
		_list.pop_front();
	}
	std::cout << '\n' << "DEQUE" << '\n';
	while (!_deque.empty())
	{
		std::cout << _deque.front() << '\n';
		_deque.pop_front();
	}
}