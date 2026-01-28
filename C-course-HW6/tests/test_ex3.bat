@echo off

REM Compile ex3
gcc -Wall -Wextra ..\exercises\ex3.c ..\exercises\fixed_point.c -o ex3.exe
echo compiled ex3

echo.
echo Testing ex3 case 1...
echo.
REM Arguments from ex3_in1.txt
ex3.exe 200 1002 1200 9012 12 > ex3_out1_mine.txt
fc ex3_out1_mine.txt ex3_out1.txt

echo.
echo Testing ex3 case 2...
echo.
REM Arguments from ex3_in2.txt
ex3.exe 10200 4000 4900 2000 14 > ex3_out2_mine.txt
fc ex3_out2_mine.txt ex3_out2.txt

@pause
