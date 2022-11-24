/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:19:00 by nflan             #+#    #+#             */
/*   Updated: 2022/11/24 12:00:45 by nflan            ###   ########.fr       */
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
	struct enable_if 
	{
	};
	template< class T >
	struct enable_if<true, T>
	{
		typedef T type;
	};

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
};

#endif
