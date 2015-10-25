@echo off

set PATH=C:\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin;%PATH%

g++ -o main.exe main.cpp input.cpp input_transformation.cpp state.cpp output_transformation.cpp output.cpp -std=c++1z -march=native -O3 -Wall -Wextra -Werror -I. -static && main.exe

pause