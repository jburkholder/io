#include <output_transformation.hpp>

#include <mutex>
//	For:
//		std::mutex
//		std::lock_guard

#include <temporary.hpp>

static std::mutex output_transformation_main_mutex;
void output_transformation_main() {
	std::lock_guard<std::mutex> output_transformation_main_lock( output_transformation_main_mutex );
	try {
		debug_print( "Hello", ", ", "Output Transformation" );
	} catch ( ... ) {
		throw;
	}
}
