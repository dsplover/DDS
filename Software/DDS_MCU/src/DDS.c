/*
 * DDS.c
 *
 *  Created on: 2022年4月16日
 *      Author: Fu Yuhao
 */
#include"DDS.h"

char KeyChar(unsigned char key_value)//键盘字符转换函数
{
    char key_char;
    switch(key_value)
    {
    case 1:
        key_char = '1';
        break;
    case 2:
        key_char = '2';
        break;
    case 3:
        key_char = '3';
        break;
    case 4:
        key_char = 'A';
        break;
    case 5:
        key_char = '4';
        break;
    case 6:
        key_char = '5';
        break;
    case 7:
        key_char = '6';
        break;
    case 8:
        key_char = 'B';
        break;
    case 9:
        key_char = '7';
        break;
    case 10:
        key_char = '8';
        break;
    case 11:
        key_char = '9';
        break;
    case 12:
        key_char = 'C';
        break;
    case 13:
        key_char = '*';
        break;
    case 14:
        key_char = '0';
        break;
    case 15:
        key_char = '#';
        break;
    case 16:
        key_char = 'D';
        break;
    default:
        key_char = 'N';
        break;
    }

    return key_char;
}

void DecNumSet(char key_char, unsigned long *num) //数据输入函数
{
    switch(key_char)
    {
    case '1':
        *num = *num * 10 + 1;
        break;
    case '2':
        *num = *num * 10 + 2;
        break;
    case '3':
        *num = *num * 10 + 3;
        break;
    case '4':
        *num = *num * 10 + 4;
        break;
    case '5':
        *num = *num * 10 + 5;
        break;
    case '6':
        *num = *num * 10 + 6;
        break;
    case '7':
        *num = *num * 10 + 7;
        break;
    case '8':
        *num = *num * 10 + 8;
        break;
    case '9':
        *num = *num * 10 + 9;
        break;
    case '0':
        *num = *num * 10 + 0;
        break;
    case 'A':
        *num = *num * 1000;
        break;
    case 'B':
        *num = *num * 1000000;
        break;
    default:
        break;
    }
}

void BinNumSet(char key_char, unsigned long *num) //二进制数据输入函数
{
    switch(key_char)
    {
    case '1':
        *num = *num * 2 + 1;
        break;
    case '0':
        *num = *num * 2 + 0;
        break;
    case 'A':
        *num = *num * 16;
        break;
    case 'B':
        *num = *num * 16 + 15;
        break;
    default:
        break;
    }
}

int DecBitCheck(unsigned long num)//十位数位数检查
{
    int i = 0;
    if(num == 0)
    {
        return 1;
    }
    for(i = 0; num != 0; i++)
    {
        num = num / 10;
    }
    return i;
}
