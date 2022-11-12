/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:32:18 by nflan             #+#    #+#             */
/*   Updated: 2022/11/12 13:10:08 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/vector.hpp"
#include "../incs/stack.hpp"
#include "../incs/iterator.hpp"
#include "../incs/tools.hpp"
#include <iostream>
#include <stack>
#include <string>

using namespace ft;

void	dostack();

int	main( int ac, char **av )
{
	int	i = 0;
	if (ac != 2)
		return (std::cout << "nb args invalid" << std::endl, 1);
	std::string	arg = av[1];
	for (std::string::iterator it = arg.begin(); it != arg.end(); it++)
		*it = std::tolower(*it);
	std::string	type[] = { "stack", "vector", "map" };
	for (i = 0; i < 3; i++)
		if (type[i] == arg)
			break;
	switch (i)
	{
		case (0):
			dostack();
			break;
		case (1):
			std::cout << arg << std::endl;
			break;
		case (2):
			std::cout << arg << std::endl;
			break;
		case (3):
			return (std::cout << "Container '" << arg << "' not found" << std::endl, 1);
			break;
	}

	return (0);
}

//STACK
void	dostack( void )
{
	std::cout << "Creation stack<int> c1" << std::endl << std::endl;
	::stack<int> c1;
	std::cout << "c1 Empty: " << (c1.empty() ? "true" : "false") << std::endl;
	std::cout << "push(5) on c1" << std::endl; 
	c1.push(5);
	std::cout << "push(2) on c1" << std::endl; 
	c1.push(2);
	std::cout << "c1 size = " << c1.size() << std::endl;

	std::cout << std::endl << "creation de c2 par copie de c1" << std::endl << std::endl;
	::stack<int> c2(c1);
	std::cout << "c2 Empty: " << (c2.empty() ? "true" : "false") << std::endl;
	std::cout << "push(5) on c2" << std::endl; 
	c2.push(5);
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "pop() on c2" << std::endl;
	c2.pop();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "pop() on c2" << std::endl;
	c2.pop();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "pop() on c2" << std::endl;
	c2.pop();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "pop() on c2" << std::endl;
//	c2.pop();
//	std::cout << "c2 size = " << c2.size() << std::endl;
//	std::cout << std::endl;

//	Valgrind error parce que pas protege dans std::stack donc pas non plus dans la mienne.
//	std::cout << "c2 top() = " << c2.top() << std::endl;
//	std::stack<int>	r1;
//	std::cout << r1.top() << std::endl;
	std::cout << "c1 top() = " << c1.top() << std::endl;
	std::cout << std::endl;

//	Operators avec c1 > c2
	std::cout << "push(5) on c2" << std::endl; 
	c2.push(5);
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 == c2 ? " << (c1 == c2 ? "true" : "false") << std::endl;
	std::cout << "c1 != c2 ? " << (c1 != c2 ? "true" : "false") << std::endl;
	std::cout << "c1 < c2 ? " << (c1 < c2 ? "true" : "false") << std::endl;
	std::cout << "c1 <= c2 ? " << (c1 <= c2 ? "true" : "false") << std::endl;
	std::cout << "c1 > c2 ? " << (c1 > c2 ? "true" : "false") << std::endl;
	std::cout << "c1 >= c2 ? " << (c1 >= c2 ? "true" : "false") << std::endl;

//	Operators avec c1 == c2
	std::cout << std::endl;
	std::cout << "push(42) on c2" << std::endl; 
	c2.push(42);
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 == c2 ? " << (c1 == c2 ? "true" : "false") << std::endl;
	std::cout << "c1 != c2 ? " << (c1 != c2 ? "true" : "false") << std::endl;
	std::cout << "c1 < c2 ? " << (c1 < c2 ? "true" : "false") << std::endl;
	std::cout << "c1 <= c2 ? " << (c1 <= c2 ? "true" : "false") << std::endl;
	std::cout << "c1 > c2 ? " << (c1 > c2 ? "true" : "false") << std::endl;
	std::cout << "c1 >= c2 ? " << (c1 >= c2 ? "true" : "false") << std::endl;

//	Operators avec c1 < c2
	std::cout << std::endl;
	std::cout << "push(-42) on c2" << std::endl; 
	c2.push(-42);
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 == c2 ? " << (c1 == c2 ? "true" : "false") << std::endl;
	std::cout << "c1 != c2 ? " << (c1 != c2 ? "true" : "false") << std::endl;
	std::cout << "c1 < c2 ? " << (c1 < c2 ? "true" : "false") << std::endl;
	std::cout << "c1 <= c2 ? " << (c1 <= c2 ? "true" : "false") << std::endl;
	std::cout << "c1 > c2 ? " << (c1 > c2 ? "true" : "false") << std::endl;
	std::cout << "c1 >= c2 ? " << (c1 >= c2 ? "true" : "false") << std::endl;
}