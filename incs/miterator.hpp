/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miterator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:00:52 by nflan             #+#    #+#             */
/*   Updated: 2022/12/05 12:10:15 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MITERATOR_HPP
#define MITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <typename T>
	class miterator {
		public:
			typedef T								value_type;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;
			typedef value_type*						pointer;
			typedef const value_type*				const_pointer;
			typedef	std::bidirectional_iterator_tag	iterator_category;
			typedef typename std::ptrdiff_t			difference_type;
			miterator() {}
			miterator( const miterator & o ): _r(o._r) {}
			miterator( const pointer & o ): _r(o) {}

			miterator &	operator=( const miterator & o )
			{
				if (this != &o)
					this->_r = o.operator->();
				return (*this);
			}
			reference	operator*( void ) const { return (*this->_r); }
			operator miterator<const T>( void ) { return (miterator<const T>(this->_r)); }
			pointer		operator->( void ) const { return (this->_r); }
			reference	operator[]( difference_type b ) { return (*(this->_r + b)); };
			const_reference	operator[]( difference_type b ) const { return (*(this->_r + b)); };
			
			miterator &	operator++( void ) { ++this->_r; return (*this); }
			miterator	operator++( int ) { miterator tmp(*this); this->_r++; return (tmp); }
			miterator &	operator--( void ) { --this->_r; return (*this); }
			miterator	operator--( int ) { miterator tmp(*this); this->_r--; return (tmp); }
			reference	operator[]( const difference_type& n ) const { return (this->_r[n]); }
			miterator &	operator+=( const difference_type& n ) { this->_r += n; return (*this); }
			miterator	operator+( const difference_type& n ) const { return (miterator(this->_r + n)); }
			miterator &	operator-=( const difference_type& n ) { this->_r -= n; return (*this); }
			miterator	operator-( const difference_type& n) const { return (miterator(this->_r - n)); }

			pointer	base( void ) const { return (this->_r); }
			static const bool	input_iter = true;

		private:
			pointer	_r;
	};
	//COMPARE
	template<typename T>
	bool	operator!=(const miterator<T>& lhs, const miterator<T>& rhs) { return (lhs.base() != rhs.base()); }
	template<typename T, typename U>
	bool	operator!=(const miterator<T>& lhs, const miterator<U>& rhs) { return (lhs.base() != rhs.base()); }
	template<typename T>
	bool	operator==(const miterator<T>& lhs, const miterator<T>& rhs) { return (lhs.base() == rhs.base()); }
	template<typename T, typename U>
	bool	operator==(const miterator<T>& lhs, const miterator<U>& rhs) { return (lhs.base() == rhs.base()); }
	template<typename T>
	bool	operator<(const miterator<T>& lhs, const miterator<T>& rhs) { return (lhs.base() < rhs.base()); }
	template<typename T, typename U>
	bool	operator<(const miterator<T>& lhs, const miterator<U>& rhs) { return (lhs.base() < rhs.base()); }
	template<typename T>
	bool	operator<=(const miterator<T>& lhs, const miterator<T>& rhs) { return (lhs.base() <= rhs.base()); }
	template<typename T, typename U>
	bool	operator<=(const miterator<T>& lhs, const miterator<U>& rhs) { return (lhs.base() <= rhs.base()); }
	template<typename T>
	bool	operator>(const miterator<T>& lhs, const miterator<T>& rhs) { return (lhs.base() > rhs.base()); }
	template<typename T, typename U>
	bool	operator>(const miterator<T>& lhs, const miterator<U>& rhs) { return (lhs.base() > rhs.base()); }
	template<typename T>
	bool	operator>=(const miterator<T>& lhs, const miterator<T>& rhs) { return (lhs.base() >= rhs.base()); }
	template<typename T, typename U>
	bool	operator>=(const miterator<T>& lhs, const miterator<U>& rhs) { return (lhs.base() >= rhs.base()); }
	//CALCUL
	template<typename T>
	typename miterator<T>::difference_type	operator-(const miterator<T>& lhs, const miterator<T>& rhs) { return (lhs.base() - rhs.base()); }
	template<typename T, typename U>
	typename miterator<T>::difference_type	operator-(const miterator<T>& lhs, const miterator<U>& rhs) { return (lhs.base() - rhs.base()); }
	template<typename T>
	miterator<T>	operator+(typename miterator<T>::difference_type n, const miterator<T>& lhs) { return (miterator<T>(lhs.base() + n)); }
}

#endif
