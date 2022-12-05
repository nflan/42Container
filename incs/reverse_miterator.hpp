/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_miterator.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:56:52 by nflan             #+#    #+#             */
/*   Updated: 2022/12/05 12:19:40 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_MITERATOR_HPP
#define REVERSE_MITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <typename Iter>
	class reverse_miterator {
		public:
			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;
		/*	typedef T						value_type;
			typedef value_type&				reference;
			typedef const value_type&		const_reference;
			typedef value_type*				pointer;
			typedef const value_type*		const_pointer;
			typedef typename std::ptrdiff_t	difference_type; */
			reverse_miterator(): _r(Iter()) {}
			explicit reverse_miterator( iterator_type x ): _r(x) {}
			template< class U >
			reverse_miterator( const reverse_miterator<U>& other ): _r(other.base()) {}
			reverse_miterator( const pointer & o ): _r(o) {}

			template< class U >
			reverse_miterator &	operator=( const reverse_miterator<U> & o )
			{
				this->_r = o.base();
				return (*this);
			}
			reference	operator*( void ) const { return (*(this->_r - 1)); }
			operator reverse_miterator<const Iter>( void ) { return (reverse_miterator<const Iter>(this->base())); }
			pointer		operator->( void ) const { return (&(*(this->_r - 1))); }
			reference	operator[]( difference_type n ) const { return (this->base()[-n - 1]); };
		//	const_reference	operator[]( difference_type b ) const { return (*(this->_r + b)); };
			
			reverse_miterator &	operator++( void ) { --(this->_r); return (*this); }
			reverse_miterator	operator++( int ) { reverse_miterator tmp(*this); (this->_r)--; return (tmp); }
			reverse_miterator &	operator--( void ) { ++(this->_r); return (*this); }
			reverse_miterator	operator--( int ) { reverse_miterator tmp(*this); (this->_r)++; return (tmp); }
			reverse_miterator &	operator+=( const difference_type& n ) { this->_r -= n; return (*this); }
			reverse_miterator	operator+( const difference_type& n ) const { return (reverse_miterator(this->_r - n)); }
			reverse_miterator &	operator-=( const difference_type& n ) { this->_r += n; return (*this); }
			reverse_miterator	operator-( const difference_type& n) const { return (reverse_miterator(this->_r + n)); }

			iterator_type	base( void ) const { return (this->_r); }
			static const bool	input_iter = true;

		protected:
			Iter	_r;
	};
	//COMPARE
	template<typename T>
	bool	operator!=(const reverse_miterator<T>& lhs, const reverse_miterator<T>& rhs) { return (lhs.base() != rhs.base()); }
	template<typename T, typename U>
	bool	operator!=(const reverse_miterator<T>& lhs, const reverse_miterator<U>& rhs) { return (lhs.base() != rhs.base()); }
	template<typename T>
	bool	operator==(const reverse_miterator<T>& lhs, const reverse_miterator<T>& rhs) { return (lhs.base() == rhs.base()); }
	template<typename T, typename U>
	bool	operator==(const reverse_miterator<T>& lhs, const reverse_miterator<U>& rhs) { return (lhs.base() == rhs.base()); }
	template<typename T>
	bool	operator<(const reverse_miterator<T>& lhs, const reverse_miterator<T>& rhs) { return (lhs.base() > rhs.base()); }
	template<typename T, typename U>
	bool	operator<(const reverse_miterator<T>& lhs, const reverse_miterator<U>& rhs) { return (lhs.base() > rhs.base()); }
	template<typename T>
	bool	operator<=(const reverse_miterator<T>& lhs, const reverse_miterator<T>& rhs) { return (lhs.base() >= rhs.base()); }
	template<typename T, typename U>
	bool	operator<=(const reverse_miterator<T>& lhs, const reverse_miterator<U>& rhs) { return (lhs.base() >= rhs.base()); }
	template<typename T>
	bool	operator>(const reverse_miterator<T>& lhs, const reverse_miterator<T>& rhs) { return (lhs.base() < rhs.base()); }
	template<typename T, typename U>
	bool	operator>(const reverse_miterator<T>& lhs, const reverse_miterator<U>& rhs) { return (lhs.base() < rhs.base()); }
	template<typename T>
	bool	operator>=(const reverse_miterator<T>& lhs, const reverse_miterator<T>& rhs) { return (lhs.base() <= rhs.base()); }
	template<typename T, typename U>
	bool	operator>=(const reverse_miterator<T>& lhs, const reverse_miterator<U>& rhs) { return (lhs.base() <= rhs.base()); }
	//CALCUL
	template<typename T>
	typename reverse_miterator<T>::difference_type	operator-(const reverse_miterator<T>& lhs, const reverse_miterator<T>& rhs) { return (rhs.base() - lhs.base()); }
	template<typename T, typename U>
	typename reverse_miterator<T>::difference_type	operator-(const reverse_miterator<T>& lhs, const reverse_miterator<U>& rhs) { return (rhs.base() - lhs.base()); }
	template<typename T>
	reverse_miterator<T>	operator+(typename reverse_miterator<T>::difference_type n, const reverse_miterator<T>& lhs) { return (reverse_miterator<T>(lhs.base() - n)); }
}

#endif
