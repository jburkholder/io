#include <input_for_windows_desktop.hpp>

#include <windows.h>
//	For:
//		WindowProc: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633573(v=vs.85).aspx
//		WNDCLASSEXW: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx

#include <sal.h>
//	For:
//		_In_

#include <type_traits>
//	For:
//		std::result_of

#include <temporary.hpp>

// WindowProc: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633573(v=vs.85).aspx
LRESULT CALLBACK window_procedure( _In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM );

void input_main_for_windows_desktop() {

	// LPCWSTR: https://msdn.microsoft.com/en-us/library/windows/desktop/aa383751(v=vs.85).aspx
	LPCWSTR window_class_name = L"window_class";
	LPCWSTR window_name = L"IO Framework";

	HINSTANCE instance_handle = GetModuleHandleW(
		/*_In_opt_ LPCWSTR lpModuleName: */ nullptr // If this parameter is NULL, GetModuleHandle returns a handle to the file used to create the calling process (.exe file).
	);

	debug_print("instance_handle: ", instance_handle);

	// WNDCLASSEXW: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx
	WNDCLASSEXW window_class;
	/* UINT:      */ window_class.cbSize = sizeof( window_class );
	// Window Class Styles: https://msdn.microsoft.com/en-us/library/windows/desktop/ff729176(v=vs.85).aspx
	/* UINT:      */ window_class.style = (
		CS_HREDRAW // Redraws the entire window if a movement or size adjustment changes the width of the client area.
		|
		CS_VREDRAW // Redraws the entire window if a movement or size adjustment changes the height of the client area.
		|
		CS_OWNDC   // Allocates a unique device context for each window in the class. 
	);
	/* WNDPROC:   */ window_class.lpfnWndProc = window_procedure;
	/* int:       */ window_class.cbClsExtra = 0;
	/* int:       */ window_class.cbWndExtra = 0;
	// GetModuleHandleW: https://msdn.microsoft.com/en-us/library/windows/desktop/ms683199(v=vs.85).aspx
	/* HINSTANCE: */ window_class.hInstance = instance_handle;
	// LoadIconW: https://msdn.microsoft.com/en-us/library/windows/desktop/ms648072(v=vs.85).aspx
	/* HICON:     */ window_class.hIcon = LoadIcon( nullptr, IDI_APPLICATION );
	// LoadCursorW: https://msdn.microsoft.com/en-us/library/windows/desktop/ms648391(v=vs.85).aspx
	/* HCURSOR:   */ window_class.hCursor = LoadCursor( nullptr, IDC_ARROW );
	// GetStockObject: https://msdn.microsoft.com/en-us/library/dd144925(v=vs.85).aspx
	/* HBRUSH:    */ window_class.hbrBackground = static_cast<HBRUSH>( GetStockObject( BLACK_BRUSH ) );
	/* LPCWSTR:   */ window_class.lpszMenuName = nullptr;
	/* LPCWSTR:   */ window_class.lpszClassName = window_class_name;
	/* HICON:     */ window_class.hIconSm = nullptr;

	// RegisterClassExW: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633587(v=vs.85).aspx
	// ATOM a is WORD.  WORD is an unsigned short.
	if (
		0 == RegisterClassExW(
			/* _In_ const WNDCLASSEXW * lpwcx: */ &window_class
		)
	) {
		debug_print_info;
		// GetLastError: https://msdn.microsoft.com/en-us/library/windows/desktop/ms679360(v=vs.85).aspx
		DWORD last_error = GetLastError();
		switch ( last_error ) {
		default:
			// TODO: Add relevant error handling or exception.
			return;
		}
	}

	// GetDesktopWindow: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633504(v=vs.85).aspx
	HWND desktop_window_handle = GetDesktopWindow();
	// GetDC: https://msdn.microsoft.com/en-us/library/dd144871(v=vs.85).aspx
	HDC desktop_device_context = GetDC(
		/* _In_ HWND hWnd: */ desktop_window_handle
	);
	
	// GetDeviceCaps: https://msdn.microsoft.com/en-us/library/dd144877(v=vs.85).aspx
	int screen_width = GetDeviceCaps(
		/* _In_ HDC hdc:    */ desktop_device_context,
		/* _In_ int nIndex: */ HORZRES // Width, in pixels, of the screen; or for printers, the width, in pixels, of the printable area of the page.
	);
	int screen_height = GetDeviceCaps(
		/* _In_ HDC hdc:    */ desktop_device_context,
		/* _In_ int nIndex: */ VERTRES // Height, in raster lines, of the screen; or for printers, the height, in pixels, of the printable area of the page.
	);
	debug_print( "screen_width:  ", screen_width );
	debug_print( "screen_height: ", screen_height );

	// ReleaseDC: https://msdn.microsoft.com/en-us/library/dd162920(v=vs.85).aspx
	if (
		0 == ReleaseDC(
			/* _In_ HWND hWnd: */ desktop_window_handle,
			/* _In_ HDC  hDC:  */ desktop_device_context
		)
	) {
		debug_print_info;
		// TODO: Add relevant error handling or exception.
		return;
	}

	// CreateWindowExW: https://msdn.microsoft.com/en-us/library/ms632680(v=vs.85).aspx
	HWND window_handle = CreateWindowExW(
		// Extended Window Styles: https://msdn.microsoft.com/en-us/library/ff700543(v=vs.85).aspx
		/* _In_     DWORD     dwExStyle:    */ (
			WS_EX_LEFT           // The window has generic left-aligned properties. This is the default.
			|
			WS_EX_LTRREADING     // The window text is displayed using left-to-right reading-order properties. This is the default.
			|
			WS_EX_RIGHTSCROLLBAR // The vertical scroll bar (if present) is to the right of the client area. This is the default.
			//|
			//WS_EX_TOPMOST        // The window should be placed above all non-topmost windows and should stay above them, even when the window is deactivated. To add or remove this style, use the SetWindowPos function.
			//|
			//WS_EX_TRANSPARENT    // The window should not be painted until siblings beneath the window (that were created by the same thread) have been painted. The window appears transparent because the bits of underlying sibling windows have already been painted. To achieve transparency without these restrictions, use the SetWindowRgn function.
		),
		/* _In_opt_ LPCWSTR   lpClassName:  */ window_class_name,
		/* _In_opt_ LPCWSTR   lpWindowName: */ window_name,
		// Window Styles: https://msdn.microsoft.com/en-us/library/ms632600(v=vs.85).aspx
		/* _In_     DWORD     dwStyle:      */ (
			WS_CLIPCHILDREN // Excludes the area occupied by child windows when drawing occurs within the parent window. This style is used when creating the parent window.
			|
			WS_CLIPSIBLINGS // Clips child windows relative to each other; that is, when a particular child window receives a WM_PAINT message, the WS_CLIPSIBLINGS style clips all other overlapping child windows out of the region of the child window to be updated. If WS_CLIPSIBLINGS is not specified and child windows overlap, it is possible, when drawing within the client area of a child window, to draw within the client area of a neighboring child window.
			|
			WS_POPUP        // The windows is a pop-up window. This style cannot be used with the WS_CHILD style.
		),
		/* _In_     int       x:            */ 0,
		/* _In_     int       y:            */ 0,
		/* _In_     int       nWidth:       */ screen_width,
		/* _In_     int       nHeight:      */ screen_height,
		/* _In_opt_ HWND      hWndParent:   */ nullptr, // A handle to the parent or owner window of the window being created. To create a child window or an owned window, supply a valid window handle. This parameter is optional for pop-up windows.
		/* _In_opt_ HMENU     hMenu:        */ nullptr, // A handle to a menu, or specifies a child-window identifier, depending on the window style. For an overlapped or pop-up window, hMenu identifies the menu to be used with the window; it can be NULL if the class menu is to be used.
		// GetModuleHandleW: https://msdn.microsoft.com/en-us/library/windows/desktop/ms683199(v=vs.85).aspx
		/* _In_opt_ HINSTANCE hInstance:    */ instance_handle,
		/* _In_opt_ LPVOID    lpParam:      */ nullptr  // Pointer to a value to be passed to the window through the CREATESTRUCT structure (lpCreateParams member) pointed to by the lParam param of the WM_CREATE message. This message is sent to the created window by this function before it returns. lpParam may be NULL if no additional data is needed. 
	);
	
	if ( window_handle == nullptr ) {
		debug_print_info;
		// TODO: Add error handling / exception since the window was not create
		return;
	}

	// ShowWindow: https://msdn.microsoft.com/en-us/library/ms633548(v=vs.85).aspx
	BOOL window_previously_visible = ShowWindow(
		/* _In_ HWND hWnd:     */ window_handle,
		/* _In_ int  nCmdShow: */ SW_SHOW // Activates the window and displays it in its current size and position.
	);
	(void) window_previously_visible;

	// UpdateWindow: https://msdn.microsoft.com/en-us/library/dd145167(v=vs.85).aspx
	if (
		0 == UpdateWindow(
			/* _In_ HWND hWnd: */ window_handle
		)
	) {
		debug_print_info;
		// TODO: Add error handling / exception
		return;
	}

	// MSG: https://msdn.microsoft.com/en-us/library/ms644958(v=vs.85).aspx
	MSG message;
	// GetMessageW: https://msdn.microsoft.com/en-us/library/ms644936(v=vs.85).aspx
	while (
		0 != GetMessageW(
			/* _Out_    LPMSG lpMsg:         */ &message,
			/* _In_opt_ HWND  hWnd:          */ nullptr, // A handle to the window whose messages are to be retrieved. If hWnd is NULL, GetMessage retrieves messages for any window that belongs to the current thread, and any messages on the current thread's message queue whose hwnd value is NULL (see the MSG structure). Therefore if hWnd is NULL, both window messages and thread messages are processed.
			/* _In_     UINT  wMsgFilterMin: */ 0, // The integer value of the lowest message value to be retrieved. If wMsgFilterMin and wMsgFilterMax are both zero, GetMessage returns all available messages (that is, no range filtering is performed). 
			/* _In_     UINT  wMsgFilterMax: */ 0  // The integer value of the highest message value to be retrieved. If wMsgFilterMin and wMsgFilterMax are both zero, GetMessage returns all available messages (that is, no range filtering is performed).
		)
	) {
		// TranslateMessage: https://msdn.microsoft.com/en-us/library/ms644955(v=vs.85).aspx
		BOOL translate_message_return_value = TranslateMessage(
			/* _In_ const MSG * lpMsg: */ &message
		);
		(void) translate_message_return_value;
		
		// DispatchMessageW: https://msdn.microsoft.com/en-us/library/ms644934(v=vs.85).aspx
		LRESULT window_procedure_return_value = DispatchMessageW(
			/* _In_ const MSG * lpmsg: */ &message
		);
		(void) window_procedure_return_value;
	}
	debug_print_info;
}

// WindowProc: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633573(v=vs.85).aspx
LRESULT CALLBACK window_procedure(
	_In_ HWND   window_handle,
	_In_ UINT   message,
	_In_ WPARAM w_param,
	_In_ LPARAM l_param
) {
	switch ( message ) {
	default:
		break;
	}
	// DefWindowProcW: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633572(v=vs.85).aspx
	return /* LRESULT */ DefWindowProcW(
		/* _In_ HWND   hWnd:   */ window_handle,
		/* _In_ UINT   Msg:    */ message,
		/* _In_ WPARAM wParam: */ w_param,
		/* _In_ LPARAM lParam: */ l_param
	);
}
