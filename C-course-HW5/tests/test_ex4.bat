@echo off

REM Compile ex4
gcc -Wall -Wextra ..\exercises\ex4.c ..\exercises\parser.c -o ex4.exe
echo compiled ex4

echo.
echo Testing ex4 help...
echo.
ex4.exe -h > ex4_help_out_mine.txt
fc ex4_help_out_mine.txt ex4_help_out.txt

echo.
echo Testing ex4 missing value...
echo.
ex4.exe -v 1 -l -k 17 -s 123 -d 89 -p 2 -e 1 3 > ex4_missing_value_out_mine.txt
fc ex4_missing_value_out_mine.txt ex4_missing_value_out.txt

echo.
echo Testing ex4 normal...
echo.
ex4.exe -v 1 -l 8 -t 17 -s 123 -d 83 -p 0 -e 0 > ex4_normal_out_mine.txt
fc ex4_normal_out_mine.txt ex4_normal_out.txt

echo.
echo Testing ex4 num args...
echo.
ex4.exe -v 1 -l 8 -k 17 -s -d 123 > ex4_num_args_out_mine.txt
fc ex4_num_args_out_mine.txt ex4_num_args_out.txt

echo.
echo Testing ex4 out of range...
echo.
ex4.exe -v 1 -l 2222 -k 17 -s 123 -d 89 -p 2 -e 1 > ex4_out_of_range_out_mine.txt
fc ex4_out_of_range_out_mine.txt ex4_out_of_range_out.txt

echo.
echo Testing ex4 unknown flag...
echo.
ex4.exe -v 1 -l 8 -k 17 -s 123 -d 89 -p 2 -e 1 > ex4_unknown_flag_out_mine.txt
fc ex4_unknown_flag_out_mine.txt ex4_unknown_flag_out.txt

@pause
