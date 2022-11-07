/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:18:36 by nflan             #+#    #+#             */
/*   Updated: 2022/11/07 14:54:46 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace ft {

	template < class T, class Allocator = allocator<T> >
	class vector {
		public:
			typedef T					value_type;
			typedef unsigned int		size_type;
			typedef vector<T>::iterator	iterator;
			typedef vector<T>::const_iterator	const_iterator;
			typedef	allocator_type;
			typedef vector<T>::reference		reference;
			typedef vector<T>::const_reference	const_reference;
			
			explicit vector( const allocator_type& alloc = allocator_type() );
			explicit vector( size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type() );
			template <class InputIterator>
				vector( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type() );
			vector( const vector & );
			~vector( void ) {};

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
			const_iterator			cbegin( void ) const noexcept;
			const_iterator			cend( void ) const noexcept;
			const_reverse_iterator	crbegin( void ) const noexcept;

			//CAPACITY
			size_type				size() const;
			size_type				max_size() const;
			void					resize(size_type n, value_type val = value_type());
			size_type				capacity() const;
			bool					empty() const;
			void					reserve (size_type n);
			void					shrink_to_fit();

			//ELEMENT ACCESS
			reference				operator[](size_type n);
			const_reference			operator[](size_type n) const;
			reference				at(size_type n);
			const_reference			at(size_type n) const;
			reference				front();
			const_reference			front() const;
			reference				back();
			const_reference			back() const;
			value_type*				data() noexcept;
			const value_type*		data() const noexcept;

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
			iterator				erase(iterator position);
			iterator				erase(iterator first, iterator last);
			void					swap(vector& x);
			void					clear( void );
			template <class... Args>
				iterator			emplace(const_iterator position, Args&&... args);
			template <class... Args>
				void				emplace_back(Args&&... args);

			//ALLOCATOR
			allocator_type						get_allocator( void ) const;

		private:
		};

}

#endif
