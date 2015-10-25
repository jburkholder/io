@echo off
set PATH=C:\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin;%PATH%
g++ -o main.exe main.cpp -std=c++1z -Wall -Wextra -Werror -static && main.exe
pause