/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viterator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:56:52 by nflan             #+#    #+#             */
/*   Updated: 2022/11/15 19:31:40 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VITERATOR_HPP
#define VITERATOR_HPP

namespace ft
{
	template<typename _Iterator, typename _Sequence>
	class viterator
	{
		public:
			typedef _Iterator											iterator_type;
			typedef typename std::iterator_traits<_Iterator>::iterator_category	iterator_category;
			typedef typename std::iterator_traits<_Iterator>::value_type			value_type;
			typedef typename std::iterator_traits<_Iterator>::difference_type	difference_type;
			typedef typename std::iterator_traits<_Iterator>::reference			reference;
			typedef typename std::iterator_traits<_Iterator>::pointer			pointer;

			viterator(): _r() {};
			viterator( const viterator & o )
			{
				*this = o;
			}

			viterator &	operator=( const viterator & o ) { if (this = &o) this->_r = o->_r; return (*this); }
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

			_Iterator	base( void ) const { return (this->_r); }
			

		private:
			_Iterator	_r;
	};
};

#endif
