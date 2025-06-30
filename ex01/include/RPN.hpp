/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:30:34 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/06/30 18:04:24 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <math.h>
# include <string>
# include <limits>
# include <vector>
# include <sstream>
# include <iostream>

struct Token
{
	enum Type { Number, Operator } type;
	int number;
	char oper;
};

std::vector<Token>	extractTokens(const char* expr);
void				processTokens(std::vector<Token> tokens);

#endif // RPN_HPP
