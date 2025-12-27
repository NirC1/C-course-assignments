@echo off

REM Compile ex2
gcc -Wall -Wextra ..\exercises\ex2.c -o ex2.exe
echo compiled ex2

echo.
echo Testing ex2 with 18...
echo.

ex2.exe < ex2_18_in.txt > ex2_18_out_mine.txt
fc ex2_18_out_mine.txt ex2_18_out.txt

echo.
echo Testing ex2 with 9...
echo.

ex2.exe < ex2_9_in.txt > ex2_9_out_mine.txt
fc ex2_9_out_mine.txt ex2_9_out.txt

@pause
