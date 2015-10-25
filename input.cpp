#include <input.hpp>

#include <mutex>
//	For:
//		std::mutex
//		std::lock_guard

#include <temporary.hpp>

static std::mutex input_main_mutex;
void input_main() {
	std::lock_guard<std::mutex> input_main_lock( input_main_mutex );
	try {
		print( "Hello", ", ", "Input", "\n" );
	} catch ( ... ) {
		throw;
	}
}
