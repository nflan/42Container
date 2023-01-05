/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:32:18 by nflan             #+#    #+#             */
/*   Updated: 2023/01/05 10:55:09 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/vector.hpp"
#include "../incs/iterator.hpp"
#include "../incs/rbiterator.hpp"
#include "../incs/tools.hpp"
#include "../incs/rbtree.hpp"
#include "../incs/map.hpp"
#include "../incs/color.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

#ifndef	NAMESPACE
#define	NAMESPACE ft
#endif

//Surcharge operator <<
template<class Os, typename T, typename U>
Os& operator<<(Os& os, const ft::pair<T, U>* co)
{
	os << "{ " << co->first << "; " << co->second;
	return os << " } ";
}

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

void printnode(ft::rbtree<ft::pair<int,int> >::nodePTR & tmp)
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

void printTree(ft::rbtree<ft::pair<const int, int>, ft::map<int, int>::value_compare >::nodePTR root, Trunk *prev, bool isLeft)
{
	if (root->key == NULL)
		return ;
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

void	printing( color c )
{
	ft::vector<int>	v;
	for (size_t i = 0; i < 20; i++)
		v.push_back(i);
	std::random_shuffle(v.begin(), v.end());

	//Creation et affichage arbre binaire FT
	{
		ft::map<int, int>		map;
		//FILLING
		std::cout << "inserting: " << std::endl;
		for (size_t i = 0; i < 20; i++)
		{
			std::cout << std::endl << c.y << "Insert: " << v[i] << c.rt << std::endl;
			map.insert(ft::make_pair(v[i], v[i]));
			printTree(map.getTree().getRoot(), NULL, false);
			std::cout << std::endl << "--------------------------------------------" << std::endl;
		}
		std::cout << std::endl;
		
		std::cout << std::endl;
		//ERASE WITH POSITION ITERATOR
		std::cout << c.y << "erase position 10" << c.rt << std::endl;
		map.erase(map.find(10));
		printTree(map.getTree().getRoot(), NULL, false);
		std::cout << std::endl << "--------------------------------" << std::endl << std::endl;
		std::cout << c.y << "erase position --end()" << c.rt << std::endl;
		map.erase(--map.end());
		printTree(map.getTree().getRoot(), NULL, false);
		std::cout << std::endl << "--------------------------------" << std::endl << std::endl;
		std::cout << c.y << "erase position ++begin()" << c.rt << std::endl;
		map.erase(++map.begin());
		printTree(map.getTree().getRoot(), NULL, false);
		std::cout << std::endl << "--------------------------------" << std::endl << std::endl;
		std::cout << c.y << "erase position begin()" << c.rt << std::endl;
		map.erase(map.begin());
		printTree(map.getTree().getRoot(), NULL, false);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
