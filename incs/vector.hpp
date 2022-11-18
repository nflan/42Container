/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:18:36 by nflan             #+#    #+#             */
/*   Updated: 2022/11/18 16:23:03 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <iostream>
#include <vector>
#include <iterator>
#include <stdexcept>
#include "tools.hpp"
#include "viterator.hpp"
#include "const_viterator.hpp"

namespace ft {

	template < class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
		//	typedef typename ft::viterator<pointer, vector>			iterator;
		//	typedef typename ft::const_viterator<pointer, vector>	const_iterator;
			typedef typename std::vector<T>::iterator		iterator;
			typedef typename std::vector<T>::iterator		const_iterator;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
			
			//Default
			vector( void ): _tab(NULL), _capacity(0), _size(0), _alloc(Allocator()) {}
			//Copy
			vector( const vector & v ): _tab(NULL), _capacity(v._size), _size(v._size), _alloc(v._alloc)
			{
				if (this->_capacity)
				{
					this->_tab = this->_alloc.allocate(this->_capacity, 0);
					for (size_type i = 0; i < this->_capacity; i++)
						this->_alloc.construct(&this->_tab[i], v._tab[i]);
				}
			}
			explicit vector( const Allocator & alloc ): _tab(NULL), _capacity(0), _size(0), _alloc(alloc) {}
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()): _tab(NULL), _capacity(count * 2), _size(count), _alloc(alloc)
			{
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
				InputIt	tmp = first;
				difference_type	dif = 0;
				while (tmp != last)
				{
					tmp++;
					dif++;
				}
				tmp = first;
				this->_size = dif;
				this->_capacity = dif;
				this->_tab = NULL;
				this->_alloc = alloc;
				if (this->_capacity)
				{
					this->_tab = this->_alloc.allocate(this->_capacity, 0);
					for (size_type i = 0; tmp != last; i++)
					{
						this->_alloc.construct(&this->_tab[i], *tmp);
						tmp++;
					}
				}
					
			}
			~vector( void )
			{
				this->clear();
				this->_alloc.deallocate(this->_tab, this->_capacity);
		//		std::cout << "Destructor called" << std::endl;
			}

			vector &				operator=( const vector & other )
			{
				if (this == &other)
					return (*this);
				if (this->_tab && other.size() > this->capacity())
				{
					this->clear();
					this->_alloc.deallocate(this->_tab, this->capacity());
					this->_capacity = other.size();
					this->_tab = this->_alloc.allocate(this->capacity(), 0);
				}
				else
					for (size_type i = 0; i < this->size(); i++)
						this->_alloc.destroy(&this->_tab[i]);
				this->_alloc = other._alloc;
				this->_size = other._size;
				for (size_type i = 0; i < other.size(); i++)
					this->_alloc.construct(&this->_tab[i], other._tab[i]);
				return (*this);
			}
			void					assign( size_type count, const T& value )
			{
				pointer	tmp = NULL;
				this->_size = count;
				if (this->capacity() < count)
				{
					size_type i = 0;
					this->_capacity = count;
					tmp = this->_alloc.allocate(this->capacity(), 0);
					for (; i < count; i++)
						this->_alloc.construct(&tmp[i], value);
					this->_tab = tmp;
				}
				else if (this->capacity() && this->capacity() > count)
				{
					for (size_type i = 0; i < count; i++)
					{
						this->_alloc.destroy(&this->_tab[i]);
						this->_alloc.construct(&this->_tab[i], value);
					}
				}
			}
			template< class InputIt >
			//peut pas le faire avant les iterators // check diff aussi
			void					assign( InputIt first, InputIt last );
			allocator_type			get_allocator( void ) const { return (this->_alloc); }

			//ITERATORS
			iterator				begin( void ) { return (iterator(this->data())); }
			const_iterator			begin( void ) const { return (const_iterator(this->_tab)); }
			iterator				end( void ) { return (iterator(this->data() + this->size())); }
			const_iterator			end( void ) const { return (const_iterator(&(this->_tab[this->size()]))); }
			reverse_iterator		rbegin( void ) { return (this->end()); }
			const_reverse_iterator	rbegin( void ) const { return (this->end()); }
			reverse_iterator		rend( void ) { return (this->begin()); }
			const_reverse_iterator	rend( void ) const { return (this->begin()); }

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
					throw std::length_error("oscour");
				pointer	tmp = NULL;
				size_type	i = 0;
				tmp = this->_alloc.allocate(n, 0);
				for (; i < this->size(); i++)
				{
					this->_alloc.construct(&tmp[i], this->_tab[i]);
					this->_alloc.destroy(&this->_tab[i]);
				}
				this->_alloc.deallocate(this->_tab, this->capacity());
				this->_capacity = n;
				this->_tab = tmp;
			}

			//ELEMENT ACCESS
			reference				at(size_type pos)
			{
				if (pos >= 0 && pos < this->size())
					return (this->_tab[pos]);
				throw std::out_of_range("Out of range");
			}
			const_reference			at(size_type pos) const
			{
				if (pos >= 0 && pos < this->size())
					return (this->_tab[pos]);
				throw std::out_of_range("Out of range");
			}
			reference				operator[](size_type pos) { return (this->_tab[pos]); }
			const_reference			operator[](size_type pos) const { return (this->_tab[pos]); }
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
			value_type*				data( void ) { return (this->_tab); }
			const value_type*		data( void ) const { return (this->_tab); }

			//MODIFIERS
			void					clear( void )
			{
				while (this->_size)
				{
					this->_alloc.destroy(&this->_tab[this->size()]);
					this->_size--;
				}
			}
			iterator				insert(iterator position, const value_type& val);
			void					insert(iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void					insert(iterator position, InputIterator first, InputIterator last);
			iterator				erase( iterator pos )
			{
//				iterator	tmp = pos;
				iterator	ret = pos + 1;

				for (iterator it = pos + 1; it != this->end(); it++, pos++)
					pos = it;
				if (pos == this->end() - 1)
					return (this->end());
				//this->_alloc.destroy(&tmp);
				return (ret);
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
				/*	{
						vector<T, Allocator>	dest(this->capacity());
						for (size_type i = 0; i < this->size(); i++)
							dest._alloc.construct(&dest._tab[i], this->_tab[i]);
						*this = dest;
					}
				*/	{
						pointer	tmp;
						tmp = this->_alloc.allocate(this->capacity() * 2, 0);
						for (size_type i = 0; i < this->size(); i++)
						{
							this->_alloc.construct(&tmp[i], this->_tab[i]);
							this->_alloc.destroy(&this->_tab[i]);
						}
						this->_alloc.deallocate(this->_tab, this->_capacity);
						this->_capacity *= 2;
						this->_tab = tmp;
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


		private:
			pointer			_tab;
			size_type		_capacity;
			size_type		_size;
			Allocator		_alloc;
	};

	template< class T, class Allocator >
	bool	operator==( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename vector<T, Allocator>::iterator rt = rhs.begin();
		for (typename vector<T, Allocator>::iterator lt = lhs.begin(); lt != lhs.end(); lt++, rt++)
			if (*lt != *rt)
				return (false);
		return (true);
	}
	template< class T, class Allocator >
	bool	operator!=( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs )
	{
		return (!(lhs == rhs));
	}
	template< class T, class Allocator >
	bool	operator<( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs )	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs != rhs); }
	template< class T, class Allocator >
	bool	operator<=( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs )	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs); }
	template< class T, class Allocator >
	bool	operator>( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs )	{ return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) && lhs != rhs); }
	template< class T, class Allocator >
	bool	operator>=( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs )	{ return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) || lhs == rhs); }
};

#endif
