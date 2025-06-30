/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:07:55 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/06/28 08:16:43 by daniel-esca      ###   ########.fr       */
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
	for (std::list<unsigned int>::iterator it = _maxList.begin(); it != _maxList.end(); it++)
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
			_maxList.push_back(number1);
			break ;
		}
		number2 = nextNumber(array, i);
		_maxList.push_back(std::max(number1, number2));
		_minList.push_back(std::min(number1, number2));
	}
	_maxList.sort(); // Crear algoritmo de ordenación
}

void PmergeMe::printTest()
{
	std::cout << '\n' << "MAX-LIST" << '\n';
	while (!_maxList.empty())
	{
		std::cout << _maxList.front() << '\n';
		_maxList.pop_front();
	}
	std::cout << '\n' << "MIN-LIST" << '\n';
	while (!_minList.empty())
	{
		std::cout << _minList.front() << '\n';
		_minList.pop_front();
	}
}

int PmergeMe::jacobsthal(int n)
{
	if (n == 0 || n == 1)
		return n;
	int j0 = 0;
	int j1 = 1;
	int j2 = 0;
	while (j2 <= n)
	{
		j2 = j1 + j0 * 2;
		if (j2 > n)
			return j1;
		j0 = j1;
		j1 = j2;
		std::cout << j2 << std::endl;
	}
	return j2;	
}

void PmergeMe::insertNumbers()
{
	while (!_minList.empty())
	{
		unsigned int value = _minList.front();
		std::list<unsigned int>::iterator insertPos = _maxList.begin();
		while (insertPos != _maxList.end() && *insertPos < value)
			++insertPos;
		_maxList.insert(insertPos, value);
		_minList.pop_front();
	}
}
