/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:32:18 by nflan             #+#    #+#             */
/*   Updated: 2022/12/15 17:43:05 by nflan            ###   ########.fr       */
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
#include <sstream>
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

#ifndef	NAMESPACE
#define	NAMESPACE ft
#endif


/*template<class Os, typename T>
Os& operator<<(Os& os, const ft::vector<T>& co) 
{
	os << "{";
	for (size_t i = 0; i < co.size(); i++)
		os << ' ' << co[i];
	return os << " } ";
}*/

void	dostack();
void	dovector();
void	domap();
template< typename T >
void	compare(T c1, T c2);

struct Trunk
{
	Trunk *prev;
	std::string str;
	Trunk(Trunk *prev, std::string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

void showTrunks(Trunk *p)
{
	if (p == NULL)
		return;
	showTrunks(p->prev);
	std::cout << p->str;
}

void printnode(ft::rbtree<int, int, ft::pair<int,int> >::nodePTR & tmp)
{
	if (!tmp)
	{
		std::cout << "Invalide insert" << std::endl;
		return ;
	}
	if (!tmp->col)
		std::cout << "\033[0;90m";
	else
		std::cout << "\033[0;91m";
	std::cout << "Key : " << tmp->key << " | Val : " << tmp->key << "\033[0m" << std::endl;
}

void printTree(ft::rbtree<int, int, ft::pair<const int, int>, ft::map<int, int>::value_compare >::nodePTR root, Trunk *prev, bool isLeft)
{
	if (root->key == NULL)
		return ;
//    std::cout << "root : " << root->val.first << std::endl;
	std::string prev_str = "         ";
	Trunk *trunk = new Trunk(prev, prev_str);
	printTree(root->right, trunk, true);
	if (!prev)
		trunk->str = "—————————";
	else if (isLeft)
	{
		trunk->str = ".—————————";
		prev_str = "         |";
	}
	else
	{
		trunk->str = "`—————————";
		prev->str = prev_str;
	}
	showTrunks(trunk);
	if (root->col)
		std::cout << "\033[0;90m";
	else
		std::cout << "\033[0;91m";
	std::cout << " " << root->key << "\033[0m" << std::endl;
	if (prev)
		prev->str = prev_str;
	trunk->str = "         |";
	printTree(root->left, trunk, false);
	delete trunk;
}

int	main( int ac, char **av )
{
	srand (time(NULL));
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
			domap();
			break;
		case (3):
			return (std::cout << "Container '" << arg << "' not found" << std::endl, 1);
			break;
	}

	return (0);
}

//RBTREE
void	domap( void )
{
	{
		std::cout << "Creation d'une pair avec int(2) et std::string('oui')" << std::endl << std::endl;
		NAMESPACE::pair<int, std::string>	p = NAMESPACE::make_pair(2, "oui");
		std::cout << "Creation d'une pair avec int(4) et std::string('et alors')" << std::endl;
		NAMESPACE::pair<int, std::string>	p2 = NAMESPACE::make_pair(4, "et alors");
		std::cout << "Comparaison entre les 2 pairs" << std::endl;
		compare(p, p2);
		std::cout << std::endl;
	}

	//Creation et affichage arbre binaire STD
	{
		std::cout << "STD PART" << std::endl << std::endl;
		std::map<int, int>		map;
		std::vector<int>	v;

		//CAPACITY
		std::cout << "TEST CAPACITY" << std::endl;
		std::cout << "Is map empty ? " << (map.empty() ? "TRUE" : "FALSE") << std::endl;
		std::cout << "Map size ? " << map.size() << std::endl;
		std::cout << "Map max::sisze ? " << map.max_size() << std::endl;
		std::cout << std::endl;

		//FILLING
		for (size_t i = 0; i < 20; i++)
			v.push_back(i);
		std::random_shuffle(v.begin(), v.end());
		try
		{
			for (size_t i = 0; i < 20; i++)
				if (i != 12)
					map.insert(std::make_pair(v[i], v[i]));
		}
		catch ( std::exception & e )
		{
			std::cerr << e.what() << std::endl;
		}

		{
			//COPY WITH ITERATORS
			std::cout << "COPY WITH ITERATORS" << std::endl;
			std::map<int, int>		map2;
			map2.insert(map.begin(), map.end());
			std::cout << "Map2 size ? " << map2.size() << std::endl;
			std::cout << "Map content : ";
			for (std::map<int, int>::iterator it = map.begin(); it != map.end(); it++)
				std::cout << it->first << "; ";
			std::cout << std::endl << std::endl; 
		}


		//CAPACITY
		std::cout << "TEST CAPACITY" << std::endl;
		std::cout << "Is map empty ? " << (map.empty() ? "TRUE" : "FALSE") << std::endl;
		std::cout << "Map size ? " << map.size() << std::endl;
		std::cout << "Map max::sisze ? " << map.max_size() << std::endl;
		std::cout << std::endl;

		//COUNT
		std::cout << "15 is in std::map: " << (map.count(15) ? "TRUE" : "FALSE") << std::endl;
		std::cout << "21 is in std::map: " << (map.count(21) ? "TRUE" : "FALSE") << std::endl;
		std::cout << "Les iterateurs de l'arbre STD" << std::endl;
		std::map<int, int>::iterator it = map.begin();
		for (; it != map.end(); it++)
			std::cout << it->first << std::endl;
		for (; it != map.begin(); it--)
			if (it != map.end())
				std::cout << it->first << std::endl;

		std::cout << std::endl << "Les reverse iterateurs de l'arbre STD" << std::endl;
		std::map<int, int>::reverse_iterator rit = map.rend();
		for (; rit != map.rbegin(); rit--)
			if (rit != map.rend())
			std::cout << rit->first << std::endl;
		for (; rit != map.rend(); rit++)
				std::cout << rit->first << std::endl;
		std::cout << std::endl;

	//AT
		std::cout << "Test at STD" << std::endl;
		try
		{
			std::cout << map.at(3) << std::endl;
			std::cout << map.at(21) << std::endl;
		}
		catch ( std::exception & e )
		{
			std::cerr << e.what() << std::endl;
		}

	//FIND
		std::cout << "Test find STD" << std::endl;
		std::cout << map.find(3)->second << std::endl;
		if (map.find(21) != map.end())
			std::cout << map.find(21)->second << std::endl;
		else
			std::cout << "map::find element not found" << std::endl;
		std::cout << std::endl;

	//VALUE_COMP
		if (map.value_comp()(std::make_pair(2, 2), std::make_pair(3, 3)))
			std::cout << "Fonction STD value_comp() 2;2 < 3;3" << std::endl;
		else
			std::cout << "Fonction STD value_comp() 3;3 > 2;2" << std::endl;
	//KEY_COMP
		if (map.key_comp()(3, 2))
			std::cout << "Fonction STD value_comp() 3 > 2" << std::endl;
		else
			std::cout << "Fonction STD value_comp() 2 < 3" << std::endl;

		std::cout << std::endl;
	//LOWER_BOUND
		std::cout << "STD LOWER BOUND" << std::endl;
		if (map.lower_bound(10) != map.end())
			std::cout << map.lower_bound(10)->first << std::endl;
		else
			std::cout << "map::lower_bound element not found" << std::endl;
		if (map.lower_bound(21) != map.end())
			std::cout << map.lower_bound(21)->first << std::endl;
		else
			std::cout << "map::lower_bound element not found" << std::endl;
		if (map.upper_bound(-3) != map.end())
			std::cout << map.upper_bound(-3)->first << std::endl;
		else
			std::cout << "map::upper_bound element not found" << std::endl;

		std::cout << std::endl;
	//UPPER_BOUND
		std::cout << "STD UPPER BOUND" << std::endl;
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
		std::cout << "STD EQUAL RANGE" << std::endl;
		{
			std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator>	p1 = map.equal_range(-1);
			if (p1.first == map.begin())
				std::cout << "p1.first is iterator to first not-less than -1" << std::endl;
			else
				std::cout << "unexpected p1.first" << std::endl;
			std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator>	p2 = map.equal_range(5);
			if (p2.first == map.begin())
				std::cout << "p2.first is iterator to first not-less than 5" << std::endl;
			else
				std::cout << "unexpected p2.first" << std::endl;
			std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator>	p3 = map.equal_range(15);
			if (p3.first == map.begin())
				std::cout << "p3.first is iterator to first not-less than 15" << std::endl;
			else
				std::cout << "unexpected p3.first" << std::endl;
		}
	}

	std::cout << std::endl;
	//Creation et affichage arbre binaire FT
	{
		std::cout << "FT PART" << std::endl << std::endl;
		ft::map<int, int>		map;
		ft::vector<int>	v;

		//CAPACITY
		std::cout << "TEST CAPACITY" << std::endl;
		std::cout << "Is map empty ? " << (map.empty() ? "TRUE" : "FALSE") << std::endl;
		std::cout << "Map size ? " << map.size() << std::endl;
		std::cout << "Map max::sisze ? " << map.max_size() << std::endl;
		std::cout << std::endl;

		//FILLING
		for (size_t i = 0; i < 20; i++)
			v.push_back(i);
		std::random_shuffle(v.begin(), v.end());
		try
		{
			for (size_t i = 0; i < 20; i++)
			{
				if (i != 12)
					map.insert(ft::make_pair(v[i], v[i]));
//			std::cout << "--------------------------------------------" << std::endl;
			}
		}
		catch ( std::exception & e )
		{
			std::cerr << e.what() << std::endl;
		}
		printTree(map.getTree().getRoot(), NULL, false);

		{
			//COPY WITH ITERATORS
			std::cout << "COPY WITH ITERATORS" << std::endl;
			ft::map<int, int>		map2;
			map2.insert(map.begin(), map.end());
			std::cout << "Map2 size ? " << map2.size() << std::endl;
			std::cout << "Map content : ";
			for (ft::map<int, int>::iterator it = map.begin(); it != map.end(); it++)
				std::cout << it->first << "; ";
			std::cout << std::endl << std::endl; 
		}
		
		//INSERT WITH POSITION
		std::cout << "INSERT WITH POSITION" << std::endl;
		std::cout << "insert 12 a position + 12 = " << map.insert(map.find(11), ft::make_pair(v[12], v[12]))->first << std::endl;
		printTree(map.getTree().getRoot(), NULL, false);


		//CAPACITY
		std::cout << "TEST CAPACITY" << std::endl;
		std::cout << "Is map empty ? " << (map.empty() ? "TRUE" : "FALSE") << std::endl;
		std::cout << "Map size ? " << map.size() << std::endl;
		std::cout << "Map max::sisze ? " << map.max_size() << std::endl;
		std::cout << std::endl;

		//COUNT
		std::cout << "15 is in ft::map: " << (map.count(15) ? "TRUE" : "FALSE") << std::endl;
		std::cout << "21 is in ft::map: " << (map.count(21) ? "TRUE" : "FALSE") << std::endl;
		std::cout << std::endl;

		std::cout << "Les iterateurs de l'arbre FT" << std::endl;
		ft::map<int, int>::iterator it = map.begin();
		for (; it != map.end(); it++)
			std::cout << it->first << std::endl;
		for (; it != map.begin(); it--)
			if (it != map.end())
				std::cout << it->first << std::endl;

		std::cout << std::endl << "Les reverse iterateurs de l'arbre FT" << std::endl;
		ft::map<int, int>::reverse_iterator rit = map.rend();
		for (; rit != map.rbegin(); rit--)
			if (rit != map.rend())
				std::cout << rit->first << std::endl;
		for (; rit != map.rend(); rit++)
			std::cout << rit->first << std::endl;
		std::cout << std::endl;

		//AT
		std::cout << "Test at FT" << std::endl;
		try
		{
			std::cout << map.at(3) << std::endl;
			std::cout << map.at(21) << std::endl;
		}
		catch ( std::exception & e )
		{
			std::cerr << e.what() << std::endl;
		}
		//FIND
		std::cout << "Test find FT" << std::endl;
		std::cout << map.find(3)->second << std::endl;
		if (map.find(21) != map.end())
			std::cout << map.find(21)->second << std::endl;
		else
			std::cout << "map::find element not found" << std::endl;
		std::cout << std::endl;

	//VALUE_COMP KEY_COMP
		if (map.value_comp()(ft::make_pair(2, 2), ft::make_pair(3, 3)))
			std::cout << "Fonction FT value_comp() 2;2 < 3;3" << std::endl;
		else
			std::cout << "Fonction FT value_comp() 3;3 > 2;2" << std::endl;
	//VALUE_COMP KEY_COMP
		if (map.key_comp()(3, 2))
			std::cout << "Fonction FT value_comp() 3 > 2" << std::endl;
		else
			std::cout << "Fonction FT value_comp() 2 < 3" << std::endl;

		std::cout << std::endl;
	//LOWER_BOUND
		std::cout << "FT LOWER BOUND" << std::endl;
		if (map.lower_bound(10) != map.end())
			std::cout << map.lower_bound(10)->first << std::endl;
		else
			std::cout << "map::lower_bound element not found" << std::endl;
		if (map.lower_bound(21) != map.end())
			std::cout << map.lower_bound(21)->first << std::endl;
		else
			std::cout << "map::lower_bound element not found" << std::endl;
		if (map.upper_bound(-3) != map.end())
			std::cout << map.upper_bound(-3)->first << std::endl;
		else
			std::cout << "map::upper_bound element not found" << std::endl;

		std::cout << std::endl;
	//UPPER_BOUND
		std::cout << "FT UPPER BOUND" << std::endl;
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
		std::cout << "FT EQUAL RANGE" << std::endl;
		{
			ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator>	p1 = map.equal_range(-1);
			if (p1.first == map.begin())
				std::cout << "p1.first is iterator to first not-less than -1" << std::endl;
			else
				std::cout << "unexpected p1.first" << std::endl;
			ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator>	p2 = map.equal_range(5);
			if (p2.first == map.begin())
				std::cout << "p2.first is iterator to first not-less than 5" << std::endl;
			else
				std::cout << "unexpected p2.first" << std::endl;
			ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator>	p3 = map.equal_range(15);
			if (p3.first == map.begin())
				std::cout << "p3.first is iterator to first not-less than 15" << std::endl;
			else
				std::cout << "unexpected p3.first" << std::endl;
		}
	}
	std::cout << std::endl;
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

		ft::reverse_iterator<ft::vector<int>::iterator>	rev_ite = c2.rbegin();
		ft::reverse_iterator<ft::vector<int>::iterator>	rev_it = c2.rend();
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
