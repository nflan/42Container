/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:32:18 by nflan             #+#    #+#             */
/*   Updated: 2022/11/10 17:31:26 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../incs/vector.hpp"
#include "../incs/stack.hpp"
#include <iostream>

using namespace ft;

int	main( void )
{
	::stack<int> c1;
	c1.push(5);
	std::cout << c1.size() << '\n';

	::stack<int> c2(c1);
	std::cout << c2.size() << '\n';

	return (0);
}
