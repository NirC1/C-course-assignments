@echo off

REM Compile ex1
gcc -Wall -Wextra ..\exercises\ex1.c -o ex1.exe
echo compiled ex1

echo.
echo Testing ex1 with 15...
echo.

ex1.exe < ex1_15_in.txt > ex1_15_out_mine.txt
fc ex1_15_out_mine.txt ex1_15_out.txt

echo.
echo Testing ex1 with 2147483648...
echo.

ex1.exe < ex1_2147483648_in.txt > ex1_2147483648_out_mine.txt
fc ex1_2147483648_out_mine.txt ex1_2147483648_out.txt

@pause
