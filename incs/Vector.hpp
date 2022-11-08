/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:18:36 by nflan             #+#    #+#             */
/*   Updated: 2022/11/08 16:42:16 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <iostream>

namespace ft {

	template < class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T					value_type;
			typedef T					size_type;
			typedef value_type *		pointer;
			typedef value_type *		iterator;
			typedef value_type *		reverse_iterator;
			typedef const value_type *	const_iterator;
			typedef const value_type *	const_reverse_iterator;
			typedef value_type &		reference;
			typedef const value_type &	const_reference;
			typedef Allocator			allocator_type;
			
			//Default
			vector( void )
			{ 
				std::cout << "Void constructor" << std::endl;
				_tab = NULL;
				_capacity = 1;
				_size = 0;
			}
			//Copy
			//pointer allocate( size_type n, const void * hint = 0 );
			vector( const vector & v )
			{
				std::cout << "Const vector & v constructor" << std::endl;
				_size = v._size;
				_capacity = v._capacity;
				_alloc = v._alloc;
				if (_capacity)
				{
					try
					{
						_tab = Allocator::allocate(_capacity, 0);
					}
					catch ( std::exception & e )
					{
						std::cerr << e.what() << " in vector( const vector & v )" << std::endl;
					}
					for (value_type i = 0; i < _capacity; i++)
						_tab[i] = v._tab[i];
				}
				else
					_tab = NULL;
			}
			//OSCOURRRRRRRRRRR
			explicit vector( const Allocator & alloc )
			{
				std::cout << "const Allocator & alloc constructor" << std::endl;
				_tab = NULL;
				_capacity = 1;
				_size = 0;
				_alloc = alloc;
			}
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
			{
				std::cout << "size_type count, const T& value = T(), const Allocator& alloc = Allocator() constructor" << std::endl;
				_size = count;
				_capacity = count * 2;
				_alloc = alloc;
				if (_capacity)
				{
					try
					{
						_tab = Allocator::allocate(_capacity, 0);
					}
					catch ( std::exception & e )
					{
						std::cerr << e.what() << " in vector(size_type countm const T& value = T(), const Allocator& alloc = Allocator())" << std::endl;
					}
					for (value_type i = 0; i < _capacity; i++)
						_tab[i] = value;
				}
				else
					_tab = NULL;
			}
			//Range
			template< class InputIt >
				vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() )
				{
					std::cout << "InputIT first, InputIt last, const Allocator& alloc = Allocator() constructor" << std::endl;
				}
			~vector( void )
			{
				delete [] _tab;
				std::cout << "Destructor called" << std::endl;
			}

			vector &	operator=( const vector & );
			//ITERATORS
			iterator				begin( void );
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
				void				assign(InputIterator first, InputIterator last);
			void					assign(size_type n, const value_type& val);
			void					push_back(const value_type& val);
			void					pop_back( void );
			iterator				insert(iterator position, const value_type& val);
			void					insert(iterator position, size_type n, const value_type& val);
			template <class InputIterator>
				void				insert(iterator position, InputIterator first, InputIterator last);
			void					swap(vector& x);
			void					clear( void );

			//ALLOCATOR
			allocator_type						get_allocator( void ) const;

		private:
			value_type *	_tab;
			size_type		_capacity;
			size_type		_size;
			Allocator		_alloc;
		};

	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs );
};

#endif
