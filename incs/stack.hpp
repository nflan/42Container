/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:01:56 by nflan             #+#    #+#             */
/*   Updated: 2023/01/05 11:36:39 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			explicit stack( const container_type& cont = container_type() ): c(cont) {};
			stack( const stack& other ): c(other.c) {}
			~stack() {};

			stack&	operator=( const stack& other )
			{
				if (this->c != other.c)
					this->c = other.c;
				return (*this);
			}
			value_type&			top( void )						{ return (c.back()); };
			const value_type&	top( void ) const				{ return (c.back()); };
			bool				empty( void ) const				{ return (c.empty()); };
			size_type			size( void ) const				{ return (c.size()); };
			void				push( const value_type& value )	{ c.push_back(value); };
			void				pop( void )						{ if (!c.size()) return ; c.pop_back(); };
			
			friend bool	operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs )	{ return (lhs.c == rhs.c); }
			friend bool	operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )	{ return (lhs.c != rhs.c); }
			friend bool	operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs )	{ return (lhs.c < rhs.c); }
			friend bool	operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )	{ return (!(lhs.c > rhs.c)); }
			friend bool	operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs )	{ return (lhs.c > rhs.c); }
			friend bool	operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )	{ return (!(lhs.c < rhs.c)); }

		protected:
			container_type	c;
	};
	template< class T, class Container >
	bool	operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
	template< class T, class Container >
	bool	operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
	template< class T, class Container >
	bool	operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
	template< class T, class Container >
	bool	operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
	template< class T, class Container >
	bool	operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
	template< class T, class Container >
	bool	operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs );
}

#endif
