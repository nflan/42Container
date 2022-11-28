/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:32:18 by nflan             #+#    #+#             */
/*   Updated: 2022/11/28 13:08:53 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/vector.hpp"
#include "../incs/stack.hpp"
#include "../incs/iterator.hpp"
#include "../incs/viterator.hpp"
#include "../incs/tools.hpp"
#include <sstream>
#include <iostream>
#include <stack>
#include <string>

#ifndef	NAMESPACE
#define	NAMESPACE ft
#endif

/*template<class Os, class Co>
Os& operator<<(Os& os, const Co& co) 
{
	os << "{";
	for (size_t i = 0; i < co.size(); i++)
		os << ' ' << co[i];
	return os << " } ";
}*/

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
	{
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
		{
			// This test checks if vector works with iterators tagged as std::input_iterator_tag
			std::cout << std::endl;
			NAMESPACE::vector<char> v;

			std::istringstream str("1 2 3 4 5 6 7");
			std::istreambuf_iterator<char> it(str), end;
			std::cout << "v size = " << v.size() << std::endl;
			std::cout << "v capacity = " << v.capacity() << std::endl;
			std::cout << "v = " << v << std::endl;
			v.assign(it, end);

			std::cout << "v size = " << v.size() << std::endl;
			std::cout << "v capacity = " << v.capacity() << std::endl;
			std::cout << "v = " << v << std::endl;
			std::cout << std::endl;
		}
	}

	//ERASE
	{
		std::cout << "Test erase avec c2 = 012346789" << std::endl;
		NAMESPACE::vector<int> c2;
		size_t	size = 10;
		for (size_t i = 0; i < size; i++)
		{
			c2.push_back(i);
			std::cout << " --> c2[" << i << "] = " << c2[i] << std::endl;
		}
		std::cout << "c2.erase begin() + 2" << std::endl;
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

	//INSERT
	{
		std::cout << "Test insert avec c2 = 012346789" << std::endl;
		NAMESPACE::vector<int> c2(5);
		size_t	size = 5;
		for (size_t i = 0; i < size; i++)
		{
			c2[i] = i;
			c2.push_back(i + 5);
		}
		std::cout << c2 << " et c2.capacity() = " << c2.capacity() << " et size = " << c2.size() << std::endl;
		c2.insert(c2.begin() + 2, 5);
		std::cout << "c2.insert(begin() + 2, 5): " << c2 << std::endl;
		std::cout << "c2.capacity() = " << c2.capacity() << " et size = " << c2.size() << std::endl;
		c2.insert(c2.end(), 100);
		std::cout << "c2.insert(end(), 100): " << c2 << std::endl;
		std::cout << "c2.capacity() = " << c2.capacity() << " et size = " << c2.size() << std::endl;

		std::cout << std::endl << "Creation d'un vector avec iterators begin + 2 / end - 2 de c2" << std::endl;
		NAMESPACE::vector<int> c5(c2.begin() + 2, c2.end() - 2);
		std::cout << c5 << std::endl;
		std::cout << "c5.capacity() = " << c5.capacity() << " et size = " << c5.size() << std::endl;
		std::cout << std::endl << "Insertion a c5[1] de c2[5] a c2[20]" << std::endl;
		c5.insert(c5.begin() + 1, c2.begin() + 5, c2.begin() + 20);
		std::cout << c5 << std::endl;
		std::cout << "c5.capacity() = " << c5.capacity() << " et size = " << c5.size() << std::endl;
		std::cout << std::endl;

		c2.insert(c2.end() - 3, static_cast<size_t>(10), static_cast<const int>(-2));
		std::cout << "c2.insert(c2.end() - 3, 10, -2): " << c2 << std::endl;
		std::cout << "c2.capacity() = " << c2.capacity() << " et size = " << c2.size() << std::endl;
		
		c2.insert(c2.end(), static_cast<size_t>(100), static_cast<const int>(100));
		std::cout << "c2.insert(c2.end(), 2, 100): " << c2 << std::endl;
		std::cout << "c2.capacity() = " << c2.capacity() << " et size = " << c2.size() << std::endl;

		std::cout << std::endl << "Creation d'un vector avec iterators begin + 2 / end - 2 de c2" << std::endl;
		NAMESPACE::vector<int> c3(c2.begin() + 2, c2.end() - 2);
		std::cout << c3 << std::endl;
		std::cout << "c3.capacity() = " << c3.capacity() << " et size = " << c3.size() << std::endl;

		std::cout << std::endl << "Creation d'un vector NULL puis association de c3 par operator =" << std::endl;
		NAMESPACE::vector<int> c4 = c3;
		std::cout << c4 << std::endl;
		std::cout << "c4.capacity() = " << c4.capacity() << " et size = " << c4.size() << std::endl;
		std::cout << std::endl << "C4 = C2" << std::endl;
		c4 = c2;
		std::cout << c4 << std::endl;
		std::cout << "c4.capacity() = " << c4.capacity() << " et size = " << c4.size() << std::endl;

		//Test avec throw erreur car pos < 0
		try {
		std::cout << std::endl << "Insertion a c5[-1] de c2[20] a c2[10]" << std::endl;
		c5.insert(c5.begin() - 1, c2.begin() + 20, c2.begin() + 10);
		std::cout << c5 << std::endl;
		std::cout << "c5.capacity() = " << c5.capacity() << " et size = " << c5.size() << std::endl;
		std::cout << std::endl; }
		catch ( std::exception & e ) {
		}
		std::cout << std::endl;
	}

	//SWAP
	{
		std::cout << "Test swap" << std::endl;
		NAMESPACE::vector<int> a1;
		NAMESPACE::vector<int> a2;

		a1.push_back(1);
		a1.push_back(2);
		a1.push_back(3);
		a2.push_back(4);
		a2.push_back(5);
		NAMESPACE::vector<int>::iterator it1 = a1.begin() + 1;
		NAMESPACE::vector<int>::iterator it2 = a2.begin() + 1;

		int& ref1 = a1.front();
		int& ref2 = a2.front();

		std::cout << "a1.capacity = " << a1.capacity() << " et a1.size = " << a1.size() << std::endl;
		std::cout << "a2.capacity = " << a2.capacity() << " et a2.size = " << a2.size() << std::endl;
		std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
		a1.swap(a2);
		std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
		std::cout << "a1.capacity = " << a1.capacity() << " et a1.size = " << a1.size() << std::endl;
		std::cout << "a2.capacity = " << a2.capacity() << " et a2.size = " << a2.size() << std::endl;
		std::cout << std::endl;
	}

	//RESIZE
	{
		std::cout << "Test resize" << std::endl;
		NAMESPACE::vector<int> c;

		c.push_back(1);
		c.push_back(2);
		c.push_back(3);
		std::cout << "Le vector contient: " << c << std::endl;

		c.resize(5, 3);
		std::cout << "Apres resize up a 5 (initializer = 3): " << c << std::endl;

		c.resize(2, 2);
		std::cout << "Apres resize down a 2 (initializer = 2): " << c << std::endl;

		c.resize(7, 4);
		std::cout << "Apres resize up a 7 (initializer = 4): " << c << std::endl;

		c.resize(10, 100);
		std::cout << "Apres resize up a 10 (initializer = 4): " << c << std::endl;
		std::cout << std::endl;
	}

	//AT
	{
		std::cout << "Test at" << std::endl;
		NAMESPACE::vector<int> c(5);
		size_t	size = 5;
		for (size_t i = 0; i < size; i++)
		{
			c[i] = i;
			c.push_back(i + 5);
		}
		std::cout << "c = " << c << std::endl;
		std::cout << "c.at(2) = " << c.at(2) << std::endl;
		std::cout << "c.front() = " << c.front() << std::endl;
		std::cout << "c.back() = " << c.back() << std::endl;
		std::cout << std::endl;
	}

	std::cout << "creation de c2 par copie de c1" << std::endl << std::endl;
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
	std::cout << std::endl;

//REVERSE ITERATORS
	{
		std::cout << "Reverse iterators tests FT" << std::endl;
		ft::vector<int> c2(5);
		size_t	size = 5;
		for (size_t i = 0; i < size; i++)
		{
			c2[i] = i;
			c2.push_back(i + 5);
		}
		std::cout << c2 << " et c2.capacity() = " << c2.capacity() << " et size = " << c2.size() << std::endl;

		ft::reverse_viterator<ft::vector<int>::iterator>	rev_ite = c2.rbegin();
		ft::reverse_viterator<ft::vector<int>::iterator>	rev_it = c2.rend();
		std::cout << "creation reverse iterator rbegin = " << *rev_ite << std::endl;
		std::cout << "creation reverse iterator rend = " << *rev_it << std::endl;
		std::cout << std::endl << "comparaison de rev_ite et rev_it" << std::endl;
		compare(rev_ite, rev_it);
	}
	{
		std::cout << "Reverse iterators tests STD" << std::endl;
		std::vector<int> c2(5);
		size_t	size = 5;
		for (size_t i = 0; i < size; i++)
		{
			c2[i] = i;
			c2.push_back(i + 5);
		}
		std::cout << c2 << " et c2.capacity() = " << c2.capacity() << " et size = " << c2.size() << std::endl;

		std::reverse_iterator<std::vector<int>::iterator>	rev_ite = c2.rbegin();
		std::reverse_iterator<std::vector<int>::iterator>	rev_it = c2.rend();
		std::cout << "creation reverse iterator rbegin = " << *rev_ite << std::endl;
		std::cout << "creation reverse iterator rend = " << *rev_it << std::endl;
		std::cout << std::endl << "comparaison de rev_ite et rev_it" << std::endl;
		compare(rev_ite, rev_it);
	}
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
