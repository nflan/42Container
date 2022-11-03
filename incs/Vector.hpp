#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
	public:
		explicit Vector( const allocator_type& alloc = allocator_type() );
		explicit Vector( size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type() );
		template <class InputIterator> Vector( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type() );
		Vector( const vector & );
		~Vector( void );

		Vector &	operator=( const Vector & );

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



	private:
}

#endif
