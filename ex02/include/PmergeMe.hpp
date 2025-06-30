/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:07:48 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/06/30 18:04:16 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <list>
# include <ctime>
# include <deque>
# include <limits>
# include <string>
# include <iomanip>
# include <sstream>
# include <iostream>
# include <algorithm>
# include <sys/time.h>

class PmergeMe
{
	private:
		std::list<unsigned int> _maxList;
		std::list<unsigned int> _minList;
		std::list<unsigned int> _List;
		std::list<unsigned int> _EntireList;
		std::deque<unsigned int> _maxDeque;
		std::deque<unsigned int> _minDeque;
		std::deque<unsigned int> _Deque;
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe operator=(const PmergeMe &copy);
		void			printInfo();
		void			orderListNumbers(const std::string& array);
		void			orderDequeNumbers(const std::string& array);
		void			dequeJacobOrder();
		int				jacobsthal(int n);
		unsigned int	nextNumber(const std::string& array, size_t& i);
		
		double listTime;
		double dequeTime;
};

#endif // PMERGEME_HPP
