/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:58:38 by nflan             #+#    #+#             */
/*   Updated: 2022/12/01 15:22:41 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <set>

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
					node( void ): _col(0), _key(0), _left(NULL), _right(NULL), _parent(NULL) {}
					node( const node & o ) { *this = o; }
					node( value_type k, const node & parent ): _col(0), _key(k), _left(NULL), _right(NULL), _parent(parent) {}
					node( value_type k ): _col(0), _key(k), _left(NULL), _right(NULL), _parent(NULL) {}
					~node ( void ) {}

					node & operator=( const node & o )
					{
						if (this == &o)
							return (*this);
						this->_col = o._col;
						this->_key = o._key;
						this->_left = o._left;
						this->_right = o._right;
						this->_parent = o._parent;
						return (*this);
					}
				private:
					bool		_col;
					value_type	_key;
					pointer		_left;
					pointer		_right;
					pointer		_parent;
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

			void	insert(const node & n)
			{
				if (!this->_root)
				{
					this->_root = n;
					this->_root._col = 0;
					return ;
				}
				node tmp = this->_root;
				while (tmp != NULL)
				{
					if (tmp._key == n._key)
						throw std::exception("same");
					else if (tmp._key < n._key)
						tmp = tmp._right;
					else
						tmp = tmp._left;
				}
				tmp = n;
				tmp = 1;
			}

		private:
			nodePTR		_root;
			NAllocator	_allocnode;
			Allocator	_alloctree;

			void	_initNullNode( nodePTR nod, nodePTR parent )
			{
				nod->_col = 0;
				nod->_key = 0;
				nod->_parent = parent;
				nod->_left = NULL;
				nod->_right = NULL;
			}
			void	print(  )
			{
				
			}
	};
}

#endif
