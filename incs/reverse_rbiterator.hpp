/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rbiterator.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:56:52 by nflan             #+#    #+#             */
/*   Updated: 2022/12/12 19:07:36 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_RBITERATOR_HPP
#define REVERSE_RBITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <typename Iter>
	class reverse_rbiterator {
		public:
			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;

			reverse_rbiterator(): _r(Iter()) {}
			explicit reverse_rbiterator( iterator_type x ): _r(x) {}
			template< class U >
			reverse_rbiterator( const reverse_rbiterator<U>& other ): _r(other.base()) {}
			reverse_rbiterator( const pointer & o ): _r(o) {}

			template< class U >
			reverse_rbiterator &	operator=( const reverse_rbiterator<U> & o )
			{
				this->_r = o.base();
				return (*this);
			}
			reference	operator*( void ) const { reverse_rbiterator tmp(*this); tmp->_r--; return (tmp._r); }
			operator reverse_rbiterator<const Iter>( void ) { return (reverse_rbiterator<const Iter>(this->base())); }
			pointer		operator->( void ) const { reverse_rbiterator tmp(*this); tmp--; return (&(*tmp._r)); }
			reference	operator[]( difference_type n ) const { return (this->base()[-n - 1]); };
			
			reverse_rbiterator &	operator++( void ) { --(this->_r); return (*this); }
			reverse_rbiterator	operator++( int ) { reverse_rbiterator tmp(*this); (this->_r)--; return (tmp); }
			reverse_rbiterator &	operator--( void ) { ++(this->_r); return (*this); }
			reverse_rbiterator	operator--( int ) { reverse_rbiterator tmp(*this); (this->_r)++; return (tmp); }

			iterator_type	base( void ) const { return (this->_r); }
			static const bool	input_iter = true;

		protected:
			Iter	_r;
	};
	//COMPARE
	template<typename T>
	bool	operator!=(const reverse_rbiterator<T>& lhs, const reverse_rbiterator<T>& rhs) { return (lhs.base() != rhs.base()); }
	template<typename T, typename U>
	bool	operator!=(const reverse_rbiterator<T>& lhs, const reverse_rbiterator<U>& rhs) { return (lhs.base() != rhs.base()); }
	template<typename T>
	bool	operator==(const reverse_rbiterator<T>& lhs, const reverse_rbiterator<T>& rhs) { return (lhs.base() == rhs.base()); }
	template<typename T, typename U>
	bool	operator==(const reverse_rbiterator<T>& lhs, const reverse_rbiterator<U>& rhs) { return (lhs.base() == rhs.base()); }
}

#endif
