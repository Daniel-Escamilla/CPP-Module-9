/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:07:48 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/06/26 10:56:02 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <list>
# include <deque>
# include <limits>
# include <string>
# include <sstream>
# include <iostream>
# include <algorithm>

class PmergeMe
{
	private:
	
		std::list<unsigned int> _list;
		std::list<unsigned int> _deque;
	
	public:
		void	printTest();
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe operator=(const PmergeMe &copy);
	
		void readNumbers(const std::string& array);

		unsigned int nextNumber(const std::string& array, size_t& i);

};

#endif // PMERGEME_HPP
