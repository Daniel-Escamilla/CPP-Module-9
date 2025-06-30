/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:07:55 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/06/30 18:03:51 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

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

void splitList(std::list<unsigned int>& source, std::list<unsigned int>& left, std::list<unsigned int>& right)
{
	if (source.empty())
		return ;

	std::list<unsigned int>::iterator fast = source.begin();
	std::list<unsigned int>::iterator slow = source.begin();

	if (fast != source.end())
	{
		fast++;
		if (fast != source.end())
		{
			fast++;
			slow++;
		}
	}
	left.splice(left.begin(), source, source.begin(), slow);
	right.splice(right.begin(), source);
}

void mergeSortedLists(std::list<unsigned int>& result, std::list<unsigned int>& left, std::list<unsigned int>& right)
{
	while (!left.empty() && !right.empty())
	{
		if (left.front() <= right.front())
		{
			result.push_back(left.front());
			left.pop_front();
		}
		else
		{
			result.push_back(right.front());
			right.pop_front();
		}
	}
	result.splice(result.end(), left);
	result.splice(result.end(), right);
}

std::list<unsigned int>& mergeSort(std::list<unsigned int>& list)
{
	if (list.size() <= 1)
		return list;
	if (list.size() == 2)
	{
		std::list<unsigned int>::iterator first = list.begin();
		std::list<unsigned int>::iterator second = first;
		++second;
		if (*second < *first)
		{
			unsigned int tmp = *first;
			*first = *second;
			*second = tmp;
		}
		return list;
	}
	std::list<unsigned int> left;
	std::list<unsigned int> right;
	splitList(list, left, right);
	mergeSort(left);
	mergeSort(right);
	list.clear();
	mergeSortedLists(list, left, right);
	return list;
}

std::string trim(std::string str)
{
    while (!str.empty() && std::isspace(str[0]))
        str.erase(0, 1);
    while (!str.empty() && std::isspace(str[str.size() - 1]))
        str.erase(str.size() - 1, 1);
    return str;
}

void PmergeMe::orderListNumbers(const std::string& str)
{
	unsigned int number1;
	unsigned int number2;
	std::string	array;

	for (size_t i = 0; str[i] &&  i < str.size(); i++)
		if (validChar(str[i]) == false)
			throw std::invalid_argument(std::string("Invalid character: ") + str[i]);
	array = trim(str);
	for (size_t i = 0; array[i] && i < array.size();)
	{
		number1 = nextNumber(array, i);
		_EntireList.push_back(number1);
		if ((array).find_first_not_of(' ', i) == std::string::npos )
		{
			_maxList.push_back(number1);
			break ;
		}
		number2 = nextNumber(array, i);
		_EntireList.push_back(number2);
		_maxList.push_back(std::max(number1, number2));
		_minList.push_back(std::min(number1, number2));
	}
	mergeSortedLists(_List, mergeSort(_maxList), mergeSort(_minList));
}

void splitList(std::deque<unsigned int>& source, std::deque<unsigned int>& left, std::deque<unsigned int>& right)
{
	if (source.empty())
		return ;

	std::deque<unsigned int>::iterator fast = source.begin();
	std::deque<unsigned int>::iterator slow = source.begin();

	if (fast != source.end())
	{
		fast++;
		if (fast != source.end())
		{
			fast++;
			slow++;
		}
	}
	left.insert(left.begin(), source.begin(), slow);
	source.erase(source.begin(), slow);
	right.insert(right.begin(), source.begin(), source.end());
	source.clear();
}

void mergeSortedLists(std::deque<unsigned int>& result, std::deque<unsigned int>& left, std::deque<unsigned int>& right)
{
	while (!left.empty() && !right.empty())
	{
		if (left.front() <= right.front())
		{
			result.push_back(left.front());
			left.pop_front();
		}
		else
		{
			result.push_back(right.front());
			right.pop_front();
		}
	}
	result.insert(result.end(), left.begin(), left.end());
	left.clear();
	result.insert(result.end(), right.begin(), right.end());
	right.clear();
}

void mergeSort(std::deque<unsigned int>& list)
{
	if (list.size() <= 1)
		return ;
	if (list.size() == 2)
	{
		std::deque<unsigned int>::iterator first = list.begin();
		std::deque<unsigned int>::iterator second = first;
		++second;
		if (*second < *first)
		{
			unsigned int tmp = *first;
			*first = *second;
			*second = tmp;
		}
		return ;
	}
	std::deque<unsigned int> left;
	std::deque<unsigned int> right;
	splitList(list, left, right);
	mergeSort(left);
	mergeSort(right);
	list.clear();
	mergeSortedLists(list, left, right);
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
	}
	return j2;	
}

void PmergeMe::dequeJacobOrder()
{
	std::deque<unsigned int> jacobIndices;
	std::deque<bool> inserted(_minDeque.size(), false);
	std::size_t n = _minDeque.size();

	for (std::size_t i = 1;; ++i)
	{
		int j = jacobsthal(i);
		if (j >= static_cast<int>(n))
			break ;
		if (!inserted[j])
		{
			jacobIndices.push_back(j);
			inserted[j] = true;
		}
	}
	std::size_t k;
	for (k = 0; k < jacobIndices.size(); ++k)
	{
		std::size_t idx = jacobIndices[k];
		std::deque<unsigned int>::iterator it = _minDeque.begin();
		std::advance(it, idx);
		unsigned int val = *it;

		std::deque<unsigned int>::iterator pos = _maxDeque.begin();
		while (pos != _maxDeque.end() && *pos < val)
			++pos;
		_maxDeque.insert(pos, val);
	}
	std::size_t i;
	for (i = 0; i < n; ++i)
	{
		if (inserted[i])
			continue ;

		std::deque<unsigned int>::iterator it = _minDeque.begin();
		std::advance(it, i);
		unsigned int val = *it;

		std::deque<unsigned int>::iterator pos = _maxDeque.begin();
		while (pos != _maxDeque.end() && *pos < val)
			++pos;
		_maxDeque.insert(pos, val);
	}
}

void PmergeMe::orderDequeNumbers(const std::string& str)
{
	unsigned int number1;
	unsigned int number2;
	std::string	array;

	for (size_t i = 0; str[i] &&  i < str.size(); i++)
		if (validChar(str[i]) == false)
			throw std::invalid_argument(std::string("Invalid character: ") + str[i]);
	array = trim(str);
	for (size_t i = 0; array[i] && i < array.size();)
	{
		number1 = nextNumber(array, i);
		if ((array).find_first_not_of(' ', i) == std::string::npos )
		{
			_maxDeque.push_back(number1);
			break ;
		}
		number2 = nextNumber(array, i);
		_maxDeque.push_back(std::max(number1, number2));
		_minDeque.push_back(std::min(number1, number2));
	}
	mergeSort(_maxDeque);
}

std::string formatContainer(const std::list<unsigned int>& c)
{
	std::ostringstream oss;
	std::list<unsigned int>::const_iterator it = c.begin();
	int count = 0;
	size_t totalChars = 0;
	while (it != c.end() && count < 5)
	{
		std::ostringstream num;
		num << *it << " ";
		totalChars += num.str().size();
		oss << num.str();
		++it;
		++count;
	}
	if (it != c.end())
		oss << " [...]";

	return oss.str();
}

void PmergeMe::printInfo()
{
	{
		std::cout << "Before: " << formatContainer(_EntireList) << std::endl;
		std::cout << "After:  " << formatContainer(_List) << std::endl;
		std::cout << std::fixed << std::setprecision(5);
		std::cout << "Time to process a range of " << _List.size()
				  << " elements with std::deque : " << dequeTime << " ms" << std::endl;
		std::cout << "Time to process a range of " << _List.size()
				  << " elements with std::list  : " << listTime << " ms" << std::endl;
	}
}
