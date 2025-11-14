echo off
gcc -Wall -Wextra ..\exercises\ex2.c -o ..\exercises\ex2.exe
echo compiled ex2
..\exercises\ex2.exe < ex2_example1_in.txt > ex2_example1_out_mine.txt
..\exercises\ex2.exe < ex2_example2_in.txt > ex2_example2_out_mine.txt
fc ex2_example1_out_mine.txt ex2_example1_out.txt
fc ex2_example2_out_mine.txt ex2_example2_out.txt
@pause