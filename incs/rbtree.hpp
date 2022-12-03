/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:58:38 by nflan             #+#    #+#             */
/*   Updated: 2022/12/03 18:07:24 by nflan            ###   ########.fr       */
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
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
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
					~node ( void ) { }

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
			explicit rbtree( const Compare& comp, const Allocator& alloc = Allocator() ): _root(NULL), _compare(comp), _alloctree(alloc), _allocnode(NAllocator()) {}
			rbtree( const node & n ): _root(n), _allocnode(NAllocator()), _alloctree(Allocator()) {}
			rbtree( const rbtree & o ) { *this = o; }
			~rbtree( void ) { this->_clear(this->_root); }

			rbtree &	operator=( const rbtree & o )
			{
				if (this == &o)
					return (*this);
				this->_root = o._root;
				this->_allocnode = o._allocnode;
				this->_alloctree = o._alloctree;
			}
			allocator_type	get_allocator() const { return (this->_alloctree); }
//			T&				at( const Key& key ) { return (this->_;
//			T&				at( const key_type& k ) const;

			size_type		max_size( void ) const { return (this->_alloctree.max_size()); }
			void	insert( const value_type & k )
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
					if (tmp->key._second == n->key._second)
						throw EqualException();
					else if (tmp->key._second < n->key._second)
						tmp = tmp->right;
					else
						tmp = tmp->left;
				}
				n->parent = temp;
				if (n->key._second < temp->key._second)
					temp->left = n;
				else
					temp->right = n;
				if (!n->parent)
				{
					n->col = 0;
					return ;
				}
				if (!n->parent->parent)
					return ;
			//	this->_recolor(n);
			}

			//EXCEPTION
			class EqualException: public std::exception {
				virtual const char* what() const throw()
				{
					return ("Error: same values in two different nodes!");
				}
			};
			void	print( void ) { this->_print(this->_root, "", true); }

		private:
			nodePTR		_root;
			Compare		_compare;
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
			void	_print(nodePTR root, std::string indent, bool last)
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
					_print(root->left, indent, false);
					_print(root->right, indent, true);
				}
			}
			void	_clear(nodePTR root)
			{
				if (root)
				{
					_clear(root->left);
					_clear(root->right);
					delete (root);
				}
			}
			void	_recolor( nodePTR & n )
			{
				nodePTR	p = n->parent;
				nodePTR gp = p->parent;
				std::cout << "n = " << n << " & p = " << p << " & gp = " << gp << std::endl;
				while (p->col == 1)
				{
					if (p == gp->left)
					{
						if (gp->right && gp->right->col == 1)
						{
							gp->col = 1;
							gp->right->col = 0;
							gp->left->col = 0;
							n = gp;
						}
						else if (n == p->right)
						{
							n = p;
							this->_left_rotate(n);
						}
						else
						{
							p->col = 0;
							gp->col = 1;
							this->_right_rotate(gp);
						}
					}
					else
					{
						if (gp->left && gp->left->col == 1)
						{
							gp->col = 1;
							gp->right->col = 0;
							gp->left->col = 0;
							n = gp;
						}
						else if (n == p->left)
						{
							n = p;
							this->_right_rotate(n);
						}
						else
						{
							p->col = 0;
							gp->col = 1;
							this->_left_rotate(gp);
						}
					}
				}
				this->_root->col = 0;
			}
			void	_left_rotate( nodePTR & n )
			{
				nodePTR	p = n->parent;
				if (n->left)
				{
					n->left->parent = p;
				}
				if (!p->parent)
				{
					p->parent = n;
					this->_root = n;
				}
				else if (p == p->parent->left)
					p->parent->left = n;
				else
					p->parent->right = n;
				p->parent = n;
			}
			void	_right_rotate( nodePTR & n )
			{
				nodePTR	p = n->parent;
				if (n->right)
					p->right->parent = p;
				if (!p->parent)
				{
					p->parent = n;
					this->_root = n;
				}
				else if (p == p->parent->right)
					p->parent->right = n;
				else
					p->parent->left = n;
				p->parent = n;
			}
			void	_left_right_rot( nodePTR & n )
			{
				nodePTR	p = n->parent;
				nodePTR	gp = n->parent->parent;
				this->left_rotate(n);
				this->left_rotate(p);
				this->right_rotate(n);
				this->right_rotate(gp);
			}
			void	_right_left_rot( nodePTR & n )
			{
				nodePTR	p = n->parent;
				nodePTR	gp = n->parent->parent;
				this->right_rotate(n);
				this->right_rotate(p);
				this->left_rotate(n);
				this->left_rotate(gp);
			}
	};
}

#endif
