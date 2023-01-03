/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:49:48 by nflan             #+#    #+#             */
/*   Updated: 2023/01/03 17:16:30 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>
#include <iostream>

class color
{
	public:
		color(): bk("\033[30m"), r("\033[31m"), g("\033[32m"), y("\033[33m"), b("\033[34m"), m("\033[35m"), c("\033[36m"), w("\033[37m"), rt("\033[39m") {}
		color(color & o): bk(o.bk), r(o.r), g(o.g), y(o.y), b(o.b), m(o.m), c(o.c), w(o.w), rt(o.rt) {}
		~color() {}

		color & operator=(color & o)
		{
			(void) o;
			return (*this);
		}
		
		const std::string bk;
		const std::string r;
		const std::string g;
		const std::string y;
		const std::string b;
		const std::string m;
		const std::string c;
		const std::string w;
		const std::string rt;
};

#endif
