#include <input_transformation.hpp>

#include <mutex>
//	For:
//		std::mutex
//		std::lock_guard

#include <temporary.hpp>

static std::mutex input_transformation_main_mutex;
void input_transformation_main() {
	std::lock_guard<std::mutex> input_transformation_main_lock( input_transformation_main_mutex );
	try {
		print( "Hello", ", ", "Input Transformation", "\n" );
	} catch ( ... ) {
		throw;
	}
}
