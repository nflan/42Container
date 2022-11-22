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

#include "iterator.hpp"

namespace ft
{
	template <typename T>
	class viterator {
		public:
			typedef T						value_type;
			typedef value_type&				reference;
			typedef const value_type&		const_reference;
			typedef value_type*				pointer;
			typedef const value_type*		const_pointer;
			typedef typename std::ptrdiff_t difference_type;
			viterator() {}
			viterator( const viterator & o ): _r(o._r) {}

			viterator &	operator=( const viterator & o )
			{
				if (this != &o)
					this->_r = o.operator->();
				return (*this);
			}
			reference	operator*( void ) const { return (*this->_r); }
			pointer		operator->( void ) const { return (this->_r); }
			reference	operator[]( difference_type b ) { return (*(_ptr + b)); };
			const_reference	operator[]( difference_type b ) const { return (*(_ptr + b)); };
			
			viterator &	operator++( void ) { ++this->_r; return (*this); }
			viterator	operator++( int ) { return (viterator(this->_r++)); }
			viterator &	operator--( void ) { --this->_r; return (*this); }
			viterator	operator--( int ) { return (viterator(this->_r--)); }
			reference	operator[]( const difference_type& n ) const { return (this->_r[n]); }
			viterator &	operator+=( const difference_type& n ) { this->_r += n; return (*this); }
			viterator	operator+( const difference_type& n ) const { return (viterator(this->_r + n)); }
			viterator &	operator-=( const difference_type& n ) { this->_r -= n; return (*this); }
			viterator	operator-( const difference_type& n) const { return (viterator(this->_r - n)); }

			pointer	base( void ) const { return (this->_r); }
			static const bool	input_iter = true;

		private:
			pointer	_r;
	};
	template<typename T>
	bool	operator!=(const viterator<T>& lhs, const viterator<T>& rhs) const { return (lhs.base() != rhs.base); }
	template<typename T>
	bool	operator==(const viterator<T>& lhs, const viterator<T>& rhs) const { return (lhs.base() == rhs.base); }
	template<typename T>
	bool	operator<(const viterator<T>& lhs, const viterator<T>& rhs) const { return (lhs.base() < rhs.base); }
	template<typename T>
	bool	operator<=(const viterator<T>& lhs, const viterator<T>& rhs) const { return (lhs.base() <= rhs.base); }
	template<typename T>
	bool	operator>(const viterator<T>& lhs, const viterator<T>& rhs) const { return (lhs.base() > rhs.base); }
	template<typename T>
	bool	operator>=(const viterator<T>& lhs, const viterator<T>& rhs) const { return (lhs.base() >= rhs.base); }
};

#endif
