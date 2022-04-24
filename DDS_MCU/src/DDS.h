/*
 * DDS.h
 *
 *  Created on: 2022年4月16日
 *      Author: Fu Yuhao
 */

#ifndef SRC_DDS_H_
#define SRC_DDS_H_

char KeyChar(unsigned char key_value);//键盘字符转换函数
void DecNumSet(char key_char, unsigned long *num);//数据输入函数
void BinNumSet(char key_char, unsigned long *num);//二进制数据输入函数
int DecBitCheck(unsigned long num);//十位数位数检查

#endif /* SRC_DDS_H_ */
