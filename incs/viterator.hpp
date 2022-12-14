/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viterator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:56:52 by nflan             #+#    #+#             */
/*   Updated: 2022/12/14 15:17:40 by nflan            ###   ########.fr       */
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
			typedef T								value_type;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;
			typedef value_type*						pointer;
			typedef const value_type*				const_pointer;
			typedef	std::random_access_iterator_tag	iterator_category;
			typedef typename std::ptrdiff_t			difference_type;
			viterator() {}
			viterator( const viterator & o ): _r(o._r) {}
			viterator( const pointer & o ): _r(o) {}

			viterator &	operator=( const viterator & o )
			{
				if (this != &o)
					this->_r = o.operator->();
				return (*this);
			}
			reference	operator*( void ) const { return (*this->_r); }
			operator viterator<const T>( void ) { return (viterator<const T>(this->_r)); }
			pointer		operator->( void ) const { return (this->_r); }
			reference	operator[]( difference_type b ) { return (*(this->_r + b)); };
			const_reference	operator[]( difference_type b ) const { return (*(this->_r + b)); };
			
			viterator &	operator++( void ) { ++this->_r; return (*this); }
			viterator	operator++( int ) { viterator tmp(*this); this->_r++; return (tmp); }
			viterator &	operator--( void ) { --this->_r; return (*this); }
			viterator	operator--( int ) { viterator tmp(*this); this->_r--; return (tmp); }
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
	//COMPARE
	template<typename T>
	bool	operator!=(const viterator<T>& lhs, const viterator<T>& rhs) { return (lhs.base() != rhs.base()); }
	template<typename T, typename U>
	bool	operator!=(const viterator<T>& lhs, const viterator<U>& rhs) { return (lhs.base() != rhs.base()); }
	template<typename T>
	bool	operator==(const viterator<T>& lhs, const viterator<T>& rhs) { return (lhs.base() == rhs.base()); }
	template<typename T, typename U>
	bool	operator==(const viterator<T>& lhs, const viterator<U>& rhs) { return (lhs.base() == rhs.base()); }
	template<typename T>
	bool	operator<(const viterator<T>& lhs, const viterator<T>& rhs) { return (lhs.base() < rhs.base()); }
	template<typename T, typename U>
	bool	operator<(const viterator<T>& lhs, const viterator<U>& rhs) { return (lhs.base() < rhs.base()); }
	template<typename T>
	bool	operator<=(const viterator<T>& lhs, const viterator<T>& rhs) { return (lhs.base() <= rhs.base()); }
	template<typename T, typename U>
	bool	operator<=(const viterator<T>& lhs, const viterator<U>& rhs) { return (lhs.base() <= rhs.base()); }
	template<typename T>
	bool	operator>(const viterator<T>& lhs, const viterator<T>& rhs) { return (lhs.base() > rhs.base()); }
	template<typename T, typename U>
	bool	operator>(const viterator<T>& lhs, const viterator<U>& rhs) { return (lhs.base() > rhs.base()); }
	template<typename T>
	bool	operator>=(const viterator<T>& lhs, const viterator<T>& rhs) { return (lhs.base() >= rhs.base()); }
	template<typename T, typename U>
	bool	operator>=(const viterator<T>& lhs, const viterator<U>& rhs) { return (lhs.base() >= rhs.base()); }
	//CALCUL
	template<typename T>
	typename viterator<T>::difference_type	operator-(const viterator<T>& lhs, const viterator<T>& rhs) { return (lhs.base() - rhs.base()); }
	template<typename T, typename U>
	typename viterator<T>::difference_type	operator-(const viterator<T>& lhs, const viterator<U>& rhs) { return (lhs.base() - rhs.base()); }
	template<typename T>
	viterator<T>	operator+(typename viterator<T>::difference_type n, const viterator<T>& lhs) { return (viterator<T>(lhs.base() + n)); }

}

#endif
