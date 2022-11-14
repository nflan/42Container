/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:18:36 by nflan             #+#    #+#             */
/*   Updated: 2022/11/14 18:17:14 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <iostream>
#include "tools.hpp"

namespace ft {

	template < class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef value_type &							reference;
			typedef const value_type &						const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef value_type *							iterator;
			typedef const value_type *						const_iterator;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
			
			//Default
			vector( void ): _tab(NULL), _capacity(0), _size(0)
			{ 
	//			std::cout << "Void constructor" << std::endl;
			}
			//Copy
			//pointer allocate( size_type n, const void * hint = 0 );
			vector( const vector & v )
			{
	//			std::cout << "Const vector & v constructor" << std::endl;
				this->_size = v._size;
				this->_capacity = v._capacity;
				this->_alloc = v._alloc;
				this->_tab = NULL;
				if (this->_capacity)
				{
					this->_tab = this->_alloc.allocate(_capacity, 0);
					for (size_type i = 0; i < this->_capacity; i++)
						this->_alloc.construct(&this->_tab[i], v._tab[i]);
				}
			}
			//OSCOURRRRRRRRRRR
			explicit vector( const Allocator & alloc )
			{
	//			std::cout << "const Allocator & alloc constructor" << std::endl;
				this->_tab = NULL;
				this->_capacity = 1;
				this->_size = 0;
				this->_alloc = alloc;
			}
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
			{
				std::cout << "size_type count, const T& value = T(), const Allocator& alloc = Allocator() constructor" << std::endl;
				this->_size = count;
				this->_capacity = count * 2;
				this->_alloc = alloc;
				this->_tab = NULL;
				if (this->_capacity)
				{
					this->_tab = this->_alloc.allocate(this->_capacity, 0);
					for (size_type i = 0; i < this->_capacity; i++)
						this->_alloc.construct(&this->_tab[i], value);
				}
			}
			//Range
			template< class InputIt >
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() )
			{
	//			std::cout << "InputIT first, InputIt last, const Allocator& alloc = Allocator() constructor" << std::endl;
			}
			~vector( void )
			{
				for (size_type i = 0; i < this->size(); i++)
					this->_alloc.destroy(&this->_tab[i]);
				this->_alloc.destroy(this->_tab);
				this->_alloc.deallocate(this->_tab, this->_capacity);
	//			std::cout << "Destructor called" << std::endl;
			}

			vector &				operator=( const vector & other )
			{
				if (this == &other)
					return (*this);
				if (this->_tab)
				{
					for (size_type i = this->size(); i != 0; i--)
						this->_alloc.destroy(&this->_tab[i]);
					this->_alloc.deallocate(this->_tab, this->capacity());
				}
				this->_alloc = other._alloc;
				this->_size = other._size;
				this->_capacity = other._capacity;
				this->_tab = this->_alloc.allocate(other._capacity, 0);
				for (size_type i = 0; i <= this->size(); i++)
					this->_alloc.construct(&this->_tab[i], other._tab[i]);
				return (*this);
			}
			void					assign( size_type count, const T& value )
			{
				vector<T>	dest(count, value);
				*this = dest;
			}
			template< class InputIt >
			void					assign( InputIt first, InputIt last );
			allocator_type			get_allocator( void ) const { return (this->_alloc); }

			//ITERATORS
			iterator				begin( void ) { return (this->_tab[0]); }
			const_iterator			begin( void ) const { return (const_cast<iterator>(&this->_tab[0])); }
			iterator				end( void ) { return (&this->_tab[this->_size]); }
			const_iterator			end( void ) const { return (const_cast<iterator>(&this->_tab[this->_size])); }
			reverse_iterator		rbegin( void ) { return (this->_tab[this->_size - 1]); }
			const_reverse_iterator	rbegin( void ) const { return (const_cast<reverse_iterator>(this->_tab[this->_size - 1])); }
			reverse_iterator		rend( void ) { return (this->begin()); }
			const_reverse_iterator	rend( void ) const { return (const_cast<reverse_iterator>(this->begin())); }

			//CAPACITY
			size_type				size( void ) const { return (this->_size); }
			size_type				max_size( void ) const { return (this->_alloc.max_size()); }
			size_type				capacity( void ) const { return (this->_capacity); }
			bool					empty( void ) const { return (this->_size == 0 ? true : false ); }
			void					reserve (size_type n)
			{ 
				if (n <= this->_capacity)
					return ;
				else if (n > this->max_size())
					throw std::length_error();
				this->_capacity += n - this->_capacity;
				this->_alloc.allocate(this->_capacity, this->_tab);
				this->_alloc.construct(this->_tab, this->_capacity);
			};

			//ELEMENT ACCESS
			reference				at(size_type pos)
			{
				if (pos = 0 && pos < this->size())
					return (this->_tab[pos]);
				throw std::out_of_range();
			}
			const_reference			at(size_type pos) const
			{
				if (pos >= 0 && pos < this->size())
					return (this->_tab[pos]);
				throw std::out_of_range();
			}
			reference				operator[](size_type pos)
			{
				return (this->_tab[pos]);
			}
			const_reference			operator[](size_type pos) const
			{
				return (this->_tab[pos]);
			}
			reference				front( void )
			{
				if (this->size())
					return (this->_tab[0]);
				return (NULL);
			}
			const_reference			front( void ) const
			{
				if (this->size())
					return (this->_tab[0]);
				return (NULL);
			}
			reference				back( void )
			{
				if (this->size())
					return (this->_tab[this->size()]);
				return (*this->_tab);
			}
			const_reference			back( void ) const
			{
				if (this->size())
					return (this->_tab[this->size()]);
				return (NULL);
			}
			value_type*				data( void );
			const value_type*		data( void ) const;

			//MODIFIERS
			void					clear( void );
			iterator				insert(iterator position, const value_type& val);
			void					insert(iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void					insert(iterator position, InputIterator first, InputIterator last);
			iterator				erase( iterator pos )
			{
				iterator	it = pos + 1;
				pos = NULL;
				if (pos == this->end() - 1)
					return (this->end());
				return (it);
			}
			iterator				erase( iterator first, iterator last );
			void					push_back(const value_type& val)
			{
				if (this->_size == this->_capacity)
				{
					if (!this->_tab)
					{
						this->_capacity++;
						this->_tab = this->_alloc.allocate(this->capacity(), 0);
					}
					else
					{
						vector<T>	dest(this->capacity());
						size_type	i = 0;
						while (i < this->size())
						{
							dest._alloc.construct(&dest._tab[i], this->_tab[i]);
							i++;
						}
						*this = dest;
					}
				}
				this->_alloc.construct(&this->_tab[this->size()], val);
				this->_size++;
			}
			void					pop_back( void )
			{
				if (this->_size)
				{
					this->_alloc.destroy(&this->_tab[this->size()]);
					this->_size--;
				}
			}
			void					resize( size_type count, T value = T() );
			void					swap(vector& x);

			friend bool	operator==( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs )	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
			friend bool	operator!=( const vector< T, Allocator >& lhs, const vector< T,Allocator >& rhs )	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
			friend bool	operator<( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs )	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
			friend bool	operator<=( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs )	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
			friend bool	operator>( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs )	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
			friend bool	operator>=( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs )	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

		private:
			value_type *	_tab;
			size_type		_capacity;
			size_type		_size;
			Allocator		_alloc;
		};

	template< class T, class Allocator >
	bool	operator==( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs );
	template< class T, class Allocator >
	bool	operator!=( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs );
	template< class T, class Allocator >
	bool	operator<( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs );
	template< class T, class Allocator >
	bool	operator<=( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs );
	template< class T, class Allocator >
	bool	operator>( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs );
	template< class T, class Allocator >
	bool	operator>=( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs );
};

#endif
