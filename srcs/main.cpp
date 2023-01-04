/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:32:18 by nflan             #+#    #+#             */
/*   Updated: 2023/01/04 19:29:03 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/vector.hpp"
#include "../incs/stack.hpp"
#include "../incs/iterator.hpp"
#include "../incs/viterator.hpp"
#include "../incs/rbiterator.hpp"
#include "../incs/tools.hpp"
#include "../incs/rbtree.hpp"
#include "../incs/map.hpp"
#include "../incs/set.hpp"
#include "../incs/color.hpp"
#include <sstream>
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

#ifndef	NAMESPACE
#define	NAMESPACE ft
#endif

//Surcharge operator <<
	template<class Os, typename T>
Os& operator<<(Os& os, const NAMESPACE::vector<T> & co) 
{
	os << "{ ";
	for (size_t i = 0; i < co.size(); i++)
	{
		os << co.at(i);
		if (i != co.size() - 1)
			os << "; ";
	}
	return os << " } ";
}

void	dostack(color);
void	dovector(color);
void	domap(color);
void	doset(color);
template< typename T >
void	compare(T c1, T c2);

int	main( int ac, char **av )
{
	color	c;
	srand (time(NULL));
	int	i = 0;
	int	d = 1;
	if (av[2])
		d = atoi(av[2]);
	if (ac != 2 && ac != 3)
		return (std::cout << c.r << "nb args invalid" << c.rt << std::endl, 1);
	std::string	arg = av[1];
	for (std::string::iterator it = arg.begin(); it != arg.end(); it++)
		*it = std::tolower(*it);
	std::string	type[] = { "stack", "vector", "map", "set" };
	for (i = 0; i < 3; i++)
		if (type[i] == arg)
			break;
	switch (i)
	{
		case (0):
			for (; d > 0; d--)
				dostack(c);
			break;
		case (1):
			for (; d > 0; d--)
				dovector(c);
			break;
		case (2):
			for (; d > 0; d--)
				domap(c);
			break;
		case (3):
			for (; d > 0; d--)
				doset(c);
			break;
		case (4):
			return (std::cout << c.r << "Container '" << arg << "' not found" << c.rt << std::endl, 1);
			break;
	}
	return (0);
}

//map
void	domap( color c )
{
	std::cout << c.b << "COMPARAISON DE PAIRS" << c.rt << std::endl << std::endl;
	{
		std::cout << "Creation d'une pair avec int(2) et std::string('oui')" << std::endl << std::endl;
		NAMESPACE::pair<int, std::string>	p = NAMESPACE::make_pair(2, "oui");
		std::cout << "Creation d'une pair avec int(4) et std::string('et alors')" << std::endl;
		NAMESPACE::pair<int, std::string>	p2 = NAMESPACE::make_pair(4, "et alors");
		std::cout << "Comparaison entre les 2 pairs" << std::endl;
		compare(p, p2);
		std::cout << std::endl;
	}

	NAMESPACE::vector<int>	v;
	for (size_t i = 0; i < 20; i++)
		v.push_back(i);
	std::random_shuffle(v.begin(), v.end());
	NAMESPACE::vector<int>	v2(v);
	//Creation et affichage arbre binaire
	{
		std::cout << c.y << "-----------MAP------------" << c.rt << std::endl << std::endl;
		NAMESPACE::map<int, int>		map;

		//CAPACITY
		std::cout << c.g << "TEST CAPACITY" << c.rt << std::endl;
		std::cout << "Is map empty ? " << (map.empty() ? "TRUE" : "FALSE") << std::endl;
		std::cout << "Map size ? " << map.size() << std::endl;
		std::cout << "Map max::sisze ? " << map.max_size() << std::endl;
		std::cout << std::endl;

		//FILLING
		std::cout << c.g << "TEST INSERT" << c.rt << std::endl;
		for (size_t i = 0; i < 20; i++)
		{
			if (v[i] != 12)
				std::cout << "v[i] = " << v[i] << " -> " << map.insert(NAMESPACE::make_pair(v[i], v[i])).first->first << "; ";
		}
		std::cout << std::endl << std::endl;

		{
			//COPY WITH ITERATORS
			std::cout << c.g << "TEST COPY WITH ITERATORS" << c.rt << std::endl;
			NAMESPACE::map<int, int>		map2;
			map2.insert(map.begin(), map.end());
			std::cout << "Map2 size ? " << map2.size() << std::endl;
			std::cout << "Map content : ";
			for (NAMESPACE::map<int, int>::iterator it = map.begin(); it != map.end(); it++)
				std::cout << it->first << "; ";
			std::cout << std::endl << std::endl; 
		}

		//INSERT WITH POSITION
		std::cout << c.g << "TEST INSERT WITH POSITION" << c.rt << std::endl;
		std::cout << "insert 12 a position 12 = " << map.insert(map.find(13), NAMESPACE::make_pair(12, 12))->first << std::endl;
		std::cout << "insert 12 a position 12 = " << map.insert(map.find(13), NAMESPACE::make_pair(12, 12))->first << std::endl;
		std::cout << "insert 12 alors que deja cree = " << (map.insert(NAMESPACE::make_pair(12, 12)).second ? "TRUE" : "FALSE") << std::endl;
		std::cout << std::endl;


		//CAPACITY
		std::cout << c.g << "TEST CAPACITY" << c.rt << std::endl;
		std::cout << "Is map empty ? " << (map.empty() ? "TRUE" : "FALSE") << std::endl;
		std::cout << "Map size ? " << map.size() << std::endl;
		std::cout << "Map max::size ? " << map.max_size() << std::endl;
		std::cout << std::endl;

		//COUNT
		std::cout << c.g << "TEST COUNT" << c.rt << std::endl;
		std::cout << "15 is in map: " << (map.count(15) ? "TRUE" : "FALSE") << std::endl;
		std::cout << "21 is in map: " << (map.count(21) ? "TRUE" : "FALSE") << std::endl;

		std::cout << std::endl << c.m << "Les iterateurs de l'arbre" << c.rt << std::endl;
		NAMESPACE::map<int, int>::iterator it = map.begin();
		std::cout << "map.begin() -> map.end(): ";
		for (; it != map.end(); it++)
			std::cout << it->first << "; ";
		std::cout << std::endl << "map.end() -> map.begin(): ";
		for (; it != map.begin(); it--)
			if (it != map.end())
				std::cout << it->first << "; ";
		std::cout << std::endl;

		std::cout << std::endl << c.m << "Les reverse iterateurs de l'arbre" << c.rt << std::endl;
		NAMESPACE::map<int, int>::reverse_iterator rit = map.rend();
		std::cout << "map.rend() -> map.rbegin(): ";
		for (; rit != map.rbegin(); rit--)
			if (rit != map.rend())
				std::cout << rit->first << "; ";
		std::cout << std::endl << "map.rbegin() -> map.rend(): ";
		for (; rit != map.rend(); rit++)
			std::cout << rit->first << "; ";
		std::cout << std::endl << std::endl;

		//AT
		std::cout << c.g << "TEST AT" << c.rt << std::endl;
		try
		{
			std::cout << map.at(3) << std::endl;
			std::cout << map.at(21) << std::endl;
		}
		catch ( std::exception & e )
		{
			std::cout << e.what() << std::endl;
		}

		//FIND
		std::cout << c.g << "TEST FIND" << c.rt << std::endl;
		std::cout << map.find(3)->second << std::endl;
		if (map.find(21) != map.end())
			std::cout << map.find(21)->second << std::endl;
		else
			std::cout << "map::find element not found" << std::endl;
		std::cout << std::endl;

		//VALUE_COMP
		std::cout << c.g << "TEST VALUE_COMPARE" << c.rt << std::endl;
		if (map.value_comp()(NAMESPACE::make_pair(2, 2), NAMESPACE::make_pair(3, 3)))
			std::cout << "Fonction value_comp() 2;2 < 3;3" << std::endl;
		else
			std::cout << "Fonction value_comp() 3;3 > 2;2" << std::endl;
		//KEY_COMP
		std::cout << c.g << "TEST KEY_COMPARE" << c.rt << std::endl;
		if (map.key_comp()(3, 2))
			std::cout << "Fonction key_comp() 3 > 2" << std::endl;
		else
			std::cout << "Fonction key_comp() 2 < 3" << std::endl;

		std::cout << std::endl;
		//LOWER_BOUND
		std::cout << c.g << "TEST LOWER_BOUND" << c.rt << std::endl;
		if (map.lower_bound(10) != map.end())
			std::cout << map.lower_bound(10)->first << std::endl;
		else
			std::cout << "map::lower_bound element not found" << std::endl;
		if (map.lower_bound(21) != map.end())
			std::cout << map.lower_bound(21)->first << std::endl;
		else
			std::cout << "map::lower_bound element not found" << std::endl;
		if (map.lower_bound(-3) != map.end())
			std::cout << map.lower_bound(-3)->first << std::endl;
		else
			std::cout << "map::lower_bound element not found" << std::endl;

		std::cout << std::endl;
		//UPPER_BOUND
		std::cout << c.g << "TEST UPPER BOUND" << c.rt << std::endl;
		if (map.upper_bound(10) != map.end())
			std::cout << map.upper_bound(10)->first << std::endl;
		else
			std::cout << "map::upper_bound element not found" << std::endl;
		if (map.upper_bound(21) != map.end())
			std::cout << map.upper_bound(21)->first << std::endl;
		else
			std::cout << "map::upper_bound element not found" << std::endl;
		if (map.upper_bound(-3) != map.end())
			std::cout << map.upper_bound(-3)->first << std::endl;
		else
			std::cout << "map::upper_bound element not found" << std::endl;

		std::cout << std::endl;
		//EQUAL BOUND
		std::cout << c.g << "TEST EQUAL RANGE" << c.rt << std::endl;
		{
			NAMESPACE::pair<NAMESPACE::map<int, int>::iterator, NAMESPACE::map<int, int>::iterator>	p1 = map.equal_range(-1);
			if (p1.first == map.begin())
				std::cout << "p1.first is iterator to first not-less than -1" << std::endl;
			else
				std::cout << "unexpected p1.first" << std::endl;
			NAMESPACE::pair<NAMESPACE::map<int, int>::iterator, NAMESPACE::map<int, int>::iterator>	p2 = map.equal_range(5);
			if (p2.first == map.begin())
				std::cout << "p2.first is iterator to first not-less than 5" << std::endl;
			else
				std::cout << "unexpected p2.first" << std::endl;
			NAMESPACE::pair<NAMESPACE::map<int, int>::iterator, NAMESPACE::map<int, int>::iterator>	p3 = map.equal_range(15);
			if (p3.first == map.begin())
				std::cout << "p3.first is iterator to first not-less than 15" << std::endl;
			else
				std::cout << "unexpected p3.first" << std::endl;
		}
		std::cout << std::endl;

		//ERASE WITH POSITION ITERATOR
		std::cout << c.g << "TEST ERASE WITH POSITION ITERATOR" << c.rt << std::endl;
		std::cout << "erase position 10 -> ";
		map.erase(map.find(10));
		if (map.find(10) != map.end())
			std::cout << "key 10 non erase" << std::endl;
		else
			std::cout << "key 10 erased" << std::endl;
		std::cout << std::endl;
	}
}

//SET
void	doset( color c )
{
	NAMESPACE::vector<int>	v;
	for (size_t i = 0; i < 20; i++)
		v.push_back(i);
	std::random_shuffle(v.begin(), v.end());
	NAMESPACE::vector<int>	v2(v);
	//Creation et affichage arbre binaire
	{
		std::cout << c.y << "-----------SET------------" << c.rt << std::endl << std::endl;
		NAMESPACE::set<int>		set;

		//CAPACITY
		std::cout << c.g << "TEST CAPACITY" << c.rt << std::endl;
		std::cout << "Is set empty ? " << (set.empty() ? "TRUE" : "FALSE") << std::endl;
		std::cout << "Set size ? " << set.size() << std::endl;
		std::cout << "Set max::sisze ? " << set.max_size() << std::endl;
		std::cout << std::endl;

		//FILLING
		std::cout << c.g << "TEST INSERT" << c.rt << std::endl;
		for (size_t i = 0; i < 20; i++)
		{
			if (v[i] != 12)
				std::cout << "v[i] = " << v[i] << " -> " << *set.insert(v[i]).first << "; ";
		}
		std::cout << std::endl;

		{
			//COPY WITH ITERATORS
			std::cout << c.g << "TEST COPY WITH ITERATORS" << c.rt << std::endl;
			NAMESPACE::set<int>		set2;
			set2.insert(set.begin(), set.end());
			std::cout << "set2 size ? " << set2.size() << std::endl;
			std::cout << "set content : ";
			for (NAMESPACE::set<int>::iterator it = set.begin(); it != set.end(); it++)
				std::cout << *it << "; ";
			std::cout << std::endl << std::endl; 
		}

		//INSERT WITH POSITION
		std::cout << c.g << "TEST INSERT WITH POSITION" << c.rt << std::endl;
		std::cout << "insert 12 a position 12 = " << *set.insert(set.find(13), v[12]) << std::endl;
		std::cout << "insert 12 a position 12 = " << *set.insert(set.find(13), v[12]) << std::endl;
		std::cout << "insert 12 alors que deja cree = " << (set.insert(v[12]).second ? "TRUE" : "FALSE") << std::endl;
		std::cout << std::endl;


		//CAPACITY
		std::cout << c.g << "TEST CAPACITY" << c.rt << std::endl;
		std::cout << "Is set empty ? " << (set.empty() ? "TRUE" : "FALSE") << std::endl;
		std::cout << "set size ? " << set.size() << std::endl;
		std::cout << "set max::size ? " << set.max_size() << std::endl;
		std::cout << std::endl;

		//COUNT
		std::cout << c.g << "TEST COUNT" << c.rt << std::endl;
		std::cout << "15 is in set: " << (set.count(15) ? "TRUE" : "FALSE") << std::endl;
		std::cout << "21 is in set: " << (set.count(21) ? "TRUE" : "FALSE") << std::endl;

		std::cout << std::endl << c.m << "Les iterateurs de l'arbre" << c.rt << std::endl;
		NAMESPACE::set<int>::iterator it = set.begin();
		std::cout << "set.begin() -> set.end(): ";
		for (; it != set.end(); it++)
			std::cout << *it << "; ";
		std::cout << std::endl << "set.end() -> set.begin(): ";
		for (; it != set.begin(); it--)
			if (it != set.end())
				std::cout << *it << "; ";
		std::cout << std::endl;

		std::cout << std::endl << c.m << "Les reverse iterateurs de l'arbre" << c.rt << std::endl;
		NAMESPACE::set<int>::reverse_iterator rit = set.rend();
		std::cout << "set.rend() -> set.rbegin(): ";
		for (; rit != set.rbegin(); rit--)
			if (rit != set.rend())
				std::cout << *rit << "; ";
		std::cout << std::endl << "set.rbegin() -> set.rend(): ";
		for (; rit != set.rend(); rit++)
			std::cout << *rit << "; ";
		std::cout << std::endl << std::endl;

		//FIND
		std::cout << c.g << "TEST FIND" << c.rt << std::endl;
		std::cout << *set.find(3) << std::endl;
		if (set.find(21) != set.end())
			std::cout << *set.find(21) << std::endl;
		else
			std::cout << "set::find element not found" << std::endl;
		std::cout << std::endl;

		//VALUE_COMP
		std::cout << c.g << "TEST VALUE_COMPARE" << c.rt << std::endl;
		if (set.value_comp()(v[2], v[2]))
			std::cout << "Fonction value_comp() 2;2 < 3;3" << std::endl;
		else
			std::cout << "Fonction value_comp() 3;3 > 2;2" << std::endl;
		//KEY_COMP
		std::cout << c.g << "TEST KEY_COMPARE" << c.rt << std::endl;
		if (set.key_comp()(3, 2))
			std::cout << "Fonction key_comp() 3 > 2" << std::endl;
		else
			std::cout << "Fonction key_comp() 2 < 3" << std::endl;

		std::cout << std::endl;
		//LOWER_BOUND
		std::cout << c.g << "TEST LOWER_BOUND" << c.rt << std::endl;
		if (set.lower_bound(10) != set.end())
			std::cout << *set.lower_bound(10) << std::endl;
		else
			std::cout << "set::lower_bound element not found" << std::endl;
		if (set.lower_bound(21) != set.end())
			std::cout << *set.lower_bound(21) << std::endl;
		else
			std::cout << "set::lower_bound element not found" << std::endl;
		if (set.lower_bound(-3) != set.end())
			std::cout << *set.lower_bound(-3) << std::endl;
		else
			std::cout << "set::lower_bound element not found" << std::endl;

		std::cout << std::endl;
		//UPPER_BOUND
		std::cout << c.g << "TEST UPPER BOUND" << c.rt << std::endl;
		if (set.upper_bound(10) != set.end())
			std::cout << *set.upper_bound(10) << std::endl;
		else
			std::cout << "set::upper_bound element not found" << std::endl;
		if (set.upper_bound(21) != set.end())
			std::cout << *set.upper_bound(21) << std::endl;
		else
			std::cout << "set::upper_bound element not found" << std::endl;
		if (set.upper_bound(-3) != set.end())
			std::cout << *set.upper_bound(-3) << std::endl;
		else
			std::cout << "set::upper_bound element not found" << std::endl;

		std::cout << std::endl;
		//EQUAL BOUND
		std::cout << c.g << "TEST EQUAL RANGE" << c.rt << std::endl;
		{
			NAMESPACE::pair<NAMESPACE::set<int>::iterator, NAMESPACE::set<int>::iterator>	p1 = set.equal_range(-1);
			if (p1.first == set.begin())
				std::cout << "p1.first is iterator to first not-less than -1" << std::endl;
			else
				std::cout << "unexpected p1.first" << std::endl;
			NAMESPACE::pair<NAMESPACE::set<int>::iterator, NAMESPACE::set<int>::iterator>	p2 = set.equal_range(5);
			if (p2.first == set.begin())
				std::cout << "p2.first is iterator to first not-less than 5" << std::endl;
			else
				std::cout << "unexpected p2.first" << std::endl;
			NAMESPACE::pair<NAMESPACE::set<int>::iterator, NAMESPACE::set<int>::iterator>	p3 = set.equal_range(15);
			if (p3.first == set.begin())
				std::cout << "p3.first is iterator to first not-less than 15" << std::endl;
			else
				std::cout << "unexpected p3.first" << std::endl;
		}
		std::cout << std::endl;

		//ERASE WITH POSITION ITERATOR
		std::cout << c.g << "TEST ERASE WITH POSITION ITERATOR" << c.rt << std::endl;
		std::cout << "erase position 10 -> ";
		set.erase(set.find(10));
		if (set.find(10) != set.end())
			std::cout << "key 10 non erase" << std::endl;
		else
			std::cout << "key 10 erased" << std::endl;
		std::cout << std::endl;
	}
	{
		NAMESPACE::set<int>	st;

		NAMESPACE::set<int>::const_iterator ite = st.begin();
		//		*ite = 42; // < -- error
		std::cout << std::endl;
		(void)ite;
	}
	{
		NAMESPACE::set<int> const st;
		NAMESPACE::set<int>::iterator it = st.begin(); // <-- no error, actually ! set allows for const_iterator => iterator conversion

		(void)it;
	}
}

//VECTOR
void	dovector( color c )
{
	std::cout << c.y << "-----------VECTOR------------" << c.rt << std::endl << std::endl;
	//Constructeur par defaut
	NAMESPACE::vector<int> c1;
	std::cout << c.g << "TEST CAPACITY" << c.rt << std::endl;
	std::cout << "c1 max_size = " << c1.max_size() << std::endl;
	std::cout << "c1 Empty: " << (c1.empty() ? "true" : "false") << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << c.b << "push(1) on c1" << c.rt << std::endl; 
	c1.push_back(1);
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << c.b << "push(2) on c1" << c.rt << std::endl; 
	c1.push_back(2);
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << c.b << "push(3) on c1" << c.rt << std::endl; 
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
	std::cout << std::endl << c.m << "TEST constructeur par iterator" << c.rt << std::endl;
	NAMESPACE::vector<int> c4(c1.begin() + 1, c1.end());
	std::cout << "c4 size = " << c4.size() << std::endl;
	std::cout << "c4 capacity = " << c4.capacity() << std::endl;
	for (int i = 0; i < 2; i++)
	{
		std::cout << " --> c1[" << i << "] = " << c1[i] << std::endl;
		std::cout << " --> c4[" << i << "] = " << c4[i] << std::endl;
	}
	std::cout << std::endl;

	//ASSIGN
	//constructeur avec infos
	{
		std::cout << std::endl << c.m << "TEST constructeur avec infos" << c.rt << std::endl;
		NAMESPACE::vector<int> c3(static_cast<size_t>(30), 20);
		std::cout << "c3 size = " << c3.size() << std::endl;
		std::cout << "c3 capacity = " << c3.capacity() << std::endl;
		std::cout << std::endl << c.g << "TEST ASSIGN" << c.b << std::endl;
		for (int i = 3; i < 11; i++)
		{
			std::cout << "push(" << i << ") on c1" << std::endl; 
			c1.push_back(i);
		}
		std::cout << c.rt << std::endl;
		for (int i = 0; i < 10; i++)
			std::cout << " --> c1[" << i << "] = " << c1[i] << std::endl;
		std::cout << "c1 size = " << c1.size() << std::endl;
		std::cout << "c1 capacity = " << c1.capacity() << std::endl;
		std::cout << c.b << "Assign avec 5 x 2" << c.rt << std::endl;
		c1.assign(static_cast<size_t>(5), 2);
		for (int i = 0; i < 10; i++)
			std::cout << " --> c1[" << i << "] = " << c1[i] << std::endl;
		std::cout << "c1 size = " << c1.size() << std::endl;
		std::cout << "c1 capacity = " << c1.capacity() << std::endl;

		//RESERVE
		std::cout << std::endl << c.g << "TEST RESERVE" << c.rt << std::endl;
		std::cout << c.b << "c1 reserve(20)" << c.rt << std::endl;
		c1.reserve(20);
		for (int i = 0; i < 10; i++)
			std::cout << " --> c1[" << i << "] = " << c1[i] << std::endl;
		std::cout << "c1 size = " << c1.size() << std::endl;
		std::cout << "c1 capacity = " << c1.capacity() << std::endl;
		std::cout << std::endl;
		for (int i = 0; i < 7; i++)
			std::cout << " --> c3[" << i << "] = " << c3[i] << std::endl;
		std::cout << "c3 size = " << c3.size() << std::endl;
		std::cout << "c3 capacity = " << c3.capacity() << std::endl;
		std::cout << std::endl << c.b << "Assign avec iterators c3.begin et c3.begin+3" << c.rt << std::endl;
		c1.assign(c3.begin(), c3.begin() + 3);
		for (int i = 0; i < 7; i++)
			std::cout << " --> c1[" << i << "] = " << c1[i] << std::endl;
		std::cout << "c1 size = " << c1.size() << std::endl;
		std::cout << "c1 capacity = " << c1.capacity() << std::endl;
		std::cout << std::endl;
	}

	//ERASE
	{
		std::cout << c.g << "TEST ERASE" << c.rt << std::endl;
		std::cout << c.b << "Erase avec c2 = 012346789" << c.rt << std::endl;
		NAMESPACE::vector<int> c2;
		size_t	size = 10;
		for (size_t i = 0; i < size; i++)
		{
			c2.push_back(i);
			std::cout << " --> c2[" << i << "] = " << c2[i] << std::endl;
		}
		std::cout << c.b << "c2.erase begin() + 2" << c.rt << std::endl;
		c2.erase(c2.begin() + 2);
		for (size_t i = 0; i < c2.size(); i++)
			std::cout << " --> c2[" << i << "] = " << c2[i] << std::endl;
		std::cout << c.b << "c2.erase begin + 2 to begin + 4" << c.rt << std::endl;
		c2.erase(c2.begin() + 2, c2.begin() + 4);
		for (size_t i = 0; i < c2.size(); i++)
			std::cout << " --> c2[" << i << "] = " << c2[i] << std::endl;
		std::cout << c.b << "c2.erase begin() to end()" << c.rt << std::endl;
		c2.erase(c2.begin(), c2.end());
		for (size_t i = 0; i < c2.size(); i++)
			std::cout << " --> c2[" << i << "] = " << c2[i] << std::endl;
		std::cout << std::endl << std::endl;
	}

	//INSERT
	{
		std::cout << c.g << "TEST INSERT" << c.rt << std::endl;
		std::cout << c.b << "insert avec c2 = 012346789" << c.rt << std::endl;
		NAMESPACE::vector<int> c2(5);
		size_t	size = 5;
		for (size_t i = 0; i < size; i++)
		{
			c2[i] = i;
			c2.push_back(i + 5);
		}
		std::cout << c2 << " et c2.capacity() = " << c2.capacity() << " et size = " << c2.size() << std::endl;
		c2.insert(c2.begin() + 2, 5);
		std::cout << c.b << "c2.insert(begin() + 2, 5): " << c.rt << c2 << std::endl;
		std::cout << "c2.capacity() = " << c2.capacity() << " et size = " << c2.size() << std::endl;
		c2.insert(c2.end(), 100);
		std::cout << c.b << "c2.insert(end(), 100): " << c.rt << c2 << std::endl;
		std::cout << "c2.capacity() = " << c2.capacity() << " et size = " << c2.size() << std::endl;

		std::cout << std::endl << c.m << "Creation d'un vector avec iterators begin + 2 / end - 2 de c2" << c.rt << std::endl;
		NAMESPACE::vector<int> c5(c2.begin() + 2, c2.end() - 2);
		std::cout << c5 << std::endl;
		std::cout << "c5.capacity() = " << c5.capacity() << " et size = " << c5.size() << std::endl;
		std::cout << std::endl << c.b << "Insertion a c5[1] de c2[5] a c2[20]" << c.rt << std::endl;
		c5.insert(c5.begin() + 1, c2.begin() + 5, c2.begin() + 20);
		std::cout << c5 << std::endl;
		std::cout << "c5.capacity() = " << c5.capacity() << " et size = " << c5.size() << std::endl;
		std::cout << std::endl;

		std::cout << c.b << "c2.insert(c2.end() - 3, 10, -2): " << c.rt << c2 << std::endl;
		c2.insert(c2.end() - 3, static_cast<size_t>(10), static_cast<const int>(-2));

		std::cout << c.b <<  "c2.insert(c2.end(), 2, 100): " << c.rt << c2 << std::endl;
		c2.insert(c2.end(), static_cast<size_t>(100), static_cast<const int>(100));

		std::cout << std::endl << c.m << "Creation d'un vector avec iterators begin + 2 / end - 2 de c2" << c.rt << std::endl;
		NAMESPACE::vector<int> c3(c2.begin() + 2, c2.end() - 2);
		std::cout << c3 << std::endl;
		std::cout << "c3.capacity() = " << c3.capacity() << " et size = " << c3.size() << std::endl;

		std::cout << std::endl << c.m << "Creation d'un vector NULL puis association de c3 par operator =" << c.rt << std::endl;
		NAMESPACE::vector<int> c4 = c3;
		std::cout << c4 << std::endl;
		std::cout << "c4.capacity() = " << c4.capacity() << " et size = " << c4.size() << std::endl;
		std::cout << std::endl << c.b << "C4 = C2" << c.rt << std::endl;
		c4 = c2;
		std::cout << c4 << std::endl;
		std::cout << "c4.capacity() = " << c4.capacity() << " et size = " << c4.size() << std::endl;

		//Test avec throw erreur car pos < 0
		try {
			std::cout << std::endl << c.b << "Insertion a c5[-1] de c2[20] a c2[10]" << c.rt << std::endl;
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
		std::cout << c.g << "TEST SWAP" << c.rt << std::endl;
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
		std::cout << c.b << "swap a1 et a2" << c.rt << std::endl;
		a1.swap(a2);
		std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
		std::cout << "a1.capacity = " << a1.capacity() << " et a1.size = " << a1.size() << std::endl;
		std::cout << "a2.capacity = " << a2.capacity() << " et a2.size = " << a2.size() << std::endl;
		std::cout << std::endl;
	}

	//RESIZE
	{
		std::cout << c.g << "TEST RESIZE" << c.rt << std::endl;
		NAMESPACE::vector<int> vc;

		vc.push_back(1);
		vc.push_back(2);
		vc.push_back(3);
		std::cout << c.m << "Le vector contient: " << c.rt << vc << std::endl;

		vc.resize(5, 3);
		std::cout << c.b << "Apres resize up a 5 (initializer = 3): " << c.rt << vc << std::endl;

		vc.resize(2, 2);
		std::cout << c.b << "Apres resize down a 2 (initializer = 2): " << c.rt << vc << std::endl;

		vc.resize(7, 4);
		std::cout << c.b << "Apres resize up a 7 (initializer = 4): " << c.rt << vc << std::endl;

		vc.resize(10, 100);
		std::cout << c.b << "Apres resize up a 10 (initializer = 4): " << c.rt << vc << std::endl;
		std::cout << std::endl;
	}

	//AT
	{
		std::cout << c.g << "TEST AT" << c.rt << std::endl;
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

	std::cout << c.m << "creation de c2 par copie de c1" << c.rt << std::endl << std::endl;
	//constructeur par copie
	NAMESPACE::vector<int> c2(c1);
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c2 capacity = " << c2.capacity() << std::endl;
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "c2 Empty: " << (c2.empty() ? "true" : "false") << std::endl;
	std::cout << c.b << "push(5) on c2" << c.rt << std::endl; 
	c2.push_back(5);
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << c.b << "pop() on c2" << c.rt << std::endl;
	c2.pop_back();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << c.b << "pop() on c2" << c.rt << std::endl;
	c2.pop_back();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << c.b << "pop() on c2" << c.rt << std::endl;
	c2.pop_back();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << c.b << "pop() on c2" << c.rt << std::endl;
	c2.pop_back();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << std::endl;

	std::cout << c.m << "Operators avec c1 == c2" << c.rt << std::endl;
	//surcharge d'operateur =
	c2 = c1;
	std::cout << "c1 capacity = " << c1.capacity() << std::endl;
	std::cout << "c2 capacity = " << c2.capacity() << std::endl;
	compare(c1, c2);

	std::cout << c.m << "Operators avec c1 > c2" << c.rt << std::endl;
	c2.pop_back();
	compare(c1, c2);

	std::cout << c.m << "Operators avec c1 < c2" << c.rt << std::endl;
	c2.push_back(42);
	compare(c1, c2);

	std::cout << c.m << "Operators avec c1 == c2" << c.rt << std::endl;
	c2.pop_back();
	c2.push_back(2);
	compare(c1, c2);
	std::cout << std::endl;

	//REVERSE ITERATORS
	{
		std::cout << c.g << "TEST REVERSE ITERATOR" << c.rt << std::endl;
		NAMESPACE::vector<int> c2(5);
		size_t	size = 5;
		for (size_t i = 0; i < size; i++)
		{
			c2[i] = i;
			c2.push_back(i + 5);
		}
		std::cout << c2 << " et c2.capacity() = " << c2.capacity() << " et size = " << c2.size() << std::endl;

		NAMESPACE::reverse_iterator<NAMESPACE::vector<int>::iterator>	rev_ite = c2.rbegin();
		NAMESPACE::reverse_iterator<NAMESPACE::vector<int>::iterator>	rev_it = c2.rend();
		std::cout << c.m << "creation reverse iterator rbegin = " << c.rt << *rev_ite << std::endl;
		std::cout << c.m << "creation reverse iterator rend = " << c.rt << *rev_it << std::endl;
		std::cout << c.b << std::endl << "comparaison de rev_ite et rev_it" << c.rt << std::endl;
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
void	dostack( color c )
{
	std::cout << c.y << "-----------SWAP------------" << c.rt << std::endl << std::endl;
	std::cout << c.m << "Creation stack<int> c1" << c.rt << std::endl << std::endl;
	NAMESPACE::stack<int> c1;
	std::cout << "c1 Empty: " << (c1.empty() ? "true" : "false") << std::endl;
	std::cout << c.b << "push(5) on c1" << c.rt << std::endl; 
	c1.push(5);
	std::cout << c.b << "push(2) on c1" << c.rt << std::endl; 
	c1.push(2);
	std::cout << "c1 size = " << c1.size() << std::endl;

	std::cout << std::endl << c.m << "creation de c2 par copie de c1" << c.rt << std::endl << std::endl;
	NAMESPACE::stack<int> c2(c1);
	std::cout << "c2 Empty: " << (c2.empty() ? "true" : "false") << std::endl;
	std::cout << c.b << "push(5) on c2" << c.rt << std::endl; 
	c2.push(5);
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << c.b << "pop() on c2" << c.rt << std::endl;
	c2.pop();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << c.b << "pop() on c2" << c.rt << std::endl;
	c2.pop();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << c.b << "pop() on c2" << c.rt << std::endl;
	c2.pop();
	std::cout << "c2 size = " << c2.size() << std::endl;
	std::cout << c.b << "pop() on c2" << c.rt << std::endl;
	//	c2.pop();
	//	std::cout << "c2 size = " << c2.size() << std::endl;
	//	std::cout << std::endl;

	//	Valgrind error parce que pas protege dans std::stack donc pas non plus dans la mienne.
	//	std::cout << "c2 top() = " << c2.top() << std::endl;
	//	NAMESPACE::stack<int>	r1;
	//	std::cout << r1.top() << std::endl;
	std::cout << "c1 top() = " << c1.top() << std::endl;
	std::cout << std::endl;

	std::cout << c.m << "Operators avec c1 == c2" << c.rt << std::endl;
	c2 = c1;
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c2 size = " << c2.size() << std::endl;
	compare(c1, c2);

	std::cout << c.m << "Operators avec c1 > c2" << c.rt << std::endl;
	std::cout << c.b << "pop on c2" << c.rt << std::endl; 
	c2.pop();
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c2 size = " << c2.size() << std::endl;
	compare(c1, c2);

	std::cout << c.m << "Operators avec c1 < c2" << c.rt << std::endl;
	std::cout << c.b << "push(2) on c2" << c.rt << std::endl; 
	c2.push(2);
	std::cout << c.b << "push(2) on c2" << c.rt << std::endl; 
	c2.push(2);
	std::cout << "c1 size = " << c1.size() << std::endl;
	std::cout << "c2 size = " << c2.size() << std::endl;
	compare(c1, c2);
}
