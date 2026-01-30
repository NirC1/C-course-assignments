@echo off

REM Compile test_org
gcc -Wall -Wextra test_org_tree.c ..\exercises\org_tree.c -o test_org.exe
echo compiled test_org

echo.
echo Testing org_tree on ex1_out1.txt...
echo.
test_org.exe ex1_out1.txt > org_tree_out1.txt

echo.
echo Testing org_tree on ex1_out2.txt...
echo.
test_org.exe ex1_out2.txt > org_tree_out2.txt

echo.
echo Testing org_tree on ex1_out3.txt...
echo.
test_org.exe ex1_out3.txt > org_tree_out3.txt

echo.
echo All tests run. Check org_tree_outX.txt files for results.

@pause
