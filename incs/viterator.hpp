/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viterator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:56:52 by nflan             #+#    #+#             */
/*   Updated: 2022/11/17 17:30:57 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VITERATOR_HPP
#define VITERATOR_HPP

#include <iterator>
#include "iterator.hpp"

#include <iostream>

namespace ft
{
	template< class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
	class viterator {
		//	typedef std::iterator_traits<T> _Traits;
		public:
			typedef T			value_type;
			typedef Category	iterator_category;
			typedef Distance	difference_type;
			typedef Reference	reference;
			typedef Pointer		pointer;

			viterator() {}
			viterator( const viterator & o ): _r(o._r) {}

	/*		bool	isConstant() const
			{
				typedef typename	_Sequence::const_iterator const_iterator;
				return (std::__are_same<const_iterator, viterator>::__value);
			}*/

			viterator &	operator=( const viterator & o )
			{
				std::cout << "oui ?" << std::endl;
				if (this != &o)
					this->_r = o._r;
				return (*this);
			}
			reference	operator*( void ) const { return (*this->_r); }
			pointer		operator->( void ) const { return (&*this->_r); }
			
			viterator &	operator++( void ) { ++this->_r; return (*this); }
			viterator	operator++( int ) { return (tmp(this->_r++)); }
/*			viterator	operator++( int )
			{
				viterator	tmp(*this);
				++this->_r;
				return (tmp);
			}
*/			viterator &	operator--( void ) { --this->_r; return (*this); }
			viterator	operator--( int ) { return (tmp(this->_r--)); }
		//	{
		//		viterator	tmp(*this);
		//		--this->_r;
		//		return (tmp);
		//	}
			reference	operator[]( const difference_type& n ) const { return (this->_r[n]); }
			viterator &	operator+=( const difference_type& n ) { this->_r += n; return (*this); }
			viterator	operator+( const difference_type& n ) const { return (tmp(this->_r + n)); }
			viterator &	operator-=( const difference_type& n ) { this->_r -= n; return (*this); }
			viterator	operator-( const difference_type& n) const { return (tmp(this->_r - n)); }


			pointer	base( void ) const { return (this->_r); }
			

		private:
			pointer	_r;
	};
	template<typename _Iterator, typename _Sequence>
	bool	operator!=(const viterator<_Iterator, _Sequence>& lhs, const viterator<_Iterator, _Sequence>& rhs) { return (lhs.base() != rhs.base); }
};

#endif
