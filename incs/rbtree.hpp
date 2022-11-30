/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:58:38 by nflan             #+#    #+#             */
/*   Updated: 2022/11/30 16:18:44 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <set>

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
				private:
					bool		_col;
					value_type	_key;
					pointer		_lChild;
					pointer		_rChild;
					pointer		_parent;
			};
			typedef std::allocator<node>					NAllocator;

			void	insert(const node & n)
			{
				if (!this->_root)
					this->_root = n;

			}
		private:
			node		_root;
			NAllocator	_allocnode;
			Allocator	_alloctree;
	};
};

#endif
