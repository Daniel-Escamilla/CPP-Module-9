/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-escamilla <daniel-escamilla@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:30:31 by daniel-esca       #+#    #+#             */
/*   Updated: 2025/06/23 18:57:37 by daniel-esca      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RPN.hpp"

static long parseNumber(const char* expr, int& i)
{
    long number = 0;
	while (std::isdigit(static_cast<unsigned char>(expr[i])))
		number = number * 10 + (expr[i++] - '0');
	if (number > 9)
		throw std::overflow_error("Number too big");
    return number;
}

std::vector<Token> extractTokens(const char* expr)
{
    if (!expr || expr[0] == '\0')
        throw std::invalid_argument("Empty expression");

    std::vector<Token> tokens;
    int i = 0;

    while (expr[i])
	{
        while (std::isspace(static_cast<unsigned char>(expr[i])))
            ++i;
        if (!expr[i])
			break ;
        if (std::isdigit(static_cast<unsigned char>(expr[i])))
        {
            long value = parseNumber(expr, i);
            Token t;
			t.type = Token::Number;
			t.number = value;
            tokens.push_back(t);
            continue ;
        }
        if (expr[i] == '+' || expr[i] == '-'
				|| expr[i] == '*' || expr[i] == '/')
		{
            Token t; 
            t.type = Token::Operator; 
            t.oper = expr[i++]; 
            tokens.push_back(t);
            continue ;
        }
        throw std::runtime_error(std::string("Unexpected character: ") + expr[i]);
    }
    return tokens;
}

long long evaluateOperation(long long first, long long second, char oper)
{
	long long result = 0;

	switch (oper)
	{
		case '+':
			result = first + second;
			break;
		case '-':
			result = first - second;
			break;
		case '*':
			result = first * second;
			break;
		case '/':
			if (second == 0)
			{
				std::ostringstream oss;
    			oss << '[' << second << " / " << first << ']';
				throw std::logic_error(std::string("Error division by 0: ") + oss.str());
			}
			result = first / second;
			break;
		default:
			break;
	}
	return (result);
}

void	processTokens(std::vector<Token> tokens)
{
	std::vector<long long> result;
	std::vector<Token>::iterator token;

	token = tokens.begin();
	if (token == tokens.end())
		throw std::logic_error(std::string("Invalid expresion"));
	if (tokens.size() < 2)
		throw std::runtime_error("Not enough numbers");
	for (; token != tokens.end(); token++)
	{
		if (token->type == Token::Number)
			result.push_back(token->number);
		else
		{
			if (result.size() < 2)
				throw std::runtime_error("Not enough numbers");
			long long second = result.back();
			result.pop_back();
			long long first = result.back();
			result.pop_back();
			result.push_back(evaluateOperation(first, second, token->oper));
		}
	}
	if (result.size() != 1)
		throw std::runtime_error("Not enough operators");
	std::cout << result.front() << std::endl;
}

