/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:05:13 by nflan             #+#    #+#             */
/*   Updated: 2022/11/17 11:15:37 by nflan            ###   ########.fr       */
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
	};
};

#endif

	//ITERATOR
/*	template< class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
	struct iterator
	{
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			
			//LegacyRandomAccessIterator
			iterator &	operator+=( difference_type n )
			{ 
				difference_type m = n;
				if (m >= 0)
					while (m--) ++this->_r;
				else
					while (m++) --this->_r;
				return (_r); 
			}
			iterator	operator+( difference_type n )
			{
				iterator	temp = this;
				return (temp += n);
			}
			iterator &	operator-=( difference_type n ) { return (this->_r += -n); }
			iterator	operator-( difference_type n )
			{
				iterator	temp = this;
				return (temp -= n);
			}
			difference_type	operator-( iterator b ) { return (b - this); }
			reference	operator[]( difference_type n ) { return (this + n); }

			bool			operator<( iterator b ) { return (b - this > 0); }
			bool			operator>( iterator b ) { return (b < this); }
			bool			operator>=( iterator b ) { return (!(this < b)); }
			bool			operator<=( iterator b ) { return (!(this > b)); }

			//LegacyBidirectionalIterator
			iterator &		operator--( void )
			{
				this->_r--;
				return (*this);
			}
			iterator &		operator--( T )
			{
				iterator	temp = *this;

				--*this;
				return (temp);
			}
			reference		operator--( iterator )
			{
				return (this->_r--);
			}
			//LegacyForwardIterator
			iterator &		operator++( void )
			{
				this->_r++;
				return (*this);
			}
			reference 		operator++( iterator )
			{
				return (this->_r++);
			}
			//LegacyIterator
			T		operator*( void ) { return (*this->r); }
			iterator &		operator++( T )
			{
				iterator	temp = *this;

				++*this;
				return (temp);
			}
			//LegacyOutputIterator
			void			operator+( pointer o ) { this->_r = o; }
			pointer &		operator++( void )
			{
				this->_r++;
				return (this);
			}
			pointer &		operator++( pointer * )
			{
				pointer	temp = this->_r;
				this->_r++;
				return (temp);
			}
			void			operator++( pointer * o )
			{
				*this->_r = o;
				this->_r++;
			}



		private:
			pointer	_r;
	};
*/	
