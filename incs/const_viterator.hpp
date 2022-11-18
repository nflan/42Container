/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_viterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:56:52 by nflan             #+#    #+#             */
/*   Updated: 2022/11/18 12:32:00 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_const_viterator_HPP
#define CONST_const_viterator_HPP

#include <iterator>
#include "iterator.hpp"

namespace ft
{
	template< class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
	class const_viterator {
//			typedef std::iterator_traits<_Iterator> _Traits;
		public:
			typedef const T			value_type;
			typedef const Category	iterator_category;
			typedef const Distance	difference_type;
			typedef const Reference	reference;
			typedef const Pointer	pointer;
		/*	typedef _Iterator							iterator_type;
			typedef typename _Traits::iterator_category	iterator_category;
			typedef typename _Traits::value_type		value_type;
			typedef typename _Traits::difference_type	difference_type;
			typedef typename _Traits::reference			reference;
			typedef typename _Traits::pointer			pointer;
*/
			const_viterator() {}
			const_viterator( const const_viterator & o ): _r(o._r) {}

	/*		bool	isConstant() const
			{
				typedef typename	_Sequence::const_iterator const_iterator;
				return (std::__are_same<const_iterator, const_viterator>::__value);
			}*/

			const_viterator &	operator=( const const_viterator & o ) { if (this != &o) this->_r = o._r; return (*this); }
			reference	operator*( void ) const { return (*this->_r); }
			pointer		operator->( void ) const { return (&*this->_r); }
			
			reference	operator[]( const difference_type& n ) const { return (this->_r[n]); }


			pointer	base( void ) const { return (this->_r); }
			

		private:
			const pointer	_r;
	};
	template<typename _Iterator, typename _Sequence>
	bool	operator!=(const const_viterator<_Iterator, _Sequence>& lhs, const const_viterator<_Iterator, _Sequence>& rhs) { return (lhs.base() != rhs.base); }
};

#endif
