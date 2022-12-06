/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:19:00 by nflan             #+#    #+#             */
/*   Updated: 2022/12/06 18:15:55 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <iostream>

namespace ft
{
	//LEXICOGRAPHICAL_COMPARE
	template< class InputIt1, class InputIt2 >
	bool	lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}
	template< class InputIt1, class InputIt2, class Compare >
	bool	lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	}

	//ENABLE IF
	template< bool B, class T = void >
	struct enable_if {};
	template< class T >
	struct enable_if<true, T> { typedef T	type; };

	//INTEGRAL_CONSTANT
	template< class T, T v >
	struct integral_constant
	{
			typedef T						value_type;
			typedef integral_constant<T,v>	type;
			operator value_type( void ) { return (value); }
			static const T	value = v;
	};
	template <bool B>
	struct integral_constant<bool, B>
	{
			typedef bool						value_type;
			typedef integral_constant<bool, B>	type;
			operator value_type( void ) { return (value); }
			static const bool	value = B;
	};
	template <bool val>
	bool const integral_constant<bool, val>::value;

	template <class T, T val>
	T const integral_constant<T, val>::value;

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	//IS_INTEGRAL
	template< typename >
	struct is_integral_b: ft::false_type {};
	template <class T>
	struct is_integral_b<const T> : ft::is_integral_b<T> {};
	template <class T>
	struct is_integral_b<volatile const T> : ft::is_integral_b<T>{};
	template <class T>
	struct is_integral_b<volatile T> : ft::is_integral_b<T>{};

	template<> struct is_integral_b<unsigned char> : ft::true_type {};
	template<> struct is_integral_b<unsigned short> : ft::true_type{};
	template<> struct is_integral_b<unsigned int> : ft::true_type{};
	template<> struct is_integral_b<unsigned long> : ft::true_type{};
	template<> struct is_integral_b<signed char> : ft::true_type{};
	template<> struct is_integral_b<short> : ft::true_type{};
	template<> struct is_integral_b<int> : ft::true_type{};
	template<> struct is_integral_b<long> : ft::true_type{};
	template<> struct is_integral_b<char> : ft::true_type{};
	template<> struct is_integral_b<bool> : ft::true_type{};

	template<class T>
	struct is_integral : is_integral_b<T> {};

	//IS_SAME
	template< class T, class U >
	struct is_same : ft::false_type{};
	template< class T >
	struct is_same<T, T> : ft::true_type{};

	//PAIR
	template < class T1, class T2 >
	struct pair
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			pair( void ): first(first_type()), second(second_type()) {}
			pair( const T1& x, const T2& y ): first(first_type(x)), second(second_type(y)) {}
			template< class U1, class U2 >
			pair( const pair<U1, U2>& p ): first(p.first), second(p.second) {}
			~pair( void ) {}

			pair& operator=( const pair& other )
			{
				if (this == &other)
					return (*this);
				this->first = other.first;
				this->second = other.second;
				return (*this);
			}

			first_type	first;
			second_type	second;
	};

	//MAKE_PAIR
	template < class T1, class T2 >
	ft::pair<T1, T2> make_pair( T1 t, T2 u ) { return (ft::pair<T1, T2>(t, u)); }

	//PAIR COMPARE
	template< class T1, class T2 >
	bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template< class T1, class T2 >
	bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{
		return (!(lhs == rhs));
	}
	template< class T1, class T2 >
	bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )	{ return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }
	template< class T1, class T2 >
	bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )	{ return (!(rhs < lhs)); }
	template< class T1, class T2 >
	bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )	{ return (rhs < lhs); }
	template< class T1, class T2 >
	bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )	{ return (!(lhs < rhs)); }

template<class Os, typename T, typename U>
Os& operator<<(Os& os, const ft::pair<T, U> *co) 
{
	os << "{ " << co->first << "; " << co->second;
	return os << " } ";
}
}

#endif
