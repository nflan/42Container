/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:18:36 by nflan             #+#    #+#             */
/*   Updated: 2023/01/05 12:49:44 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iterator>
#include "tools.hpp"
#include "viterator.hpp"
#include "iterator.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef typename Allocator::reference					reference;
			typedef typename Allocator::const_reference				const_reference;
			typedef typename Allocator::pointer						pointer;
			typedef typename Allocator::const_pointer				const_pointer;
			typedef typename ft::viterator<value_type>						iterator;
			typedef typename ft::viterator<const value_type>					const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			
			explicit vector( const allocator_type & alloc = allocator_type() ): _tab(NULL), _capacity(0), _size(0), _alloc(alloc) {}
			explicit vector( size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()): _tab(NULL), _capacity(count), _size(count), _alloc(alloc)
			{
				if (count > alloc.max_size())
					throw std::length_error("vector: max_size overflow");
				if (this->_capacity)
				{
					this->_tab = this->_alloc.allocate(this->capacity(), 0);
					for (size_type i = 0; i < this->capacity(); i++)
						this->_alloc.construct(&this->_tab[i], value);
				}
			}
			template< class InputIt >
			vector( InputIt first, InputIt last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL ): _tab(NULL), _capacity(0), _size(0), _alloc(alloc)
			{
				difference_type	dif = this->_distance(first, last);
				if (dif == -1)
				{
					for (; first != last; first++)
						this->push_back(*first);
					return ;
				}
				else if (static_cast<size_type>(dif) > alloc.max_size())
					throw std::length_error("vector: max_size overflow");
				this->_size = dif;
				this->_capacity = dif;
				this->_tab = NULL;
				this->_alloc = alloc;
				if (this->_capacity)
				{
					this->_tab = this->_alloc.allocate(this->_capacity, 0);
					for (size_type i = 0; first != last; i++, first++)
						this->_alloc.construct(this->_tab + i, *first);
				}
			}
			vector( const vector & v ): _tab(NULL), _capacity(0), _size(0), _alloc(v._alloc) { *this = v; }
			~vector( void )
			{
				this->clear();
				if (this->capacity())
					this->_alloc.deallocate(this->_tab, this->_capacity);
			}

			vector &				operator=( const vector & other )
			{
				if (this == &other)
					return (*this);
				this->clear();
				this->_alloc = other._alloc;
				this->_size = other._size;
				if (!this->_tab || other.size() > this->capacity())
				{
					if (this->_tab)
						this->_alloc.deallocate(this->_tab, this->capacity());
					this->_capacity = other.size();
					if (this->_capacity)
						this->_tab = this->_alloc.allocate(this->capacity(), 0);
				}
				if (this->_tab)
					for (size_type i = 0; i < other.size(); i++)
						this->_alloc.construct(&this->_tab[i], other._tab[i]);
				return (*this);
			}
			void					assign( size_type count, const value_type& value )
			{
				size_type	i = 0;
				if (count > this->max_size())
					throw std::length_error("vector:assign");
				if (count < this->capacity())
				{
					for (; i < this->size() && i < count; i++)
						this->_tab[i] = value;
					for (; i < count; i++)
						this->_alloc.construct(&this->_tab[i], value);
					for (size_type j = count; j < this->size(); j++)
						this->_alloc.destroy(this->_tab + j);
					this->_size = count;
					return ;
				}
				this->clear();
				if (count <= 0)
					return ;
				this->_size = count;
				if (this->capacity() < count)
				{
					if (this->_tab)
						this->_alloc.deallocate(this->_tab, this->_capacity);
					this->_tab = this->_alloc.allocate(count, 0);
					this->_capacity = count;
				}
				for (; i < count; i++)
					this->_alloc.construct(&this->_tab[i], value);
			}
			template< class InputIt >
			void					assign( InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL )
			{
				difference_type	dif = this->_distance(first, last);
				size_type		count = static_cast<size_type>(dif);
				size_type	i = 0;
				if (dif == -1)
				{
					this->clear();
					for (;first != last; first++)
						this->push_back(*first);
					return ;
				}
				else if (static_cast<size_type>(dif) > this->max_size())
					throw std::length_error("vector:assign");
				if (static_cast<size_type>(dif) < this->capacity())
				{
					for (; i < this->size() && first != last; i++, first++)
						this->_tab[i] = *first;
					for (; first != last; i++, first++)
						this->_alloc.construct(&this->_tab[i], *first);
					for (size_type j = count; j < this->size(); j++)
						this->_alloc.destroy(this->_tab + j);
					this->_size = static_cast<size_type>(dif);
					return ;
				}
				this->clear();
				this->reserve(count);
				for (; first != last; i++, first++)
					this->_alloc.construct(&this->_tab[i], *first);
				this->_size = static_cast<size_type>(dif);
			}
			allocator_type			get_allocator( void ) const { return (this->_alloc); }

			//ITERATORS
			iterator				begin( void ) { return (iterator(this->data())); }
			const_iterator			begin( void ) const { return (const_iterator(this->data())); }
			iterator				end( void ) { return (iterator(this->data() + this->size())); }
			const_iterator			end( void ) const { return (const_iterator(&this->_tab[this->size()])); }
			reverse_iterator		rbegin( void ) { return (reverse_iterator(this->end())); }
			const_reverse_iterator	rbegin( void ) const { return (const_reverse_iterator(this->end())); }
			reverse_iterator		rend( void ) { return (reverse_iterator(this->begin())); }
			const_reverse_iterator	rend( void ) const { return (const_reverse_iterator(this->begin())); }

			//CAPACITY
			size_type				size( void ) const { return (this->_size); }
			size_type				max_size( void ) const { return (this->_alloc.max_size()); }
			size_type				capacity( void ) const { return (this->_capacity); }
			bool					empty( void ) const { return (this->_size ? false : true ); }
			void					reserve (size_type n)
			{ 
				if (n <= this->capacity())
					return ;
				else if (n > this->max_size())
					throw std::length_error("vector::reserve");
				pointer	tmp = NULL;
				if (n > 0)
				{
					tmp = this->_alloc.allocate(n, 0);
					for (size_type i = 0; i < this->size(); i++)
					{
						this->_alloc.construct(&tmp[i], this->_tab[i]);
						this->_alloc.destroy(&this->_tab[i]);
					}
				}
				if (this->capacity())
					this->_alloc.deallocate(this->_tab, this->capacity());
				this->_capacity = n;
				this->_tab = tmp;
			}

			//ELEMENT ACCESS
			reference				at( size_type pos )
			{
				if (pos >= 0 && pos < this->size())
					return (this->_tab[pos]);
				throw std::out_of_range("Out of range");
			}
			const_reference			at( size_type pos ) const
			{
				if (pos >= 0 && pos < this->size())
					return (this->_tab[pos]);
				throw std::out_of_range("Out of range");
			}
			reference				operator[]( size_type pos ) { return (this->_tab[pos]); }
			const_reference			operator[]( size_type pos ) const { return (this->_tab[pos]); }
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
			iterator insert( iterator pos, const value_type& value )
			{
				iterator	it = this->begin();
				size_type	i = 0;
				if (!this->capacity() || pos == this->end())
				{
					this->push_back(value);
					return (this->end() - 1);
				}
				else if (this->size() == this->capacity())
				{
					if (this->capacity() * 2 > this->max_size())
						throw std::length_error("vector::_M_fill_insert");
					pointer	tab = this->_alloc.allocate(this->capacity() * 2, 0);
					for (; it != pos; it++, i++)
					{
						this->_alloc.construct(tab + i, this->_tab[i]);
						this->_alloc.destroy(this->_tab + i);
					}
					this->_alloc.construct(tab + i, value);
					iterator ret(tab + i);
					i++;
					for (; pos != this->end(); pos++, i++)
					{
						this->_alloc.construct(tab + i, *pos);
						this->_alloc.destroy(&*pos);
					}
					this->_alloc.deallocate(this->_tab, this->capacity());
					this->_capacity *= 2;
					this->_tab = tab;
					this->_size++;
					return (ret);
				}
				this->_alloc.construct(&this->_tab[this->size()], this->_tab[this->size() - 1]);
				for (iterator ite = this->end() - 1; ite > pos; ite--)
					*ite = *(ite - 1);
				*pos = value;
				this->_size++;
				return (pos);
			}
			iterator insert( iterator pos, size_type count, const value_type& value )
			{
				if (count < 0 || pos < this->begin() || count > this->_alloc.max_size())
					throw std::length_error("vector::_M_fill_insert");
				if (pos == this->end())
				{
					for (; count; count--)
						this->push_back(value);
					return (pos);
				}
				pointer		tab = NULL;
				size_type	i = 0;
				if (this->size() + count <= this->capacity())
				{
					iterator	ite = this->end() - 1;
					size_type	j = 0;
					for (; ite >= pos && ite + count >= this->end(); ite--)
						this->_alloc.construct(&*ite + count, *ite);
					for (; ite >= pos; ite--)
						*(ite + count) = *ite;
					for (; pos + j < this->end() && j < count; j++)
						*(pos + j) = value;
					for (; j < count; j++)
						this->_alloc.construct(&*pos + j, value);
					this->_size += count;
					return (pos);
				}
				tab = this->_alloc.allocate(this->size() + count, 0);
				for (iterator it = this->begin(); it != pos && it != this->end(); it++, i++)
				{
					this->_alloc.construct(&tab[i], this->_tab[i]);
					this->_alloc.destroy(&this->_tab[i]);
				}
				size_type	previ = i;
				for (size_type c = count; c > 0; c--, i++)
					this->_alloc.construct(&tab[i], value);
				for (; previ < this->size(); previ++, i++)
				{
					this->_alloc.construct(&tab[i], this->_tab[previ]);
					this->_alloc.destroy(&this->_tab[previ]);
				}
				if (this->capacity())
					this->_alloc.deallocate(this->_tab, this->capacity());
				this->_capacity = this->size() + count;
				this->_size += count;
				this->_tab = tab;
				return (pos);
			}
			template< class InputIt >
			iterator insert( iterator pos, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value,InputIt>::type* = NULL )
			{
				if (pos < this->begin())
					throw std::length_error("vector::_M_fill_insert");
				if (first == last)
					return (pos);
				difference_type	d = this->_distance(first, last);
				size_type		i = 0;
				size_type		count = static_cast<size_type>(d);
				if (!d)
					return (pos);
				if (d == -1)
				{
					iterator	tmpit = this->begin();
					size_type	beg = 0;
					size_type	size = this->size();
					for (; tmpit != pos && tmpit != this->end() && beg < this->size(); tmpit++)
						beg++;
					if (beg != this->size())
					{
						pointer	tab = this->_alloc.allocate(size - beg, 0);
						for (i = 0; tmpit != this->end(); tmpit++, i++)
							this->_alloc.construct(&tab[i], *tmpit);
						for (i = 0; i < size - beg; i++)
							this->pop_back();
						for (;first != last; first++)
							this->push_back(*first);
						for (i = 0; i < size - beg; i++)
						{
							this->push_back(tab[i]);
							this->_alloc.destroy(&tab[i]);
						}
						this->_alloc.deallocate(tab, size - beg);
					}
					else
						for (;first != last; first++)
							this->push_back(*first);
					return (pos);
				}
				if (this->capacity() > count && pos == this->end())
				{
					for (; first != last; first++)
						this->push_back(*first);
					return (pos);
				}
				size_type	tmp = this->_new_capacity(count);
				if (tmp <= this->capacity())
				{
					iterator	ite = this->end() - 1;
					size_type	j = 0;
					for (; ite >= pos && ite + count >= this->end(); ite--)
						this->_alloc.construct(&*ite + count, *ite);
					for (; ite >= pos; ite--)
						*(ite + count) = *ite;
					for (; pos + j < this->end() && j < count; j++, first++)
						*(pos + j) = *first;
					for (; j < count; j++, first++)
						this->_alloc.construct(&*pos + j, *first);
					this->_size += count;
					return (pos);
				}
				pointer	tab = this->_alloc.allocate(tmp, 0);
				size_type	temp = this->size();
				for (iterator it = this->begin(); it != pos && it != this->end(); it++, i++)
				{
					this->_alloc.construct(&tab[i], this->_tab[i]);
					this->_alloc.destroy(&this->_tab[i]);
				}
				iterator ret(tab + i);
				for (; first != last; first++, i++)
					this->_alloc.construct(&tab[i], *first);
				for (; pos != this->end(); pos++, i++)
				{
					this->_alloc.construct(&tab[i], *pos);
					this->_alloc.destroy(&*pos);
				}
				if (this->capacity())
					this->_alloc.deallocate(this->data(), this->capacity());
				this->_capacity = tmp;
				this->_tab = tab;
				this->_size = temp + d;
				return (ret);
			}
			iterator				erase( iterator pos )
			{
				if (pos == this->end())
					return (pos);
				iterator	tmp = pos;
				if (this->capacity())
				{
					for (; pos + 1 != this->end(); pos++)
						*pos = *(pos + 1);
					this->pop_back();
				}
				return (tmp);
			}
			iterator				erase( iterator first, iterator last )
			{
				size_type	i = 0;
				iterator	it = first;

				if (first == last)
					return (last);
				for (; it != last && last + i != this->end(); it++, i++)
					*it = *(last + i);
				if (last + i == this->end())
					for (; it != last; i++, it++) {}
				else
					for (; last + i != this->end(); it++, last++)
						*it = *(last + i);
				while (i-- > 0)
					this->pop_back();
				return (first);
			}
			void					push_back( const value_type& val )
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
						if (this->capacity() * 2 > this->max_size())
							throw std::length_error("vector: max_size overflow");
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
					this->_size--;
					this->_alloc.destroy(&this->_tab[this->size()]);
				}
			}
			void					resize( size_type count, value_type value = value_type() )
			{
				if (count > this->max_size())
					throw std::length_error("vector::_M_fill_insert");
				if (count > this->size())
				{
					if (count >= this->capacity())
					{
						pointer		tmp;
						tmp = this->_alloc.allocate(count, 0);
						for (size_type i = 0; i < this->size(); i++)
						{
							this->_alloc.construct(&tmp[i], this->_tab[i]);
							this->_alloc.destroy(&this->_tab[i]);
						}
						if (this->capacity())
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
			difference_type	_distance(It & first, It & last, typename ft::enable_if<ft::is_same<typename iterator_traits<It>::iterator_category, std::input_iterator_tag>::value, It>::type* = NULL)
			{
				(void) first, (void) last;
				return (-1);
			}
			template<typename It>
			difference_type	_distance(It & first, It & last, typename ft::enable_if<ft::is_same<typename iterator_traits<It>::iterator_category, std::output_iterator_tag>::value, It>::type* = NULL)
			{
				(void) first, (void) last;
				return (-1);
			}
			template<typename It>
			difference_type	_distance(It & first, It & last, typename ft::enable_if<ft::is_same<typename iterator_traits<It>::iterator_category, std::random_access_iterator_tag>::value, It>::type* = NULL)
			{
				return (last - first);
			}
			template<typename It>
			difference_type	_distance(It & first, It & last, typename ft::enable_if<ft::is_same<typename iterator_traits<It>::iterator_category, std::forward_iterator_tag>::value, It>::type* = NULL)
			{
				difference_type	diff = 0;
				It	tmp = first;
				for (; tmp != last; tmp++)
					diff++;
				return (diff);
			}
			template<typename It>
			difference_type	_distance(It & first, It & last, typename ft::enable_if<ft::is_same<typename iterator_traits<It>::iterator_category, std::bidirectional_iterator_tag>::value, It>::type* = NULL)
			{
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
					if (count <= this->capacity())
						while (tmp < this->size() + count)
							tmp *= 2;
					else if (count > this->capacity())
						tmp = this->size() + count;
				}
				if (tmp > this->max_size())
					throw std::length_error("vector: max_size overflow");
				return (tmp);
			}
	};

	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) { lhs.swap(rhs); }

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
}

#endif
