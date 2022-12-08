/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbiterator.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:00:52 by nflan             #+#    #+#             */
/*   Updated: 2022/12/08 13:59:56 by nflan            ###   ########.fr       */
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
			typedef Key								iterator_type;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;
			typedef value_type*						pointer;
			typedef const value_type*				const_pointer;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef typename std::ptrdiff_t			difference_type;
			typedef typename Type::node				node;
			typedef typename Type::node *			nodePTR;

			rbiterator( void ): _r() {}
			explicit rbiterator(const nodePTR & other_r, const Type * type): _r(other_r), _type(*type) {}
			template <typename P>
			rbiterator(const rbiterator<P, typename enable_if<is_same<P, typename Type::pointer>::key, Type>::type> & other) : _r(other.base()), _type(other._type) {}
			~rbiterator() {}

			rbiterator &	operator=( const rbiterator & o )
			{
				if (this != &o)
					this->_r = o.operator->();
				return (*this);
			}
			reference	operator*( void ) const { if (this->_r) std::cout << this->_r->key << std::endl; return (*this->_r->key); }
			operator rbiterator<const value_type, Type>( void ) { return (rbiterator<const value_type, Type>(this->_r)); }
			pointer		operator->( void ) const { return (*this->_r->key); }
			
			rbiterator &	operator++( void )
			{
				bool	mv = 0;
				if (this->_r && this->_r->parent && !this->_r->right)
				{
					this->_r = this->_r->parent;
					while (this->_r && this->_r == this->_r->parent->right)
						this->_r = this->_r->parent;
					mv = 1;
				}
				else if (this->_r && this->_r->right)
				{
					this->_r = this->_r->right;
					mv = 1;
					if (this->_r->left)
						while (this->_r->left)
							this->_r = this->_r->left;
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
				if (this->_r && this->_r->parent && !this->_r->left)
				{
					this->_r = this->_r->parent;
					while (this && this == this->_r->parent->left)
						this->_r = this->_r->parent;
					mv = 1;
				}
				else if (this->_r && this->_r->left)
				{
					this->_r = this->_r->left;
					mv = 1;
					if (this->_r->right)
						while (this->_r->right)
							this->_r = this->_r->right;
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
			nodePTR	_r;
			Type	_type;
	};
}

#endif
