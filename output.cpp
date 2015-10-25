#include <output.hpp>

#include <mutex>
//	For:
//		std::mutex
//		std::lock_guard

#include <temporary.hpp>

static std::mutex output_main_mutex;
void output_main() {
	std::lock_guard<std::mutex> output_main_lock( output_main_mutex );
	try {
		print( "Hello", ", ", "Output", "\n" );
	} catch ( ... ) {
		throw;
	}
}
