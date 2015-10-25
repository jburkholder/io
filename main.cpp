#include <mutex>
//	For:
//		std::mutex
//		std::lock_guard

#include <thread>
//	For:
//		std::thread

#include <input.hpp>
//	For:
//		input_main

#include <input_transformation.hpp>
//	For:
//		input_transformation_main

#include <state.hpp>
//	For:
//		state_main

#include <output_transformation.hpp>
//	For:
//		output_transformation_main

#include <output.hpp>
//	For:
//		output_main

#include <temporary.hpp>

static std::mutex main_mutex;
// input_thread:
int main() {
	std::lock_guard<std::mutex> main_lock( main_mutex );
	try {
		std::thread input_transformation_thread( input_transformation_main );
		std::thread state_thread( state_main );
		std::thread output_transformation_thread( output_transformation_main );
		std::thread output_thread( output_main );
		
		input_main();

		output_thread.join();
		output_transformation_thread.join();
		state_thread.join();
		input_transformation_thread.join();
	} catch ( ... ) {
		
	}
}