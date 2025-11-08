gcc -Wall -Wextra ..\exercises\ex1.c -o ..\exercises\ex1.exe
echo compiled ex1
..\exercises\ex1.exe < ex1_example1_in.txt > ex1_example1_out_mine.txt
..\exercises\ex1.exe < ex1_example2_in.txt > ex1_example2_out_mine.txt
fc ex1_example1_out_mine.txt ex1_example1_out.txt
fc ex1_example2_out_mine.txt ex1_example2_out.txt
@pause