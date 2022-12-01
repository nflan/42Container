/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:58:38 by nflan             #+#    #+#             */
/*   Updated: 2022/12/01 17:21:24 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <set>
#include <iostream>
// 0 = black / 1 = red

namespace ft
{
	template < class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class rbtree
	{
		public:
			typedef Key										key_type;
			typedef Key										value_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef Compare									key_compare;
			typedef Compare									value_compare;
			typedef Allocator								allocator_type;
			typedef value_type &							reference;
			typedef const value_type &						const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef typename std::set<Key>::iterator		iterator;
			typedef typename std::set<Key>::const_iterator	const_iterator;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

			struct node
			{
				public:
					node( void ): col(0), key(0), left(NULL), right(NULL), parent(NULL) {}
					node( const node & o ) { *this = o; }
					node( value_type k, const node & parent ): col(0), key(k), left(NULL), right(NULL), parent(parent) {}
					node( value_type k ): col(0), key(k), left(NULL), right(NULL), parent(NULL) {}
					~node ( void ) {}

					node & operator=( const node & o )
					{
						if (this == &o)
							return (*this);
						this->col = o.col;
						this->key = o.key;
						this->left = o.left;
						this->right = o.right;
						this->parent = o.parent;
						return (*this);
					}
					bool		col;
					value_type	key;
					node *		left;
					node *		right;
					node *		parent;
			};
			typedef std::allocator<node>					NAllocator;
			typedef node *									nodePTR;

			rbtree( void ): _root(NULL), _allocnode(NAllocator()), _alloctree(Allocator()) {}
			rbtree( const node & n ): _root(n), _allocnode(NAllocator()), _alloctree(Allocator()) {}
			rbtree( const rbtree & o ) { *this = o; }

			rbtree &	operator=( const rbtree & o )
			{
				if (this == &o)
					return (*this);
				this->_root = o._root;
				this->_allocnode = o._allocnode;
				this->_alloctree = o._alloctree;
			}

			void	insert(const value_type & k)
			{
				nodePTR	n = new node(k);
				if (!this->_root)
				{
					this->_root = n;
					return ;
				}
				n->col = 1;
				nodePTR	tmp = this->_root;
				nodePTR	temp = NULL;
				while (tmp != NULL)
				{
					temp = tmp;
					if (tmp->key == n->key)
						throw EqualException();
					else if (tmp->key < n->key)
						tmp = tmp->right;
					else
						tmp = tmp->left;
				}
				n->parent = temp;
				if (n->key < temp->key)
					temp->left = n;
				else
					temp->right = n;
				if (!n->parent)
				{
					n->col = 0;
					return;
				}
				if (!n->parent->parent)
					return;
			}
			class EqualException: public std::exception {
				virtual const char* what() const throw()
				{
					return ("Error: same values in two different nodes!");
				}
			};
			void	print( void ) { this->printHelper(this->_root, "", true); }

		private:
			nodePTR		_root;
			NAllocator	_allocnode;
			Allocator	_alloctree;

			void	_initNullNode( nodePTR nod, nodePTR parent )
			{
				nod->col = 0;
				nod->key = 0;
				nod->parent = parent;
				nod->left = NULL;
				nod->right = NULL;
			}
			void printHelper(nodePTR root, std::string indent, bool last)
			{
				if (root)
				{
					std::cout << indent;
					if (last)
					{
						std::cout << "R----";
						indent += "   ";
					}
					else
					{
						std::cout << "L----";
						indent += "|  ";
					}
					std::string sColor = root->col ? "RED" : "BLACK";
					std::cout << root->key << "(" << sColor << ")" << std::endl;
					printHelper(root->left, indent, false);
					printHelper(root->right, indent, true);
				}
			}
	/*		void	_print( const nodePTR & n, std::string sep )
			{
				if (!n)
					return ;
				if (n->right)
				{
					_print(n->right, sep += "---");
					std::cout << sep << n->key << std::endl;
				}
				if (n->left)
				{
					std::cout << sep << n->key << std::endl;
					_print(n->left, sep += "---");
				}
				std::cout << n->key << std::endl;
			}*/
	};
}

#endif
