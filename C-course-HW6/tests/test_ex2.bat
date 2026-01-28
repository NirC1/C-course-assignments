@echo off

REM Compile ex2
gcc -Wall -Wextra ..\exercises\ex2.c ..\exercises\org_tree.c -o ex2.exe
echo compiled ex2

echo.
echo Testing ex2 test 1...
echo.
ex2.exe ex2_clean_file_in.txt ex2_cipher_bits_in1.txt 55 > ex2_out_mine1.txt
fc ex2_out_mine1.txt ex2_out1.txt

echo.
echo Testing ex2 test 2...
echo.
ex2.exe ex2_clean_file_in.txt ex2_cipher_bits_in2.txt 49 > ex2_out_mine2.txt
fc ex2_out_mine2.txt ex2_out2.txt

echo.
echo Testing ex2 test 3...
echo.
ex2.exe ex2_clean_file_in.txt ex2_cipher_bits_in3.txt 40 > ex2_out_mine3.txt
fc ex2_out_mine3.txt ex2_out3.txt

@pause
