/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:01:56 by nflan             #+#    #+#             */
/*   Updated: 2022/11/11 18:39:46 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <vector>
#include <iostream>
/*
			typedef T					value_type;
			typedef T					size_type;
			typedef value_type *		pointer;
			typedef value_type *		iterator;
			typedef value_type *		reverse_iterator;
			typedef const value_type *	const_iterator;
			typedef const value_type *	const_reverse_iterator;
			typedef value_type &		reference;
			typedef const value_type &	const_reference;
			typedef Allocator			allocator_type;*/
namespace ft
{
	template< class T, class Container >
	bool	operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );
	template< class T, class Container >
	bool	operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );
	template< class T, class Container >
	bool	operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );
	template< class T, class Container >
	bool	operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );
	template< class T, class Container >
	bool	operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );
	template< class T, class Container >
	bool	operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );
	template< class T, class Container = std::vector<T> > class stack
	{
		public:
			typedef Container							container_type;
			typedef T									value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			explicit stack( const Container& cont = Container() ): c(cont) {};
			stack( const stack& other )
			{
				*this = other;
			}
			~stack() {};

			stack&	operator=( const stack& other )
			{
				if (this->c != other.c)
				{
					Container tmp = Container(other.c);
					this->c = tmp;
				}
				return (*this);
			}
			reference		top( void ){ return (c.back()); };
			const_reference	top( void ) const { return (c.back()); };
			bool			empty( void ) const { return (c.empty()); };
			size_type		size( void ) const { return (c.size()); };
			void			push( const value_type& value ) { c.push_back(value); };
			void			pop( void ) { if (!c.size()) return ; c.pop_back(); };
			
			friend bool	operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end())); }
			friend bool	operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end())); }
			friend bool	operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end())); }
			friend bool	operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end())); }
			friend bool	operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end())); }
			friend bool	operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end())); }

		protected:
			container_type	c;
	};
	template< class InputIt1, class InputIt2 >
	bool	lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
			 return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}
	template< class InputIt1, class InputIt2, class Compare >
	bool	lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return (first1 == last1) && (first2 != last2);
	}
	template< class T, class Container >
	bool	operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );
	template< class T, class Container >
	bool	operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );// { return (lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end())); };
	template< class T, class Container >
	bool	operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );// { return (lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end())); };
	template< class T, class Container >
	bool	operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );// { return (lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end())); };
	template< class T, class Container >
	bool	operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );// { return (lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end())); };
	template< class T, class Container >
	bool	operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs );// { return (lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end())); };
};

#endif
