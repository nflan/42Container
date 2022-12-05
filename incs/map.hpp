/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:58:38 by nflan             #+#    #+#             */
/*   Updated: 2022/12/05 21:29:52 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include "tools.hpp"
#include "rbtree.hpp"
//#include "miterator.hpp"
//#include "reverse_miterator.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef typename Allocator::reference				reference;
			typedef typename Allocator::const_reference			const_reference;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			typedef typename std::map<Key, T>::iterator			iterator;
			typedef typename std::map<Key, T>::const_iterator	const_iterator;
			typedef std::reverse_iterator<iterator>				reverse_iterator;
			typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

			class value_compare: std::binary_function<value_type, value_type, bool>
			{
				public:
					value_compare( void ): comp() {}
					value_compare( Compare c ): comp(c) {}
					bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
					bool operator() (const key_type& x, const value_type& y) const { return comp(x, y.first); }
					bool operator() (const value_type& x, const key_type& y) const { return comp(x.first, y); }
				protected:
					Compare	comp;
			};

			map( void ): _tree() {}
			explicit map( const Compare& comp, const Allocator& alloc = Allocator() ): _tree(NULL, comp, alloc) {}
			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator(), typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL ): _tree(NULL, comp, alloc)
			{
				for (; first != last; first++)
					this->insert(*first);
			}
			map( const map& other ) { *this = other; }
			~map() {}

			map &	operator=( const map& other )
			{
				if (this == &other)
					return (*this);
				//coder deep copy
				this->_tree = other._tree;
				return (*this);
			}
			allocator_type	get_allocator( void ) const { return (this->_tree.get_allocator()); }
			T&				at( const Key& key );
			T&				at( const key_type& k ) const;
			T&				operator[]( const Key& key );

			iterator				begin( void );
			const_iterator			begin( void ) const;
			iterator				end( void );
			const_iterator			end( void ) const;
			reverse_iterator		rbegin( void );
			const_reverse_iterator	rbegin( void ) const;
			reverse_iterator		rend( void );
			const_reverse_iterator	rend( void ) const;

			bool		empty( void ) const { return (this->begin() == this->end()); }
			size_type	size( void ) const { return (this->_distance(this->begin(), this->end())); }
			size_type	max_size( void ) const { return (this->_tree.max_size()); }

			void						clear( void ) { this->tree.clear(); }
			void	insert( const value_type& value )
			{
				return (this->_tree.insert(value));
			}
			iterator					insert( iterator pos, const value_type& value );
			template< class InputIt >
			void						insert( InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL );
			iterator					erase( iterator pos );
			iterator					erase( iterator first, iterator last );
			size_type					erase( const Key& key );
			void						swap( map& other );

			//LOOKUP
			size_type									count( const Key& key ) const;
			iterator									find( const Key& key );
			const_iterator								find( const Key& key ) const;
			std::pair<iterator,iterator>				equal_range( const Key& key );
			std::pair<const_iterator,const_iterator>	equal_range( const Key& key ) const;
			iterator									lower_bound( const Key& key );
			const_iterator								lower_bound( const Key& key ) const;
			iterator									upper_bound( const Key& key );
			const_iterator								upper_bound( const Key& key ) const;

			//OBSERVERS
			key_compare		key_comp() const { return (this->_tree.key_comp()); }
			value_compare	value_comp() const;


			void	print() { this->_tree.print(); }
			ft::rbtree<value_type, Compare, Allocator>	getTree( void ) { return (_tree); }

		private:
			ft::rbtree<value_type, Compare, Allocator>	_tree;
	};
	template< class Key, class T, class Compare, class Alloc >
	void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs ) { lhs.swap(rhs); }
	template< class Key, class T, class Compare, class Alloc >
	bool	operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename map<Key, T, Compare, Alloc>::const_iterator rt = rhs.begin();
		for (typename map<Key, T, Compare, Alloc>::const_iterator lt = lhs.begin(); lt != lhs.end(); lt++, rt++)
			if (*lt != *rt)
				return (false);
		return (true);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool	operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (!(lhs == rhs)); }
	template< class Key, class T, class Compare, class Alloc >
	bool	operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs != rhs); }
	template< class Key, class T, class Compare, class Alloc >
	bool	operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs); }
	template< class Key, class T, class Compare, class Alloc >
	bool	operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) && lhs != rhs); }
	template< class Key, class T, class Compare, class Alloc >
	bool	operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) || lhs == rhs); }

}

#endif
