echo off

gcc -Wall -Wextra ..\exercises\ex1.c -o ..\exercises\ex1.exe
echo compiled ex1

gcc -Wall -Wextra ..\exercises\ex2.c -o ..\exercises\ex2.exe
echo compiled ex2

echo.
echo Testing ex1...
echo.

..\exercises\ex1.exe < ex1_2_winner_1_diag_up_in.txt > ex1_2_winner_1_diag_up_out_mine.txt
..\exercises\ex1.exe < ex1_3_tie_in.txt > ex1_3_tie_out_mine.txt

fc ex1_2_winner_1_diag_up_out_mine.txt ex1_2_winner_1_diag_up_out.txt
fc ex1_3_tie_out_mine.txt ex1_3_tie_out.txt

echo.
echo Testing ex2...
echo.

..\exercises\ex2.exe < ex2_example1_in.txt > ex2_example1_out_mine.txt
..\exercises\ex2.exe < ex2_example2_in.txt > ex2_example2_out_mine.txt

fc ex2_example1_out_mine.txt ex2_example1_out.txt
fc ex2_example2_out_mine.txt ex2_example2_out.txt

@pause