# DDS
**FPGA Cyclone II EP2C5T144C8 与 MSP430f6638实现DDS(信号发生器)**  
# Software
调制波频率、载波频率、AM调制度、FM最大频偏、PM最大相移、ASK、FSK、PSK16位二进制序列码由键盘输入  
Sin信号、AM信号、FM信号、PM信号、ASK信号、FSK信号、PSK信号由输出，经过硬件部分得到相应的信号  
## MCU  
- 低频(100Hz)时间中断:  
按键切换  
屏幕显示函数  
数值输入函数  
- 高频(1000Hz)时间中断:   
写入函数  
## FPGA  
- 顶层模块DDS:  
BUS_inst  
KEY_inst  
SquareWave_inst方波产生  
WaveData_inst1、2、3接受MCU写入的信号相关数据  
DDS_generate_inst产生信号
- DDS_generate  
MODE_inst信号选择，并完成DAC904的输出时序要求
SIN_inst  
AM_inst  
FM_inst  
PM_inst  
ASK_inst  
FSK_inst
PSK_inst  
# Hardware
# 注:  
*MCU数据传输至FPGA时，存在24位的频率数据，因此先传低16位，再传高8位  
*可以调整SIN波的ROM核来减小资源占用  
*默认选用了signaltap使用2K的采样深度观察输出信号  
*将最终的所有频率转至SIN_inst再输出波形，并使用ROM:2-PORT核，是因为ROM核如果调用多次，会超出FPGA板的Total memory bits  
*AM_inst中的乘法核与SIN_inst中的ROM核调用速率存在不够快的情况，因此MODE_inst中不能使用negedge clk_100M作为敏感事件，需要先得到上升沿稳定信号，再得到下降沿稳定信号  
