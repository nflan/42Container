/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:58:38 by nflan             #+#    #+#             */
/*   Updated: 2022/12/05 22:00:08 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <set>
#include <map>
#include <iostream>
#include "tools.hpp"
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
			typedef typename std::map<Key, Key>::iterator		iterator;
			typedef typename std::map<Key, Key>::const_iterator	const_iterator;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

			struct node
			{
				public:
					node( void ): col(0), key(NULL), left(NULL), right(NULL), parent(NULL) {}
					node( value_type k ): col(0), left(NULL), right(NULL), parent(NULL)
					{
						Allocator	al;
						key = al.allocate(1, 0);
						al.construct(key, k);
					}
					node( value_type k, const node & parent ): col(0), left(NULL), right(NULL), parent(parent)
					{
						Allocator	al;
						key = al.allocate(1, 0);
						al.construct(key, k);
					}
					node( const node & o ): col(o.col), key(o.key), left(o.left), right(o.right), parent(o.parent)
					{
						Allocator	al;
						key = al.allocate(1, 0);
						al.construct(key, *o.key);
					}
					~node ( void )
					{
						Allocator	al;
						al.destroy(this->key);
						al.deallocate(this->key, 1);
					}

					node & operator=( const node & o )
					{
						Allocator	al;
						if (this == &o)
							return (*this);
						this->col = o.col;
						if (this->key)
						{
							al.destroy(key);
							if (!o.key)
								al.deallocate(key, 1);
							else
								al.construct(key, *o.key);
						}
						else if (o.key)
						{
							this->key = al.allocate(1, 0);
							al.construct(key, *o.key);
						}
						this->left = o.left;
						this->right = o.right;
						this->parent = o.parent;
						return (*this);
					}
					bool		col;
					pointer		key;
					node *		left;
					node *		right;
					node *		parent;
			};
			typedef std::allocator<node>					NAllocator;
			typedef node *									nodePTR;

			rbtree( void ): _root(NULL), _compare(Compare()), _allocnode(NAllocator()), _alloc(Allocator()), _size(0) {}
			explicit rbtree( const Compare& comp, const Allocator& alloc = Allocator() ): _root(NULL), _compare(comp), _alloc(alloc), _allocnode(NAllocator()), _size(0) {}
			template <class InputIt>
			rbtree( InputIt first, InputIt last, const Compare & comp = Compare(), const allocator_type & alloc = allocator_type() ): _root(NULL), _compare(comp), _allocnode(NAllocator()), _alloc(alloc), _size(0)
			{
				insert(first, last);
			}
		//	rbtree( const node & n ): _root(n), _compare(Compare()), _allocnode(NAllocator()), _alloc(Allocator()), _size(0) {}
			rbtree( const rbtree & o ): _root(NULL), _compare(o._compare), _allocnode(o._allocnode), _alloc(o._alloc), _size(o._size)
			{
				this->insert(o.begin(), o.end());
			}
			~rbtree( void ) { this->_clear(this->_root); }

			rbtree &	operator=( const rbtree & o )
			{
				std::cout << "THIS WILL SEG SADGE" << std::endl;
				if (this == &o)
					return (*this);
				this->clear();
				this->_root = NULL;
				this->_allocnode = o._allocnode;
				this->_alloc = o._alloc;
				this->_compare = o._compare;
				this->_size = o._size;
				this->insert(o.begin(), o.end());
				return (*this);
			}
			allocator_type	get_allocator() const { return (this->_alloc); }
//			T&				at( const Key& key ) { return (this->_;
//			T&				at( const key_type& k ) const;

			iterator				begin( void )
			{
				nodePTR tmp = this->_root;
				if (!this->_root)
					return (iterator(this->_root, this));
				while (tmp->left)
					tmp = tmp->left;
				return (iterator(tmp, this));
			}
			const_iterator			begin( void ) const
			{
				nodePTR tmp = this->_root;
				if (!this->_root)
					return (const_iterator(this->_root, this));
				while (tmp->left)
					tmp = tmp->left;
				return (const_iterator(tmp, this));
			}
			iterator				end( void ) { return (iterator(NULL, this)); }
			const_iterator			end( void ) const { return (const_iterator(NULL, this)); }
			size_type		max_size( void ) const { return (this->_alloc.max_size()); }
			void	insert( const value_type & k )
			{
				nodePTR	n;
				n = this->_allocnode.allocate(1, 0);
				this->_allocnode.construct(n, k);
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
					if (_compare(tmp->key, n->key))
						tmp = tmp->right;
					else if (_compare(n->key, tmp->key))
						tmp = tmp->left;
					else
						throw EqualException();
				}
				n->parent = temp;
				this->_size++;
				if (_compare(n->key, temp->key))
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
			iterator					insert( iterator pos, const value_type& value )
			{
				(void)pos;
				ft::pair<iterator, bool> ret = insert(value);
				return (ret.first);
			}
			template< class InputIt >
			void						insert( InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL )
			{
				for (; first != last; first++)
					this->insert(*first);
			}

			//EXCEPTION
			class EqualException: public std::exception {
				virtual const char* what() const throw()
				{
					return ("Error: same values in two different nodes!");
				}
			};
			key_compare		key_comp() const { return (_compare); }

			void	print( void ) { this->_print(this->_root, "", true); }
		//	void	print() { printTree(this->_root, NULL, false); }
			nodePTR	getRoot() { return (this->_root); }

		private:
			nodePTR		_root;
			key_compare	_compare;
			NAllocator	_allocnode;
			Allocator	_alloc;
			size_type	_size;

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
					this->_allocnode.destroy(root);
					this->_allocnode.deallocate(root, 1);
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
						if (gp->right->col == 1)
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
						if (gp->left->col == 1)
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
