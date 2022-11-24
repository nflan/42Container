/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:18:36 by nflan             #+#    #+#             */
/*   Updated: 2022/11/24 16:25:51 by nflan            ###   ########.fr       */
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

namespace ft
{
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
			typedef typename ft::viterator<T>				iterator;
			typedef typename ft::viterator<const T>			const_iterator;
		//	typedef typename std::vector<T>::iterator		iterator;
		//	typedef typename std::vector<T>::iterator		const_iterator;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
			
			//Default
			vector( void ): _tab(NULL), _capacity(0), _size(0), _alloc(Allocator()) {}
			//Copy
			vector( const vector & v ): _tab(NULL), _capacity(0), _size(0), _alloc(v._alloc) { *this = v; }
			explicit vector( const Allocator & alloc ): _tab(NULL), _capacity(0), _size(0), _alloc(alloc) {}
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()): _tab(NULL), _capacity(count), _size(count), _alloc(alloc)
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
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL ): _tab(NULL), _capacity(0), _size(0), _alloc(alloc)
			{
/*				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
*/				//init a 0 et push back de first a last... --> petit soucis de capacity sur le push back
	//			std::cout << "InputIT first, InputIt last, const Allocator& alloc = Allocator() constructor" << std::endl;
				InputIt		tmp = first;
				size_type	dif = 0;
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
					for (size_type i = 0; tmp != last; i++, tmp++)
						this->_alloc.construct(this->_tab + i, *tmp);
				}
					
			}
			~vector( void )
			{
				this->clear();
				if (this->capacity())
					this->_alloc.deallocate(this->_tab, this->_capacity);
		//		std::cout << "Destructor called" << std::endl;
			}

			vector &				operator=( const vector & other )
			{
				if (this == &other)
					return (*this);
				if (!this->_tab || other.size() > this->capacity())
				{
					if (this->_tab)
					{
						this->clear();
						this->_alloc.deallocate(this->_tab, this->capacity());
					}
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
				// clear puis push back de value autant de fois que count?
				this->clear();
				if (count == 0)
					return ;
				this->_size = count;
				if (this->capacity() < count)
				{
					if (this->_tab)
						this->_alloc.deallocate(this->_tab, this->_capacity);
					this->_tab = this->_alloc.allocate(count, 0);
					this->_capacity = count;
				}
				if (this->_tab)
					for (size_type i = 0; i < count; i++)
						this->_alloc.construct(&this->_tab[i], value);
			}
			template< class InputIt >
			void					assign( InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL )
			{
				difference_type	dif = this->_distance(first, last);
				this->clear();
				if (this->capacity() < static_cast<size_type>(dif))
				{
					if (this->_tab)
						this->_alloc.deallocate(this->_tab, this->capacity());
					this->_tab = this->_alloc.allocate(dif, 0);
					this->_capacity = static_cast<size_type>(dif);
				}
				if (this->_tab)
					for (size_type i = 0; first != last; i++, first++)
						this->_alloc.construct(&this->_tab[i], *first);
				this->_size = static_cast<size_type>(dif);
			}
			allocator_type			get_allocator( void ) const { return (this->_alloc); }

			//ITERATORS
			iterator				begin( void ) { return (iterator(this->data())); }
			const_iterator			begin( void ) const { return (const_iterator(this->_tab)); }
			iterator				end( void ) { return (iterator(this->data() + this->size())); }
			const_iterator			end( void ) const { return (const_iterator(&this->_tab[this->size()])); }
			reverse_iterator		rbegin( void ) { return (reverse_iterator(this->end() - 1)); }
			const_reverse_iterator	rbegin( void ) const { return (this->rbegin()); }
			reverse_iterator		rend( void ) { return (reverse_iterator(this->begin())); }
			const_reverse_iterator	rend( void ) const { return (this->rend()); }

			//CAPACITY
			size_type				size( void ) const { return (this->_size); }
			size_type				max_size( void ) const { return (this->_alloc.max_size()); }
			size_type				capacity( void ) const { return (this->_capacity); }
			bool					empty( void ) const { return (this->_size ? false : true ); }
			void					reserve (size_type n)
			{ 
				if (n <= this->_capacity)
					return ;
				else if (n > this->max_size())
					throw std::length_error("Impossible to reserve this size");
				pointer	tmp = this->_alloc.allocate(n, 0);
				for (size_type i = 0; i < this->size(); i++)
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
			reference				front( void ) { return (*this->_tab); }
			const_reference			front( void ) const { return (*this->_tab); }
			reference				back( void )
			{
				if (this->size())
					return (this->_tab[this->size() - 1]);
				return (*this->_tab);
			}
			const_reference			back( void ) const
			{
				if (this->size())
					return (this->_tab[this->size() - 1]);
				return (*this->_tab);
			}
			value_type*				data( void ) { return (this->_tab); }
			const value_type*		data( void ) const { return (this->_tab); }

			//MODIFIERS
			void					clear( void )
			{
				while (this->_size--)
					this->_alloc.destroy(&this->_tab[this->size()]);
				this->_size = 0;
			}
			iterator insert( iterator pos, const T& value )
			{
				//vector temporaire par iterator pour conserver les valeurs apres ce qu'on veut ajouter puis pop back, construct value, push back tmp??
				iterator	ite = this->end();
				if (this->size() == this->capacity())
				{
					iterator	it = this->begin();
					size_type	i = 0;
					pointer	tab = this->_alloc.allocate(this->capacity() * 2, 0);
					for (; it != pos; it++, i++)
					{
						this->_alloc.construct(&tab[i], this->_tab[i]);
						this->_alloc.destroy(&(*pos));
					}
					this->_alloc.construct(&tab[i], value);
					for (; pos != this->end(); pos++)
					{
						this->_alloc.construct(&tab[++i], *pos);
						this->_alloc.destroy(&(*pos));
					}
					this->_alloc.deallocate(this->data(), this->capacity());
					this->_capacity *= 2;
					this->_tab = tab;
				}
				else
				{
					this->_alloc.construct(&this->_tab[this->size()], *(this->end() - 1));
					while (ite != pos)
					{
						this->_alloc.destroy(&*ite);
						this->_alloc.construct(&*ite, *(ite - 1));
						ite--;
					}
					this->_alloc.construct(&*ite, value);
				}
				this->_size++;
				return (ite);
			}
			iterator insert( iterator pos, size_type count, const T& value )
			{
				if (count < 0 || pos < this->begin())
					throw std::length_error("vector::_M_fill_insert");
				size_type	tmp = this->_new_capacity(count);
				pointer		tab = this->_alloc.allocate(tmp, 0);
				size_type	y = 0;
				iterator	fill = this->begin();
				for (; fill != pos; fill++, y++)
				{
					this->_alloc.construct(&tab[y], *fill);
					this->_alloc.destroy(&*fill);
				}
				iterator	it = pos;
				for (size_type t = 0; t < count; t++)
					this->_alloc.construct(&tab[y++], value);
				for (; fill != this->end(); fill++, y++)
				{
					this->_alloc.construct(&tab[y], *fill);
					this->_alloc.destroy(&*fill);
				}
				this->_alloc.deallocate(this->data(), this->capacity());
				this->_tab = tab;
				this->_capacity = tmp;
				this->_size += count;
				return (it);
			}
			template< class InputIt >
			iterator insert( iterator pos, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL )
			{
				if (pos < this->begin())
					throw std::length_error("vector::_M_fill_insert");
				difference_type	d = this->_distance(first, last);
				size_type		tmp = this->_new_capacity(static_cast<size_type>(d));
				if (d == -1)
				{
					iterator	tmpit = this->begin() + *pos;
					for (;first != last; first++)
						this->insert(pos, *first);
					return (tmpit);
				}
				if (tmp > this->capacity())
				{
					pointer	tab = this->_alloc.allocate(tmp, 0);
					size_type	i = 0;
					for (iterator it = this->begin(); it != pos; it++, i++)
					{
						this->_alloc.construct(&tab[i], *it);
						this->_alloc.destroy(&*it);
					}
					for (; first != last; first++, i++)
						this->_alloc.construct(&tab[i], *first);
					for (; pos != this->end(); pos++, i++)
					{
						this->_alloc.construct(&tab[i], *pos);
						this->_alloc.destroy(&*pos);
					}
					this->_alloc.deallocate(this->_tab, this->capacity());
					this->_tab = tab;
					this->_capacity = tmp;
				}
				else
				{
					for (difference_type x = d; x; x--)
					{
						std::cout << "x = " << x << " size = " << this->size() << " capacity = " << this->capacity() << std::endl;
						this->_alloc.construct(this->_tab + this->size() + d, *(this->_tab + this->size() - x));
						this->_alloc.destroy(this->_tab + this->size() - x);
					}
					iterator	it = this->begin();
					while (it < pos)
						it++;
					for (; first != last; first++)
						this->_alloc.construct(&*it, *first);
				}
				this->_size = this->size() + d;
				return (pos);
			}
			iterator				erase( iterator pos )
			{
				if (pos == this->end())
					return (pos);
				iterator	tmp = pos;
				while (pos != this->end() - 1)
				{
					*pos = *(pos + 1);
					pos++;
				}
				this->_alloc.destroy(&*pos);
				this->_size--;
				return (tmp);
			}
			iterator				erase( iterator first, iterator last )
			{
				size_type	i = 0;
				iterator	it = this->begin();

				while (it != first)
					it++;
				while (it != last)
				{
					*(first + i) = *(last + i);
					it++;
					i++;
				}
				while (last != this->end() && (last + i) != this->end())
				{
					*it++ = *(last + i);
					last++;
				}
				while (i--)
				{
					this->_size--;
					this->_alloc.destroy(&this->_tab[this->size()]);
				}
				return (first);
			}
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
						pointer	tmp = this->_alloc.allocate(this->capacity() * 2, 0);
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
			void					resize( size_type count, T value = T() )
			{
				if (count > this->size())
				{
					if (count > this->capacity())
					{
						pointer		tmp;
						tmp = this->_alloc.allocate(count, 0);
						for (size_type i = 0; i < this->size(); i++)
						{
							this->_alloc.construct(&tmp[i], this->_tab[i]);
							this->_alloc.destroy(&this->_tab[i]);
						}
						this->_alloc.deallocate(this->_tab, this->_capacity);
						this->_capacity = count;
						this->_tab = tmp;
					}
					for (; this->_size < count; this->_size++)
						this->_alloc.construct(&this->_tab[this->size()], value);
				}
				else
					for (; this->_size > count;)
						this->pop_back();
			}
			void					swap( vector& other )
			{
				pointer			tab = this->_tab;
				size_type		capacity = this->_capacity;
				size_type		size = this->_size;
				Allocator		alloc = this->_alloc;

				this->_tab = other._tab;
				this->_capacity = other._capacity;
				this->_size = other._size;
				this->_alloc = other._alloc;
				other._tab = tab;
				other._capacity = capacity;
				other._size = size;
				other._alloc = alloc;
			}


		private:
			pointer			_tab;
			size_type		_capacity;
			size_type		_size;
			Allocator		_alloc;
			
			template<typename It>
			difference_type	_distance(It & first, It & last)
			{
				if (is_same<It, std::input_iterator_tag>::value)
					return (-1);
				difference_type	diff = 0;
				It	tmp = first;
				for (; tmp != last; tmp++)
					diff++;
				return (diff);
			}

			size_type		_new_capacity(size_type count)
			{
				size_type tmp = this->capacity();
				if (!tmp)
					tmp = count;
				if (tmp && this->size() + count > this->capacity())
				{
					tmp = this->size() * 2;
					if (count < this->capacity())
						while (tmp < this->size() + count)
							tmp *= 2;
					else if (count > this->capacity())
						tmp = this->size() + count;
				}
				return (tmp);
			}
	};

	template< class T, class Allocator >
	bool	operator==( const vector< T, Allocator >& lhs, const vector< T, Allocator >& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename vector<T, Allocator>::const_iterator rt = rhs.begin();
		for (typename vector<T, Allocator>::const_iterator lt = lhs.begin(); lt != lhs.end(); lt++, rt++)
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

template<class Os, class Co>
Os& operator<<(Os& os, const Co& co) 
{
	os << "{";
	for (size_t i = 0; i < co.size(); i++)
		os << ' ' << co[i];
	return os << " } ";
}

#endif
