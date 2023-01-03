/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:05:13 by nflan             #+#    #+#             */
/*   Updated: 2023/01/03 13:34:06 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

namespace ft
{
	//ITERATOR_TRAITS
	template< class Iter >
	struct iterator_traits
	{
		public:
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::iterator_category	iterator_category;
	};
	template< class T >
	struct iterator_traits<T*>
	{
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef T *								pointer;
			typedef T &								reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};
	template< class T >
	struct iterator_traits<const T*>
	{
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef const T *						pointer;
			typedef const T &						reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};

	//REVERSE_ITERATOR
	template< class Iter >
	class reverse_iterator
	{
		public:
			typedef Iter												iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;

			reverse_iterator(): _r(Iter()) {}
			explicit reverse_iterator( iterator_type x ): _r(x) {}
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ): _r(other.base()) {}

			template< class U >
			reverse_iterator &	operator=( const reverse_iterator<U> & o )
			{
				this->_r = o.base();
				return (*this);
			}
			reference	operator*( void ) const { Iter tmp = this->_r; return (*(--tmp)); }
			operator reverse_iterator<const Iter>( void ) { return (reverse_iterator<const Iter>(this->base())); }
			pointer		operator->( void ) const { Iter	tmp = this->_r; return (&(*--tmp)); }
			reference	operator[]( difference_type n ) const { return (this->base()[-n - 1]); };
			
			reverse_iterator &	operator++( void ) { --(this->_r); return (*this); }
			reverse_iterator	operator++( int ) { reverse_iterator tmp(*this); (this->_r)--; return (tmp); }
			reverse_iterator &	operator--( void ) { ++(this->_r); return (*this); }
			reverse_iterator	operator--( int ) { reverse_iterator tmp(*this); (this->_r)++; return (tmp); }
			reverse_iterator &	operator+=( difference_type n ) { this->_r -= n; return (*this); }
			reverse_iterator	operator+( difference_type n ) const { return (reverse_iterator(this->_r - n)); }
			reverse_iterator &	operator-=( difference_type n ) { this->_r += n; return (*this); }
			reverse_iterator	operator-( difference_type n) const { return (reverse_iterator(this->_r + n)); }

			iterator_type	base( void ) const { return (this->_r); }

		protected:
			Iter	_r;
	};
	//COMPARE
	template<typename T>
	bool	operator!=(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return (lhs.base() != rhs.base()); }
	template<typename T, typename U>
	bool	operator!=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() != rhs.base()); }
	template<typename T>
	bool	operator==(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return (lhs.base() == rhs.base()); }
	template<typename T, typename U>
	bool	operator==(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() == rhs.base()); }
	template<typename T>
	bool	operator<(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return (lhs.base() > rhs.base()); }
	template<typename T, typename U>
	bool	operator<(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() > rhs.base()); }
	template<typename T>
	bool	operator<=(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return (lhs.base() >= rhs.base()); }
	template<typename T, typename U>
	bool	operator<=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() >= rhs.base()); }
	template<typename T>
	bool	operator>(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return (lhs.base() < rhs.base()); }
	template<typename T, typename U>
	bool	operator>(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() < rhs.base()); }
	template<typename T>
	bool	operator>=(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return (lhs.base() <= rhs.base()); }
	template<typename T, typename U>
	bool	operator>=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() <= rhs.base()); }
	//CALCUL
	template<typename T>
	typename reverse_iterator<T>::difference_type	operator-(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return (rhs.base() - lhs.base()); }
	template<typename T, typename U>
	typename reverse_iterator<T>::difference_type	operator-(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (rhs.base() - lhs.base()); }
	template<typename T>
	reverse_iterator<T>	operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T>& lhs) { return (reverse_iterator<T>(lhs.base() - n)); }
}

#endif
