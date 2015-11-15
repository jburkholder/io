#include <input.hpp>

#include <mutex>
//	For:
//		std::mutex
//		std::lock_guard

#ifdef WINDOWS_DESKTOP
#include <input_from_windows_desktop.hpp>
//	For:
//		input_main_from_windows_desktop
#endif

#include <temporary.hpp>

static std::mutex input_main_mutex;
void input_main() {
	std::lock_guard<std::mutex> input_main_lock( input_main_mutex );
	try {
		debug_print( "Hello", ", ", "Input" );

	#ifdef WINDOWS_DESKTOP
		input_main_from_windows_desktop();
	#endif

	} catch ( ... ) {
		throw;
	}
}
