@echo off

set PATH=C:\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin;%PATH%

REM Debug:
g++ -o main.exe main.cpp input.cpp input_transformation.cpp state.cpp output_transformation.cpp output.cpp input_for_windows_desktop.cpp -std=c++1z -Wall -Wextra -Werror -I. -DWINDOWS_DESKTOP -D_DEBUG -D_CONSOLE -static && main.exe

REM Release:
REM g++ -o main.exe main.cpp input.cpp input_transformation.cpp state.cpp output_transformation.cpp output.cpp input_for_windows_desktop.cpp -std=c++1z -march=native -O3 -Wall -Wextra -Werror -I. -DWINDOWS_DESKTOP -DNDEBUG -D_CONSOLE -static && main.exe

pause