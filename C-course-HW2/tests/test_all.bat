echo off
gcc -Wall -Wextra ..\exercises\ex1.c -o ..\exercises\ex1.exe
echo compiled ex1

gcc -Wall -Wextra ..\exercises\ex2.c -o ..\exercises\ex2.exe
echo compiled ex2

gcc -Wall -Wextra ..\exercises\ex3.c -o ..\exercises\ex3.exe
echo compiled ex3


..\exercises\ex1.exe < ex1_example1_in.txt > ex1_example1_out_mine.txt
..\exercises\ex2.exe < ex2_example1_in.txt > ex2_example1_out_mine.txt
..\exercises\ex3.exe < ex3_example1_in.txt > ex3_example1_out_mine.txt
..\exercises\ex3.exe < ex3_example2_in.txt > ex3_example2_out_mine.txt
..\exercises\ex3.exe < ex3_example3_in.txt > ex3_example3_out_mine.txt
..\exercises\ex3.exe < ex3_example4_in.txt > ex3_example4_out_mine.txt

fc ex1_example1_out_mine.txt ex1_example1_out.txt
fc ex2_example1_out_mine.txt ex2_example1_out.txt
fc ex3_example1_out_mine.txt ex3_example1_out.txt
fc ex3_example2_out_mine.txt ex3_example2_out.txt
fc ex3_example3_out_mine.txt ex3_example3_out.txt
fc ex3_example4_out_mine.txt ex3_example4_out.txt

@pause