/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:58:38 by nflan             #+#    #+#             */
/*   Updated: 2022/12/15 17:41:42 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <set>
#include <map>
#include <iostream>
#include "tools.hpp"
#include "rbiterator.hpp"
#include "iterator.hpp"
// 0 = red / 1 = black

namespace ft
{
	template < class Key, class Mapped_Type, class Value_Type, class Compare = std::less<Key>, class Allocator = std::allocator<Value_Type> >
	class rbtree
	{
		public:
			struct	node;

			typedef Key													key_type;
			typedef Value_Type											value_type;
			typedef std::size_t											size_type;
			typedef std::ptrdiff_t										difference_type;
			typedef Compare												key_compare;
			typedef Compare												value_compare;
			typedef Allocator											allocator_type;
			typedef std::allocator<node>								NAllocator;
			typedef node *												nodePTR;
			typedef typename Allocator::reference						reference;
			typedef typename Allocator::const_reference					const_reference;
			typedef typename Allocator::pointer							pointer;
			typedef typename Allocator::const_pointer					const_pointer;
			typedef typename ft::rbiterator<value_type, rbtree>			iterator;
			typedef typename ft::rbiterator<const value_type, rbtree>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			struct node
			{
				public:
					node( void ): col(0), key(NULL), left(NULL), right(NULL), parent(NULL)
					{}
					node( value_type k ): col(0), key(NULL), left(NULL), right(NULL), parent(NULL)
					{
						Allocator	al;
						key = al.allocate(1, 0);
						al.construct(key, k);
					}
					node( value_type k, const node & parent ): col(0), key(NULL), left(NULL), right(NULL), parent(parent)
					{
						Allocator	al;
						key = al.allocate(1, 0);
						al.construct(key, k);
					}
					node( const node & o ): col(o.col), key(NULL), left(o.left), right(o.right), parent(o.parent)
					{
						Allocator	al;
						key = al.allocate(1, 0);
						al.construct(key, *o.key);
					}
					~node ( void )
					{
						Allocator	al;
						if (this->key)
						{
							al.destroy(this->key);
							al.deallocate(this->key, 1);
							this->key = NULL;
						}
					}

					node & operator=( const node & o )
					{
						Allocator	al;
						if (this == &o)
							return (*this);
						this->col = o.col;
						if (this->key)
						{
							al.destroy(key);
							if (!o.key)
							{
								al.deallocate(key, 1);
								key = NULL;
							}
							else
								al.construct(key, *o.key);
						}
						else if (!this->key && o.key)
						{
							this->key = al.allocate(1, 0);
							al.construct(key, *o.key);
						}
						this->left = o.left;
						this->right = o.right;
						this->parent = o.parent;
						return (*this);
					}
					bool		col;
					pointer		key;
					node *		left;
					node *		right;
					node *		parent;
			};

			explicit rbtree( const Compare& comp, const Allocator& alloc = Allocator() ): _compare(comp), _alloc(alloc), _allocnode(NAllocator()), _size(0)
			{
				value_type	test;
				_TNULL = this->_allocnode.allocate(1, 0);
				this->_allocnode.construct(_TNULL, test);
				this->_alloc.destroy(_TNULL->key);
				this->_alloc.deallocate(_TNULL->key, 1);
				_TNULL->col = 1;
				_TNULL->key = NULL;
				_TNULL->parent = _root;
				_root = _TNULL;
			}
			~rbtree( void )
			{
				this->_clear(this->_root);
				this->_allocnode.deallocate(this->_TNULL, 1);
			}

			rbtree &	operator=( const rbtree & o )
			{
				if (this == &o)
					return (*this);
				this->clear();
				this->_allocnode = o._allocnode;
				this->_alloc = o._alloc;
				this->_compare = o._compare;
				this->insert(o.begin(), o.end());
				this->_size = o._size;
				return (*this);
			}
			allocator_type				get_allocator() const { return (this->_alloc); }
			Mapped_Type&				at( const Key& key )
			{
				iterator	tmp = this->find(key);
				if (tmp == this->end())
					throw std::out_of_range("map::at");
				return (tmp->second);
			}
			const Mapped_Type&			at( const Key& key ) const
			{
				const iterator	tmp = this->find(key);
				if (tmp == this->end())
					throw std::out_of_range("map::at");
				return (tmp->second);
			}

			//ITERATORS
			iterator				begin( void )
			{
				nodePTR tmp = this->_root;
				if (tmp)
					while (tmp->left->key)
						tmp = tmp->left;
				return (iterator(tmp));
			}
			const_iterator			begin( void ) const
			{
				nodePTR tmp = this->_root;
				if (tmp)
					while (tmp->left->key)
						tmp = tmp->left;
				return (const_iterator(tmp));
			}
			iterator				end( void ) { return (iterator(this->_TNULL)); }
			const_iterator			end( void ) const { return (const_iterator(this->_TNULL)); }
			reverse_iterator		rbegin( void ) { return (reverse_iterator(this->end())); }
			const_reverse_iterator	rbegin( void ) const { return (const_reverse_iterator(this->end())); }
			reverse_iterator		rend( void ) { return (reverse_iterator(this->begin())); }
			const_reverse_iterator	rend( void ) const { return (const_reverse_iterator(this->begin())); }

			//CAPACITY
			bool					empty( void ) const { return (this->_size ? false : true); }
			size_type				size( void ) const { return (this->_size); }
			size_type				max_size( void ) const { return (this->_allocnode.max_size()); }

			//MODIFIERS
			void					clear( void );
			void					insert( const value_type & k )
			{
				nodePTR	n = this->_allocnode.allocate(1, 0);
				this->_allocnode.construct(n, k);
				n->left = this->_TNULL;
				n->right = this->_TNULL;
				nodePTR	tmp = this->_root;
				nodePTR	temp = _TNULL;
				while (tmp != this->_TNULL)
				{
					temp = tmp;
					if (_compare(*n->key, *tmp->key))
						tmp = tmp->left;
					else if (_compare(*tmp->key, *n->key))
						tmp = tmp->right;
					else
						throw EqualException();
				}
				n->parent = temp;
				this->_size++;
				if (!temp->key)
					this->_root = n;
				else if (_compare(*n->key, *temp->key))
					temp->left = n;
				else
					temp->right = n;
				if (!n->parent->key)
				{
					n->col = 1;
					return ;
				}
				if (!n->parent->parent->key)
					return ;
				this->_recolor(n);
			}
			iterator					insert( iterator pos, const value_type& value )
			{ //VERIFIER SI PAS DECONNANT D'INSERT A LA POSITION DONNEE, SINON REPRENDRE L'INSERT BASIQUE
				iterator ret = this->begin();
				if (!pos.base()->parent->key)
					insert(value);
				else if (_compare(*pos.base()->parent->key, value) && _compare(value, *pos.base()->key))
				{
					nodePTR	n = this->_allocnode.allocate(1, 0);
					this->_allocnode.construct(n, value);
					n->left = this->_TNULL;
					n->right = this->_TNULL;
					nodePTR	tmp = pos.base();
					nodePTR	temp = _TNULL;
					while (tmp != this->_TNULL)
					{
						temp = tmp;
						if (_compare(*n->key, *tmp->key))
							tmp = tmp->left;
						else if (_compare(*tmp->key, *n->key))
							tmp = tmp->right;
						else
							throw EqualException();
					}
					n->parent = temp;
					this->_size++;
					if (!temp->key)
						this->_root = n;
					else if (_compare(*n->key, *temp->key))
						temp->left = n;
					else
						temp->right = n;
					if (!n->parent->key)
					{
						n->col = 1;
						return (iterator(n));
					}
					if (!n->parent->parent->key)
						return (iterator(n));
					this->_recolor(n);
					return (pos);
				}
				else
					insert(value);
				return (ret);
			}
			template< class InputIt >
			void						insert( InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL )
			{
				for (; first != last; first++)
					this->insert(*first);
			}
			iterator					erase( iterator pos );
			iterator					erase( iterator first, iterator last );
			size_type					erase( const Key& key );

			//LOOKUP
			size_type		count( const key_type& key ) const
			{
				if (this->find(key) == this->end())
					return (0);
				return (1);
			}
			iterator		find(const key_type& key)
			{
				ft::pair<Key, Mapped_Type>	k = ft::make_pair(key, 0);
				nodePTR	tmp = this->_root;
				while (tmp != _TNULL)
				{
					if (_compare(k, *tmp->key))
						tmp = tmp->left;
					else if (_compare(*tmp->key, k))
						tmp = tmp->right;
					else
						return (iterator(tmp));
				}
				return (iterator(_TNULL));
			}
			const_iterator	find(const key_type& key) const
			{
				ft::pair<Key, Mapped_Type>	k = ft::make_pair(key, 0);
				nodePTR	tmp = this->_root;
				while (tmp != _TNULL)
				{
					if (_compare(k, *tmp->key))
						tmp = tmp->left;
					else if (_compare(*tmp->key, k))
						tmp = tmp->right;
					else
						return (const_iterator(tmp));
				}
				return (const_iterator(_TNULL));
			}
			ft::pair<iterator, iterator>				equal_range( const key_type& key ) { return (ft::make_pair(lower_bound(key), upper_bound(key))); }
			ft::pair<const_iterator, const_iterator>	equal_range( const key_type& key ) const { return (ft::make_pair(lower_bound(key), upper_bound(key))); }
			iterator									lower_bound( const key_type& key )
			{
				ft::pair<Key, Mapped_Type>	k = ft::make_pair(key, 0);
				nodePTR	tmp = this->_root;
				nodePTR	temp = this->_TNULL;
				while (tmp != this->_TNULL)
				{
					if (!_compare(*tmp->key, k) && !_compare(k, *tmp->key))
						return (iterator(tmp));
					if (!_compare(*tmp->key, k))
						temp = tmp;
					if (_compare(k, *tmp->key))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (!temp->key)
					return (iterator(_TNULL));
				return (iterator(temp));
			}
			const_iterator								lower_bound( const key_type& key ) const
			{
				ft::pair<Key, Mapped_Type>	k = ft::make_pair(key, 0);
				nodePTR	tmp = this->_root;
				nodePTR	temp = this->_TNULL;
				while (tmp != this->_TNULL)
				{
					if (!_compare(*tmp->key, k) && !_compare(k, *tmp->key))
						return (const_iterator(tmp));
					if (!_compare(*tmp->key, k))
						temp = tmp;
					if (_compare(k, *tmp->key))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (!temp->key)
					return (const_iterator(_TNULL));
				return (const_iterator(temp));
			}
			iterator									upper_bound( const key_type& key )
			{
				ft::pair<Key, Mapped_Type>	k = ft::make_pair(key, 0);
				nodePTR	tmp = this->_root;
				nodePTR	temp = this->_TNULL;
				while (tmp != this->_TNULL)
				{
					if (!_compare(*tmp->key, k) && !(!_compare(*tmp->key, k) && !_compare(k, *tmp->key)))
						temp = tmp;
					if (_compare(k, *tmp->key))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (!temp->key)
					return (iterator(_TNULL));
				return (iterator(temp));
			}
			const_iterator								upper_bound( const key_type& key ) const
			{
				ft::pair<Key, Mapped_Type>	k = ft::make_pair(key, 0);
				nodePTR	tmp = this->_root;
				nodePTR	temp = this->_TNULL;
				while (tmp != this->_TNULL)
				{
					if (!_compare(*tmp->key, k) && !(!_compare(*tmp->key, k) && !_compare(k, *tmp->key)))
						temp = tmp;
					if (_compare(k, *tmp->key))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (!temp->key)
					return (const_iterator(_TNULL));
				return (const_iterator(temp));
			}

			//OBSERVERS
			value_compare	value_comp() const { return (_compare); }

			void	print( void ) { this->_print(this->_root, "", true); }
			nodePTR	getRoot() { return (this->_root); }

		private:
			nodePTR		_root;
			nodePTR		_TNULL;
			key_compare	_compare;
			Allocator	_alloc;
			NAllocator	_allocnode;
			size_type	_size;

			//EXCEPTION
			class EqualException: public std::exception {
				virtual const char* what() const throw()
				{
					return ("Error: same index in two different nodes!");
				}
			};

			void	_initNullNode( nodePTR nod, nodePTR parent )
			{
				nod->col = 0;
				nod->key = 0;
				nod->parent = parent;
				nod->left = NULL;
				nod->right = NULL;
			}
			void	_clear(nodePTR root)
			{
				bool	r = 0;
				if (root->key)
				{
					_clear(root->left);
					_clear(root->right);
					if (root == this->_root)
						r = 1;
					this->_allocnode.destroy(root);
					root->left = NULL;
					root->right = NULL;
					root->key = NULL;
					this->_allocnode.deallocate(root, 1);
					root = NULL;
					if (r)
						root = this->_TNULL;
				}
			}
			void	_recolor( nodePTR & n )
			{
				nodePTR	u;
				while (n->parent->col == 0)
				{
					if (n->parent == n->parent->parent->right)
					{
						u = n->parent->parent->left;
						if (u && u->col == 0)
						{
							u->col = 1;
							n->parent->col = 1;
							n->parent->parent->col = 0;
							n = n->parent->parent;
						}
						else
						{
							if (n == n->parent->left)
							{
								n = n->parent;
								this->_right_rotate(n);
							}
							n->parent->col = 1;
							n->parent->parent->col = 0;
							this->_left_rotate(n->parent->parent);
						}
					}
					else
					{
						u = n->parent->parent->right;
						if (u && u->col == 0)
						{
							u->col = 1;
							n->parent->col = 1;
							n->parent->parent->col = 0;
							n = n->parent->parent;
						}
						else
						{
							if (n == n->parent->right)
							{
								n = n->parent;
								this->_left_rotate(n);
							}
							n->parent->col = 1;
							n->parent->parent->col = 0;
							this->_right_rotate(n->parent->parent);
						}
					}
					if (n == this->_root)
						break ;
				}
				this->_TNULL->parent = this->_root;
				this->_root->col = 1;
			}
			void	_left_rotate( nodePTR n )
			{
				nodePTR	y = n->right;
				n->right = y->left;
				if (y->left != this->_TNULL)
					y->left->parent = n;
				y->parent = n->parent;
				if (!n->parent->key)
					this->_root = y;
				else if (n == n->parent->left)
					n->parent->left = y;
				else
					n->parent->right = y;
				y->left = n;
				n->parent = y;
			}
			void	_right_rotate( nodePTR n )
			{
				nodePTR	y = n->left;
				n->left = y->right;
				if (y->right != this->_TNULL)
					y->right->parent = n;
				y->parent = n->parent;
				if (!n->parent->key)
					this->_root = y;
				else if (n == n->parent->right)
					n->parent->right = y;
				else
					n->parent->left = y;
				y->right = n;
				n->parent = y;
			}
		/*	void	_left_right_rot( nodePTR & n )
			{
				nodePTR	p = n->parent;
				nodePTR	gp = n->parent->parent;
				this->left_rotate(n);
				this->left_rotate(p);
				this->right_rotate(n);
				this->right_rotate(gp);
			}
			void	_right_left_rot( nodePTR & n )
			{
				nodePTR	p = n->parent;
				nodePTR	gp = n->parent->parent;
				this->right_rotate(n);
				this->right_rotate(p);
				this->left_rotate(n);
				this->left_rotate(gp);
			}
*/
	};
}

#endif
