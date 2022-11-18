/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:32:18 by nflan             #+#    #+#             */
/*   Updated: 2022/11/18 18:36:26 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/vector.hpp"
#include "../incs/stack.hpp"
#include "../incs/iterator.hpp"
#include "../incs/tools.hpp"
#include <iostream>
#include <stack>
#include <string>

#ifndef	NAMESPACE
#define	NAMESPACE ft
#endif

void	dostack();
void	dovector();
template< typename T >
void	compare(T c1, T c2);

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
			dovector();
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

//VECTOR
void	dovector( void )
{
	std::cout << "Creation stack<int> c1 avec size = 0" << std::endl << std::endl;
	//Constructeur par defaut
	NAMESPACE::vector<int> c1;
	std::cout << "c1 max_size = " << c1.max_size() << std::endl;
	std::cout << "c1 Empty: " << (c1.empty() ? "true" : "false") << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << "push(1) on c1" << std::endl; 
	c1.push_back(1);
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << "push(2) on c1" << std::endl; 
	c1.push_back(2);
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << "push(3) on c1" << std::endl; 
	c1.push_back(3);
	std::cout << "c1[0] = " << c1[0] << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
//	std::cout << "pop() on c1" << std::endl; 
//	c1.pop_back();
//	std::cout << "c1 size = " << c1.size() << std::endl;
//	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << std::endl;

	//constructeur par iterator
	NAMESPACE::vector<int> c4(c1.begin() + 1, c1.end());
	std::cout << "c4 size = " << c4.size() << std::endl;
	std::cout << "c4 capacity = " << c4.capacity() << std::endl;
	for (int i = 0; i < 2; i++)
	{
		std::cout << " --> c1[" << i << "] = " << c1[i] << std::endl;
		std::cout << " --> c4[" << i << "] = " << c4[i] << std::endl;
	}

	//ASSIGN
	//constructeur avec infos
	NAMESPACE::vector<int> c3(static_cast<size_t>(30), 20);
	std::cout << "c3 size = " << c3.size() << std::endl;
	std::cout << "c3 capacity = " << c3.capacity() << std::endl;
	std::cout << "Assign tests" << std::endl;
	for (int i = 3; i < 11; i++)
	{
		std::cout << "push(" << i << ") on c1" << std::endl; 
		c1.push_back(i);
	}
	for (int i = 0; i < 10; i++)
		std::cout << " --> c1[" << i << "] = " << c1[i] << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	c1.assign(static_cast<size_t>(5), 2);
	for (int i = 0; i < 10; i++)
		std::cout << " --> c1[" << i << "] = " << c1[i] << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	//Reserve
	std::cout << "c1 reserve(20)" << std::endl;
	c1.reserve(20);
	for (int i = 0; i < 10; i++)
		std::cout << " --> c1[" << i << "] = " << c1[i] << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << std::endl;
	std::cout << "Assign avec iterators c3.begin et c3.begin+3" << std::endl;
	for (int i = 0; i < 7; i++)
		std::cout << " --> c3[" << i << "] = " << c3[i] << std::endl;
	std::cout << "c3 size = " << c3.size() << std::endl;
	std::cout << "c3 capacity = " << c3.capacity() << std::endl;
	c1.assign(c3.begin(), c3.begin() + 3);
	for (int i = 0; i < 7; i++)
		std::cout << " --> c1[" << i << "] = " << c1[i] << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << std::endl;

	//ERASE
	{
		std::cout << "Test erase avec c2 = 012346789" << std::endl;
		NAMESPACE::vector<int> c2;
		for (int i = 0; i < 10; i++)
		{
			c2.push_back(i);
			std::cout << " --> c2[" << i << "] = " << c2[i] << std::endl;
		}
		std::cout << "c2.erase begin + 2" << std::endl;
		c2.erase(c2.begin() + 2);
		for (size_t i = 0; i < c2.size(); i++)
			std::cout << " --> c2[" << i << "] = " << c2[i] << std::endl;
		std::cout << "c2.erase begin + 2 to begin + 4" << std::endl;
		c2.erase(c2.begin() + 2, c2.begin() + 4);
		for (size_t i = 0; i < c2.size(); i++)
			std::cout << " --> c2[" << i << "] = " << c2[i] << std::endl;
		std::cout << "c2.erase begin() to end()" << std::endl;
		c2.erase(c2.begin(), c2.end());
		for (size_t i = 0; i < c2.size(); i++)
			std::cout << " --> c2[" << i << "] = " << c2[i] << std::endl;
		std::cout << std::endl;
	}

	std::cout << std::endl << "creation de c2 par copie de c1" << std::endl << std::endl;
	//constructeur par copie
	NAMESPACE::vector<int> c2(c1);
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c2 capacity = " << c2.capacity() << std::endl;
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "c2 Empty: " << (c2.empty() ? "true" : "false") << std::endl;
	std::cout << "push(5) on c2" << std::endl; 
	c2.push_back(5);
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "pop() on c2" << std::endl;
	c2.pop_back();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "pop() on c2" << std::endl;
	c2.pop_back();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "pop() on c2" << std::endl;
	c2.pop_back();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "pop() on c2" << std::endl;
	c2.pop_back();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << std::endl;

//	Valgrind error parce que pas protege dans std::stack donc pas non plus dans la mienne.
//	std::cout << "c2 top() = " << c2.top() << std::endl;
//	std::stack<int>	r1;
//	std::cout << r1.top() << std::endl;
//	std::cout << "c1 top() = " << c1.top() << std::endl;
//	std::cout << std::endl;

	std::cout << "Operators avec c1 == c2" << std::endl;
	//surcharge d'operateur =
	c2 = c1;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << "c2 capacity = " << c2.capacity() << std::endl;
	compare(c1, c2);
	
	std::cout << "Operators avec c1 > c2" << std::endl;
	c2.pop_back();
	compare(c1, c2);

	std::cout << "Operators avec c1 < c2" << std::endl;
	c2.push_back(42);
	compare(c1, c2);

	std::cout << "Operators avec c1 == c2" << std::endl;
	c2.pop_back();
	c2.push_back(2);
	compare(c1, c2);
}

template< typename T >
void	compare(T c1, T c2)
{
	std::cout << std::endl;
	std::cout << "c1 == c2 ?\t" << (c1 == c2 ? "true" : "false") << std::endl;
	std::cout << "c1 != c2 ?\t" << (c1 != c2 ? "true" : "false") << std::endl;
	std::cout << "c1 < c2 ?\t" << (c1 < c2 ? "true" : "false") << std::endl;
	std::cout << "c1 <= c2 ?\t" << (c1 <= c2 ? "true" : "false") << std::endl;
	std::cout << "c1 > c2 ?\t" << (c1 > c2 ? "true" : "false") << std::endl;
	std::cout << "c1 >= c2 ?\t" << (c1 >= c2 ? "true" : "false") << std::endl;
	std::cout << std::endl;
}
//STACK
void	dostack( void )
{
	std::cout << "Creation stack<int> c1" << std::endl << std::endl;
	NAMESPACE::stack<int> c1;
	std::cout << "c1 Empty: " << (c1.empty() ? "true" : "false") << std::endl;
	std::cout << "push(5) on c1" << std::endl; 
	c1.push(5);
	std::cout << "push(2) on c1" << std::endl; 
	c1.push(2);
	std::cout << "c1 size = " << c1.size() << std::endl;

	std::cout << std::endl << "creation de c2 par copie de c1" << std::endl << std::endl;
	NAMESPACE::stack<int> c2(c1);
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

	std::cout << "Operators avec c1 == c2" << std::endl;
	c2 = c1;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c2 size = " << c2.size() << std::endl;
	compare(c1, c2);

	std::cout << "Operators avec c1 > c2" << std::endl;
	std::cout << "pop on c2" << std::endl; 
	c2.pop();
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c2 size = " << c2.size() << std::endl;
	compare(c1, c2);

	std::cout << "Operators avec c1 < c2" << std::endl;
	std::cout << "push(2) on c2" << std::endl; 
	c2.push(2);
	std::cout << "push(2) on c2" << std::endl; 
	c2.push(2);
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c2 size = " << c2.size() << std::endl;
	compare(c1, c2);
}
