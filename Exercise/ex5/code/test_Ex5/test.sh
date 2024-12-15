#!/bin/bash
# Working under your working directory
# chmod +x test_Ex5/test.sh
# ./test_Ex5/test.sh
# Please 修改类的权限到public

g++ -Wall  ex5.cpp ./test_Ex5/test.cpp -o test.exe
#./test.exe


valgrind --leak-check=full ./test.exe # 检验空间泄漏
# 如果没有泄漏应该是：
# ==15755== Memcheck, a memory error detector
# ==15755== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
# ==15755== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
# ==15755== Command: ./test.exe
# ==15755== 
# ==15755== 
# ==15755== HEAP SUMMARY:
# ==15755==     in use at exit: 0 bytes in 0 blocks
# ==15755==   total heap usage: 28 allocs, 28 frees, 81,230 bytes allocated
# ==15755== 
# ==15755== All heap blocks were freed -- no leaks are possible
# ==15755== 
# ==15755== For lists of detected and suppressed errors, rerun with: -s
# ==15755== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
