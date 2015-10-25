#include <state.hpp>

#include <mutex>
//	For:
//		std::mutex
//		std::lock_guard

#include <temporary.hpp>

static std::mutex state_main_mutex;
void state_main() {
	std::lock_guard<std::mutex> state_main_lock( state_main_mutex );
	try {
		debug_print( "Hello", ", ", "State" );
	} catch ( ... ) {
		throw;
	}
}
