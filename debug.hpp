#pragma once

#ifdef _DEBUG

	#include <mutex>
	#include <type_traits>
	#include <iostream>

	template <typename T = void>
	struct global {
	public:
		static std::mutex print_mutex;
	};
	template <typename T>
	std::mutex global<T>::print_mutex;

	template <typename argument_type = void>
	void print_implementation() {
		std::wcout << "\r\n";
	}

	template <typename argument_type, typename... argument_types>
	void print_implementation( argument_type && argument, argument_types &&... arguments ) {
		std::wcout << std::forward<argument_type>( argument );
		print_implementation( std::forward<argument_types>( arguments )... );
	}

	template <typename... argument_types>
	void print( argument_types &&... arguments ) {
		using mutex_type = decltype( global<>::print_mutex );
		std::lock_guard<mutex_type> lock( global<>::print_mutex );
		print_implementation( std::forward<argument_types>( arguments )... );
	}

	#define debug_print(...) print( __VA_ARGS__ )

	#define debug_print_info debug_print("ERROR: LINE ", __LINE__)

	#ifdef _MSC_VER
		#define debug_print_function debug_print(__FUNCSIG__)
	#else
		#define debug_print_function debug_print(__func__)
	#endif

#else // _DEBUG

	#define debug_print(...)

	#define debug_print_info

	#define debug_print_function
	
#endif // _DEBUG
