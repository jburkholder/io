#pragma once

#include <mutex>
#include <iostream>
#include <type_traits>

template <typename T = void>
struct global {
public:
	static std::mutex print_mutex;
};
template <typename T>
std::mutex global<T>::print_mutex;

template <typename argument_type = void>
void print_implementation() {
	// No operation.
}

template <typename argument_type, typename... argument_types>
void print_implementation( argument_type && argument, argument_types &&... arguments ) {
	std::cout << std::forward<argument_type>( argument );
	print_implementation( std::forward<argument_types>( arguments )... );
}

template <typename... argument_types>
void print( argument_types &&... arguments ) {
	using mutex_type = decltype( global<>::print_mutex );
	std::lock_guard<mutex_type> lock( global<>::print_mutex );
	print_implementation( std::forward<argument_types>( arguments )... );
}
