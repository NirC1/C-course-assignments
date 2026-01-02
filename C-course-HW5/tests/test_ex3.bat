@echo off

REM Compile ex3
gcc -Wall -Wextra ..\exercises\ex3.c -o ex3.exe
echo compiled ex3

echo.
echo Testing ex3 with 4 bytes...
echo.

ex3.exe ex3_4_bytes.bin > ex3_4_bytes_out_mine.txt
fc ex3_4_bytes_out_mine.txt ex3_4_bytes_out.txt

echo.
echo Testing ex3 with 7 bytes repeated...
echo.

ex3.exe ex3_7_bytes_repeated.bin > ex3_7_bytes_repeated_out_mine.txt
fc ex3_7_bytes_repeated_out_mine.txt ex3_7_bytes_repeated_out.txt

@pause
