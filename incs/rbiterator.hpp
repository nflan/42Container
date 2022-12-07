/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbiterator.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:00:52 by nflan             #+#    #+#             */
/*   Updated: 2022/12/07 16:25:16 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBITERATOR_HPP
#define RBITERATOR_HPP

#include <map>
#include <set>
#include "iterator.hpp"
#include "rbtree.hpp"

namespace ft
{
	template < class Key, class Type >
	class rbiterator {
		public:
			typedef Key								value_type;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;
			typedef value_type*						pointer;
			typedef const value_type*				const_pointer;
			typedef	std::bidirectional_iterator_tag	iterator_category;
			typedef typename std::ptrdiff_t			difference_type;

			rbiterator( void ): _r() {}
			rbiterator( const rbiterator & o ): _r(o._r), _type(o._type) {}
			rbiterator( const value_type & o, const Type & t ): _r(o), _type(t) {}

			rbiterator &	operator=( const rbiterator & o )
			{
				if (this != &o)
					this->_r = o.operator->();
				return (*this);
			}
			reference	operator*( void ) const { return (*this->_r->key); }
			operator rbiterator<const value_type, Type>( void ) { return (rbiterator<const value_type, Type>(this->_r)); }
			pointer		operator->( void ) const { return (*this->_r->key); }
			
			rbiterator &	operator++( void )
			{
				bool	mv = 0;
				if (this && this->_r->parent && !this->_r->right)
				{
					this = this->_r->parent;
					while (this && this == this->_r->parent->right)
						this = this->_r->parent;
					mv = 1;
				}
				else if (this && this->_r->right)
				{
					this = this->_r->right;
					mv = 1;
					if (this->_r->left)
						while (this->_r->left)
							this = this->_r->left;
				}
				if (!mv)
					this->_r = NULL;
				return (*this);
			}
			rbiterator	operator++( int )
			{
				rbiterator tmp(*this);
				++(*this);
				return (tmp);
			}
			rbiterator &	operator--( void )
			{
				bool	mv = 0;
				if (this && this->_r->parent && !this->_r->left)
				{
					this = this->_r->parent;
					while (this && this == this->_r->parent->left)
						this = this->_r->parent;
					mv = 1;
				}
				else if (this && this->_r->left)
				{
					this = this->_r->left;
					mv = 1;
					if (this->_r->right)
						while (this->_r->right)
							this = this->_r->right;
				}
				if (!mv)
					this->_r = NULL;
				return (*this);
			}
			rbiterator	operator--( int )
			{
				rbiterator tmp(*this);
				--(*this);
				return (tmp);
			}
			value_type	base( void ) const { return (this->_r); }

		private:
			value_type	_r;
			Type		_type;
	};
}

#endif
