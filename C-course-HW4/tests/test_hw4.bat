@echo off

REM Compile test executables into the tests folder
gcc -Wall -Wextra test_song.c ..\exercises\song.c -o test_song.exe
echo compiled test_song

gcc -Wall -Wextra test_queue.c ..\exercises\song.c ..\exercises\database.c ..\exercises\queue.c -o test_queue.exe
echo compiled test_queue

echo.
echo Testing song output...
echo.

test_song.exe > print_song_out_mine.txt
fc print_song_out_mine.txt print_song_out.txt

echo.
echo Testing queue output...
echo.

test_queue.exe > print_queue_out_mine.txt
fc print_queue_out_mine.txt print_queue_out.txt

@pause
