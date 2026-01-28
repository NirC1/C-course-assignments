@echo off

REM Compile ex1
gcc -Wall -Wextra ..\exercises\ex1.c -o ex1.exe
echo compiled ex1

echo.
echo Testing ex1 test 1...
echo.
ex1.exe ex1_in1.txt ex1_out_mine_1.txt
fc ex1_out_mine_1.txt ex1_out1.txt

echo.
echo Testing ex1 test 2...
echo.
ex1.exe ex1_in2.txt ex1_out_mine_2.txt
fc ex1_out_mine_2.txt ex1_out2.txt

echo.
echo Testing ex1 test 3...
echo.
ex1.exe ex1_in3.txt ex1_out_mine_3.txt
fc ex1_out_mine_3.txt ex1_out3.txt

@pause
