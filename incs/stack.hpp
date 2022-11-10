/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:01:56 by nflan             #+#    #+#             */
/*   Updated: 2022/11/10 17:32:15 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <vector>
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
	template< class T, class Container = std::vector<T> > class stack
	{
		public:
			typedef T									container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			stack( const stack& other )
			{
				*this = other;
			}
			explicit stack( const Container& cont = Container() ) {(void)cont;};
			~stack() {};

			stack&	operator=( const stack& other )
			{
				if (*this != other)
					this->c = other.c;
				return (*this);
			}
			reference		top( void ){ return (*this); };
			const_reference	top( void ) const { return (*this); };
			bool			empty( void ) const { return (c ? true : false); };
			size_type		size( void ) const { return (this->c.size()); };
			void			push( const value_type& value ) { c.push(value); };
			void			pop( void ) { c.pop(); };
			
		private:
			container_type	c;
	};
	template< class T, class Container >
	bool	operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs == rhs ? true : false); };
	template< class T, class Container >
	bool	operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs != rhs ? true : false); };
	template< class T, class Container >
	bool	operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs < rhs ? true : false); };
	template< class T, class Container >
	bool	operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs <= rhs ? true : false); };
	template< class T, class Container >
	bool	operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs > rhs ? true : false); };
	template< class T, class Container >
	bool	operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs >= rhs ? true : false); };
};

#endif
