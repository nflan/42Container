/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:58:38 by nflan             #+#    #+#             */
/*   Updated: 2022/12/22 18:52:14 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include <set>
#include "rbtree.hpp"
#include "rbiterator.hpp"

namespace ft
{
	template < class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	struct set
	{
		public:
			typedef Key																				key_type;
			typedef Key																				value_type;
			typedef std::size_t																		size_type;
			typedef std::ptrdiff_t																	difference_type;
			typedef Compare																			key_compare;
			typedef Compare																			value_compare;
			typedef Allocator																		allocator_type;
			typedef value_type &																	reference;
			typedef const value_type &																const_reference;
			typedef typename Allocator::pointer														pointer;
			typedef typename Allocator::const_pointer												const_pointer;
			typedef typename ft::rbtree<value_type, value_compare, Allocator>						rbtree;
	//		typedef typename ft::rbiterator<value_type, rbtree>										iterator;
			typedef typename ft::rbiterator<const value_type, rbtree>								const_iterator;
			typedef const_iterator																	iterator;
			typedef typename ft::reverse_iterator<iterator>											reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>									const_reverse_iterator;

			set( void ): _tree(Compare(), Allocator()) {}
			explicit set( const Compare& comp, const Allocator& alloc = Allocator() ): _tree(comp, alloc) {}
			template< class InputIt >
			set( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator(), typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL ): _tree(first, last, comp, alloc) {}
			set( const set& other ): _tree(Compare(), Allocator()) { *this = other; }
			~set() {}

			set &	operator=( const set& other )
			{
				if (this == &other)
					return (*this);
				this->_tree = other._tree;
				return (*this);
			}
			allocator_type	get_allocator( void ) const { return (this->_tree.get_allocator()); }

			//ITERATORS
			const_iterator			begin( void ) const { return (this->_tree.begin()); }
			const_iterator			end( void ) const { return (this->_tree.end()); }
			reverse_iterator		rbegin( void ) { return (this->_tree.rbegin()); }
			const_reverse_iterator	rbegin( void ) const { return (this->_tree.rbegin()); }
			reverse_iterator		rend( void ) { return (this->_tree.rend()); }
			const_reverse_iterator	rend( void ) const { return (this->_tree.rend()); }

			//CAPACITY
			bool					empty( void ) const { return (this->_tree.empty()); }
			size_type				size( void ) const { return (this->_tree.size()); }
			size_type				max_size( void ) const { return (this->_tree.max_size()); }

			//MODIFIERS
			void						clear( void ) { this->_tree.clear(); }
			ft::pair<iterator, bool>	insert( const value_type& value ) { return (this->_tree.insert(value)); }
			iterator					insert( iterator pos, const value_type& value ) { return (this->_tree.insert(pos, value)); }
			template< class InputIt >
			void						insert( InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL ) { this->_tree.insert(first, last); }
			void						erase( iterator pos ) { return (this->_tree.erase(pos)); }
			void						erase( iterator first, iterator last ) { return (this->_tree.erase(first, last)); }
			size_type					erase( const Key& key ) { return (this->_tree.erase(key)); }
			void						swap( set& other ) { this->_tree.swap(other._tree); }

			//LOOKUP
			size_type									count( const Key& key ) const { return (this->_tree.count(key)); }
			const_iterator								find( const Key& key ) const { return (this->_tree.find(key)); }
			ft::pair<const_iterator, const_iterator>	equal_range( const key_type& key ) const { return (this->_tree.equal_range(key)); }
			const_iterator								lower_bound( const key_type& key ) const { return (this->_tree.lower_bound(key)); }
			const_iterator								upper_bound( const key_type& key ) const { return (this->_tree.upper_bound(key)); }

			//OBSERVERS
			key_compare		key_comp() const { return (Compare()); }
			value_compare	value_comp() const { return (this->_tree.value_comp()); }

		private:
			rbtree	_tree;
	};
	template< class Key, class Compare, class Alloc >
	void swap( set<Key,Compare,Alloc>& lhs, set<Key,Compare,Alloc>& rhs ) { lhs.swap(rhs); }
	template< class Key, class Compare, class Alloc >
	bool	operator==( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename set<Key, Compare, Alloc>::const_iterator rt = rhs.begin();
		for (typename set<Key, Compare, Alloc>::const_iterator lt = lhs.begin(); lt != lhs.end(); lt++, rt++)
			if (*lt != *rt)
				return (false);
		return (true);
	}
	template< class Key, class Compare, class Alloc >
	bool	operator!=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs ) { return (!(lhs == rhs)); }
	template< class Key, class Compare, class Alloc >
	bool	operator<( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs ) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs != rhs); }
	template< class Key, class Compare, class Alloc >
	bool	operator<=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs ) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs); }
	template< class Key, class Compare, class Alloc >
	bool	operator>( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs ) { return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) && lhs != rhs); }
	template< class Key, class Compare, class Alloc >
	bool	operator>=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs ) { return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) || lhs == rhs); }
}

#endif
