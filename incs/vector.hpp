/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:18:36 by nflan             #+#    #+#             */
/*   Updated: 2022/11/12 13:54:42 by nflan            ###   ########.fr       */
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
			typedef Allocator::pointer						pointer;
			typedef Allocator::const_pointer				pointer;
			typedef value_type *							iterator;
			typedef const value_type *						const_iterator;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
			
			//Default
			vector( void )
			{ 
				std::cout << "Void constructor" << std::endl;
				this->_tab = NULL;
				this->_capacity = 1;
				this->_size = 0;
			}
			//Copy
			//pointer allocate( size_type n, const void * hint = 0 );
			vector( const vector & v )
			{
				std::cout << "Const vector & v constructor" << std::endl;
				this->_size = v._size;
				this->_capacity = v._capacity;
				this->_alloc = v._alloc;
				if (this->_capacity)
				{
					this->_tab = this->_alloc.allocate(_capacity, 0);
					for (value_type i = 0; i < _capacity; i++)
						this->_tab[i] = v._tab[i];
				}
				else
					this->_tab = NULL;
			}
			//OSCOURRRRRRRRRRR
			explicit vector( const Allocator & alloc )
			{
				std::cout << "const Allocator & alloc constructor" << std::endl;
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
				if (this->_capacity)
				{
					this->_tab = this->_alloc.allocate(this->_capacity, 0);
					this->_alloc.construct(this->_tab, this->_capacity);
					for (value_type i = 0; i < _capacity; i++)
					{
						this->_tab[i] = value;
					}
				}
				else
					this->_tab = NULL;
			}
			//Range
			template< class InputIt >
				vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() )
				{
					std::cout << "InputIT first, InputIt last, const Allocator& alloc = Allocator() constructor" << std::endl;
				}
			~vector( void )
			{
				delete [] this->_tab;
				std::cout << "Destructor called" << std::endl;
			}

			vector &	operator=( const vector & );
			//ITERATORS
			iterator				begin( void ) { return (*;
			const_iterator			begin( void ) const;
			iterator				end( void );
			const_iterator			end( void ) const;
			reverse_iterator		rbegin( void );
			const_reverse_iterator	rbegin( void ) const;
			reverse_iterator		rend( void );
			const_reverse_iterator	rend( void ) const;
			const_iterator			cbegin( void ) const;
			const_iterator			cend( void ) const;
			const_reverse_iterator	crbegin( void ) const;
			const_reverse_iterator	crend( void ) const;

			//CAPACITY
			size_type				size( void ) const;
			size_type				max_size( void ) const;
			void					resize(size_type n, value_type val = value_type());
			size_type				capacity( void ) const;
			bool					empty( void ) const;
			void					reserve (size_type n);

			//ELEMENT ACCESS
			reference				operator[](size_type n);
			const_reference			operator[](size_type n) const;
			reference				at(size_type n);
			const_reference			at(size_type n) const;
			reference				front( void );
			const_reference			front( void ) const;
			reference				back( void );
			const_reference			back( void ) const;
			value_type*				data( void );
			const value_type*		data( void ) const;

			//MODIFIERS
			template <class InputIterator>
			void					assign(InputIterator first, InputIterator last);
			void					assign(size_type n, const value_type& val);
			void					push_back(const value_type& val);
			void					pop_back( void );
			iterator				insert(iterator position, const value_type& val);
			void					insert(iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void					insert(iterator position, InputIterator first, InputIterator last);
			void					swap(vector& x);
			void					clear( void );

			//ALLOCATOR
			allocator_type			get_allocator( void ) const;

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
