/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbiterator.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:00:52 by nflan             #+#    #+#             */
/*   Updated: 2022/12/22 18:30:28 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBITERATOR_HPP
#define RBITERATOR_HPP

#include <iterator>
#include "iterator.hpp"
#include "tools.hpp"

namespace ft
{
	template < class Key, class rbtree >
	class rbiterator
	{
		public:
			typedef Key									value_type;
			typedef Key									iterator_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef value_type*							pointer;
			typedef const value_type*					const_pointer;
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef typename rbtree::difference_type	difference_type;
			typedef typename rbtree::node				node;
			typedef typename rbtree::nodePTR			nodePTR;

			rbiterator( void ): _r() {}
			explicit rbiterator(const nodePTR & other_r): _r(other_r) {}
			template <typename P>
			rbiterator(const rbiterator<P, typename enable_if<is_same<P, typename rbtree::pointer>::value, rbtree>::type> & other) : _r(other.base()) {}
			~rbiterator() {}

			operator rbiterator<const value_type, rbtree>( void ) const { return (rbiterator<const value_type, rbtree>(this->_r)); }
			rbiterator &	operator=( const rbiterator & o )
			{
				if (this != &o)
					this->_r = o._r;
				return (*this);
			}
			reference	operator*( void ) const { return (*this->_r->key); }
			pointer		operator->( void ) { return (&(*(this->_r->key))); }
			pointer		operator->( void ) const { return (&(*(this->_r->key))); }
			
			rbiterator &	operator++( void )
			{
				if (this->_r->key && this->_r->parent->key && !this->_r->right->key)
				{
					while (this->_r == this->_r->parent->right)
					{
						this->_r = this->_r->parent;
						if (!this->_r->key)
							return (*this);
					}
					this->_r = this->_r->parent;
				}
				else if (this->_r->key && this->_r->right->key)
				{
					this->_r = this->_r->right;
					while (this->_r->left->key)
						this->_r = this->_r->left;
				}
				else if (this->_r->key && !this->_r->parent->key)
					this->_r = this->_r->parent;
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
				if (!this->_r->key)
				{
					this->_r = this->_r->parent;
					if (this->_r->right)
						while (this->_r->right->key)
							this->_r = this->_r->right;
					return (*this);
				}
				if (this->_r->parent->key && !this->_r->left->key)
				{
					while (this->_r->parent->key && this->_r == this->_r->parent->left)
						this->_r = this->_r->parent;
					this->_r = this->_r->parent;
				}
				else if (this->_r->left->key)
				{
					this->_r = this->_r->left;
					if (this->_r->right)
						while (this->_r->right->key)
							this->_r = this->_r->right;
				}
				return (*this);
			}
			rbiterator	operator--( int )
			{
				rbiterator tmp(*this);
				--(*this);
				return (tmp);
			}
			const nodePTR	base( void ) const { return (this->_r); }

		private:
			nodePTR	_r;
	};
/*	template < class Key, class rbtree >
	bool	operator==( const rbiterator<Key, rbtree>& lhs, const rbiterator<Key, rbtree>& rhs )
	{
		if (lhs->first == rhs->first && lhs->second == rhs->second)
			return (true);
		return (false);
	}
	template < class Key, class rbtree >
	bool	operator!=( const rbiterator<Key, rbtree>& lhs, const rbiterator<Key, rbtree>& rhs ) { return (!(lhs == rhs)); }
*/
	template< class Key, class rbtree>
	bool	operator!=(const rbiterator<Key, rbtree>& lhs, const rbiterator<Key, rbtree>& rhs) { return (lhs.base() != rhs.base()); }
	template< class Key, class rbtree, class rKey, class rrbtree>
	bool	operator!=(const rbiterator<Key, rbtree>& lhs, const rbiterator<rKey, rrbtree>& rhs) { return (lhs.base() != rhs.base()); }
	template< class Key, class rbtree>
	bool	operator==(const rbiterator<Key, rbtree>& lhs, const rbiterator<Key, rbtree>& rhs) { return (lhs.base() == rhs.base()); }
	template< class Key, class rbtree, class rKey, class rrbtree>
	bool	operator==(const rbiterator<Key, rbtree>& lhs, const rbiterator<rKey, rrbtree>& rhs) { return (lhs.base() == rhs.base()); }
}

#endif
