#include <msp430.h>
#include "src/lcd_serial.h"
#include "src/BUS_FPGA.h"
#include "src/setclock.h"
#include "src/key.h"
#include "src/DDS.h"

unsigned char key_value = 0;
char key_char = 0;

int screen = 0, screen_old = 0;

int waveFlag = 0;
int numSetflag = 0;
int sendFlag = 0;

unsigned long fc = 1000, fs = 1000, ma = 1, fd = 5000, pd = 0, sequenceCode = 0;
char sequenceCodestring[17] = "0000000000000000";
int k = 0;

void init();//初始化函数
void Display();//lcd显示函数
void Send();//发送数据函数
void NameRoll();//名字循环函数

int main(void)
{
    init();
    while (1)
    {

    }
}

//low freq interrupt is used to scan keyboard and (f=32768/327=100Hz)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
    static int i = 0;

    key_value = read_key();
    if(i == 0 || i == 30)
    {
        i = 0;
    }
    else
    {
        i++;
    }

    if(key_value != 0 && i == 0)
    {
        i = 1;
        key_char = KeyChar(key_value);
        int k = 0;
        switch(screen)
        {
        case 0://主界面
            switch(key_char)
            {
            case 'A'://正弦、调制
                screen = 1;
                Display();
                break;
            case 'B'://键控
                screen = 2;
                Display();
                break;
            default:
                break;
            }
            break;
        case 1://正弦、调制
            switch(key_char)
            {
            case 'A'://Sin
                screen = 3;
                waveFlag = 0;
                Display();
                sendFlag = 1;
                break;
            case 'B'://AM
                screen = 4;
                waveFlag = 1;
                Display();
                sendFlag = 1;
                break;
            case 'C'://FM
                screen = 5;
                waveFlag = 2;
                Display();
                sendFlag = 1;
                break;
            case 'D'://PM
                screen = 6;
                waveFlag = 3;
                Display();
                sendFlag = 1;
                break;
            case '#'://返回
                screen = 0;
                Display();
                break;
            default:
                break;
            }
            break;
        case 2://键控
            switch(key_char)
            {
            case 'A'://ASK
                screen = 7;
                waveFlag = 4;
                Display();
                sendFlag = 1;
                break;
            case 'B'://FSK
                screen = 8;
                waveFlag = 5;
                Display();
                sendFlag = 1;
                break;
            case 'C'://PSK
                screen = 9;
                waveFlag = 6;
                Display();
                sendFlag = 1;
                break;
            case '#'://返回
                screen = 0;
                Display();
                break;
            default:
                break;
            }
            break;
        case 3://Sin
            switch(key_char)
            {
            case 'A'://频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 0;
                fc = 0;
                Display();
                break;
            case '1':
                fc = fc + 10;
                Display();
                sendFlag = 1;
                break;
            case '2':
                fc = fc + 1000;
                Display();
                sendFlag = 1;
                break;
            case '3':
                fc = fc + 100000;
                Display();
                sendFlag = 1;
                break;
            case '4':
                fc = fc - 10;
                Display();
                sendFlag = 1;
                break;
            case '5':
                fc = fc - 1000;
                Display();
                sendFlag = 1;
                break;
            case '6':
                fc = fc - 100000;
                Display();
                sendFlag = 1;
                break;
            case '#'://返回
                screen = 1;
                Display();
                break;
            default:
                break;
            }
            break;
        case 4://AM
            switch(key_char)
            {
            case 'A'://载波频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 0;
                fc = 0;
                Display();
                break;
            case 'B'://调制波频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 1;
                fs = 0;
                Display();
                break;
            case 'C'://调制度频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 2;
                ma = 0;
                Display();
                break;
            case '#'://返回
                screen = 1;
                Display();
                break;
            default:
                break;
            }
            break;
        case 5://FM
            switch(key_char)
            {
            case 'A'://载波频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 0;
                fc = 0;
                Display();
                break;
            case 'B'://调制波频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 1;
                fs = 0;
                Display();
                break;
            case 'C'://最大频偏片选
                screen_old = screen;
                screen = 10;
                numSetflag = 3;
                fd = 0;
                Display();
                break;
            case '#'://返回
                screen = 1;
                Display();
                break;
            default:
                break;
            }
            break;
        case 6://PM
            switch(key_char)
            {
            case 'A'://载波频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 0;
                fc = 0;
                Display();
                break;
            case 'B'://调制波频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 1;
                fs = 0;
                Display();
                break;
            case 'C'://最大相移片选
                screen_old = screen;
                screen = 10;
                numSetflag = 4;
                pd = 0;
                Display();
                break;
            case '#'://返回
                screen = 1;
                Display();
                break;
            default:
                break;
            }
            break;
        case 7://ASK
            switch(key_char)
            {
            case 'A'://载波频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 0;
                fc = 0;
                Display();
                break;
            case 'B'://序列码片选
                screen_old = screen;
                screen = 10;
                numSetflag = 5;
                sequenceCode = 0;
                Display();
                break;
            case '#'://返回
                screen = 2;
                Display();
                break;
            default:
                break;
            }
            break;
        case 8://FSK
            switch(key_char)
            {
            case 'A'://载波频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 0;
                fc = 0;
                Display();
                break;
            case 'B'://序列码片选
                screen_old = screen;
                screen = 10;
                numSetflag = 5;
                sequenceCode = 0;
                Display();
                break;
            case 'C'://调制波频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 1;
                fs = 0;
                Display();
                break;
            case '#'://返回
                screen = 2;
                Display();
                break;
            default:
                break;
            }
            break;
        case 9://PSK
            switch(key_char)
            {
            case 'A'://载波频率片选
                screen_old = screen;
                screen = 10;
                numSetflag = 0;
                fc = 0;
                Display();
                break;
            case 'B'://序列码片选
                screen_old = screen;
                screen = 10;
                numSetflag = 5;
                sequenceCode = 0;
                Display();
                break;
            case '#'://返回
                screen = 2;
                Display();
                break;
            default:
                break;
            }
            break;
        case 10://Set
            switch(key_char)
            {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
            case 'A'://K
            case 'B'://M
                switch(numSetflag)
                {
                case 0://载波频率
                    DecNumSet(key_char, &fc);
                    DispDec57At(0, 18, fc, DecBitCheck(fc));
                    if(fc >= 10000000)
                    {
                        fc = 10000000;
                        screen = screen_old;
                        Display();
                        sendFlag = 1;
                    }
                    break;
                case 1://调制波频率
                    DecNumSet(key_char, &fs);
                    DispDec57At(0, 18, fs, DecBitCheck(fs));
                    if(fs >= 100000)
                    {
                        fs = 100000;
                        screen = screen_old;
                        Display();
                        sendFlag = 1;
                    }
                    break;
                case 2://调制度
                    DecNumSet(key_char, &ma);
                    DispDec57At(0, 18, ma, DecBitCheck(ma));
                    if(ma >= 10)
                    {
                        ma = 10;
                        screen = screen_old;
                        Display();
                        sendFlag = 1;
                    }
                    break;
                case 3://最大频偏
                    DecNumSet(key_char, &fd);
                    DispDec57At(0, 18, fd, DecBitCheck(fd));
                    if(fd >= 20000)
                    {
                        fd = 20000;
                        screen = screen_old;
                        Display();
                        sendFlag = 1;
                    }
                    break;
                case 4://最大相移
                    DecNumSet(key_char, &pd);
                    DispDec57At(0, 18, pd, DecBitCheck(pd));
                    if(pd >= 2047)
                    {
                        pd = 2047;
                        screen = screen_old;
                        Display();
                        sendFlag = 1;
                    }
                    break;
                case 5://序列码
                    BinNumSet(key_char, &sequenceCode);
                    for(k = 0; k < 16; k++)
                    {
                        sequenceCodestring[15 - k] = (sequenceCode >> k) % 2 + 48;
                    }
                    DispString57At(0, 0, sequenceCodestring);
                    if(sequenceCode >= 65535)
                    {
                        sequenceCode = 65535;
                        screen = screen_old;
                        Display();
                        sendFlag = 1;
                    }
                    break;
                default:
                    break;
                }
                break;
            case '#'://返回
                if(fc <= 1000)
                {
                    fc = 1000;
                }
                if(fs <= 1000)
                {
                    fs = 1000;
                }
                if(ma <= 1)
                {
                    ma = 1;
                }
                if(fd <= 5000)
                {
                    fd = 5000;
                }
                screen = screen_old;
                Display();
                sendFlag = 1;
                break;
            default:
                break;
            }
        default:
            break;
        }
        if(key_char == '*')
        {
            screen = 0;
            Display();
        }
    }
    static int j = 0;
    if(screen == 0 && j == 0)
    {
        NameRoll();
    }
    j = (j + 1) % 10;
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
    Send();
}

void Display()//lcd显示函数
{
    lcd_clear();
    //    DispDec57At(6, 116, key_value, 2);
    //DDS信号发生器
    // A / B
    // 正弦、调制/键控
    //By 付宇豪、陆寿文、王乐明
    // * / #
    // 主页 / 返回
    if(screen == 0)
    {
        DispStringAt(0, 0, "DDS");
        disp_graph_16x16(0, 24, Xin);
        disp_graph_16x16(0, 40, Hao2);
        disp_graph_16x16(0, 56, Fa);
        disp_graph_16x16(0, 72, Sheng);
        disp_graph_16x16(0, 88, Qi);

        disp_graph_16x16(2, 0, Zheng);
        disp_graph_16x16(2, 16, Xian);
        DispStringAt(2, 32, "/");
        disp_graph_16x16(2, 40, Tiao);
        disp_graph_16x16(2, 56, Zhi);
        DispStringAt(2, 120, "A");

        disp_graph_16x16(4, 0, Jian);
        disp_graph_16x16(4, 16, Kong);
        DispStringAt(4, 120, "B");
    }
    //正弦、调制
    // A / B / C / D
    // Sin / AM / FM / PM
    if(screen == 1)
    {
        DispString57At(0, 0, "Sin");
        DispString57At(0, 122, "A");
        DispString57At(2, 0, "AM");
        DispString57At(2, 122, "B");
        DispString57At(4, 0, "FM");
        DispString57At(4, 122, "C");
        DispString57At(6, 0, "PM");
        DispString57At(6, 122, "D");
    }
    //键控
    // A / B / C
    // ASK / FSK / PSK
    else if(screen == 2)
    {
        DispString57At(0, 0, "ASK");
        DispString57At(0, 122, "A");
        DispString57At(2, 0, "FSK");
        DispString57At(2, 122, "B");
        DispString57At(4, 0, "PSK");
        DispString57At(4, 122, "C");
    }
    //Sin
    // A
    // 频率
    else if(screen == 3)
    {
        DispString57At(0, 0, "Sin");
        DispString57At(1, 0, "fc=");
        DispDec57At(1, 18, fc, DecBitCheck(fc));
        DispString57At(1, 122, "A");
    }
    //AM
    // A / B / C
    // 载波频率 / 调制波频率 / 调制度
    else if(screen == 4)
    {
        DispString57At(0, 0, "AM");
        DispString57At(1, 0, "fc=");
        DispDec57At(1, 18, fc, DecBitCheck(fc));
        DispString57At(1, 122, "A");
        DispString57At(2, 0, "fs=");
        DispDec57At(2, 18, fs, DecBitCheck(fs));
        DispString57At(2, 122, "B");
        DispString57At(3, 0, "ma=");
        DispDec57At(3, 18, ma, DecBitCheck(ma));
        DispString57At(3, 122, "C");
    }
    //FM
    // A / B / C
    // 载波频率 / 调制波频率 / 最大频偏
    else if(screen == 5)
    {
        DispString57At(0, 0, "FM");
        DispString57At(1, 0, "fc=");
        DispDec57At(1, 18, fc, DecBitCheck(fc));
        DispString57At(1, 122, "A");
        DispString57At(2, 0, "fs=");
        DispDec57At(2, 18, fs, DecBitCheck(fs));
        DispString57At(2, 122, "B");
        DispString57At(3, 0, "fd=");
        DispDec57At(3, 18, fd, DecBitCheck(fd));
        DispString57At(3, 122, "C");
    }
    //PM
    // A / B / C
    // 载波频率 / 调制波频率 / 最大相移
    else if(screen == 6)
    {
        DispString57At(0, 0, "PM");
        DispString57At(1, 0, "fc=");
        DispDec57At(1, 18, fc, DecBitCheck(fc));
        DispString57At(1, 122, "A");
        DispString57At(2, 0, "fs=");
        DispDec57At(2, 18, fs, DecBitCheck(fs));
        DispString57At(2, 122, "B");
        DispString57At(3, 0, "pd=");
        DispDec57At(3, 18, pd, DecBitCheck(pd));
        DispString57At(3, 122, "C");
    }
    //ASK
    // A / B
    // 载波频率 / 序列码
    else if(screen == 7)
    {
        DispString57At(0, 0, "ASK");
        DispString57At(1, 0, "fc=");
        DispDec57At(1, 18, fc, DecBitCheck(fc));
        DispString57At(1, 122, "A");
        for(k = 0; k < 16; k++)
        {
            sequenceCodestring[15 - k] = (sequenceCode >> k) % 2 + 48;
        }
        DispString57At(2, 0, sequenceCodestring);
    }
    //FSK
    // A / B / C
    // 载波频率 / 序列码 / 调制波频率
    else if(screen == 8)
    {
        DispString57At(0, 0, "FSK");
        DispString57At(1, 0, "fc=");
        DispDec57At(1, 18, fc, DecBitCheck(fc));
        DispString57At(1, 122, "A");
        for(k = 0; k < 16; k++)
        {
            sequenceCodestring[15 - k] = (sequenceCode >> k) % 2 + 48;
        }
        DispString57At(2, 0, sequenceCodestring);
        DispString57At(3, 0, "fs=");
        DispDec57At(3, 18, fs, DecBitCheck(fs));
        DispString57At(3, 122, "C");
    }
    //PSK
    // A / B
    // 载波频率 / 序列码
    else if(screen == 9)
    {
        DispString57At(0, 0, "PSK");
        DispString57At(1, 0, "fc=");
        DispDec57At(1, 18, fc, DecBitCheck(fc));
        DispString57At(1, 122, "A");
        for(k = 0; k < 16; k++)
        {
            sequenceCodestring[15 - k] = (sequenceCode >> k) % 2 + 48;
        }
        DispString57At(2, 0, sequenceCodestring);
    }

    //参数设置
    // 0~9
    // 数字输入
    else if(screen == 10)
    {
        switch(numSetflag)
        {
        case 0:
            DispString57At(0, 0, "fc=");
            break;
        case 1:
            DispString57At(0, 0, "fs=");
            break;
        case 2:
            DispString57At(0, 0, "ma=");
            break;
        case 3:
            DispString57At(0, 0, "fd=");
            break;
        case 4:
            DispString57At(0, 0, "pd=");
            break;
        case 5:
            for(k = 0; k < 16; k++)
            {
                sequenceCodestring[15 - k] = (sequenceCode >> k) % 2 + 48;
            }
            DispString57At(0, 0, sequenceCodestring);
            break;
        default:
            break;
        }
    }
}

void Send()//发送数据
{
    static int i = 0;
    if(sendFlag == 1)
    {
        switch(i)
        {
        case 0:
            IOWR(CS1, 0, waveFlag);
            break;
        case 1:
            IOWR(CS2, 0, 0); //fc
            break;
        case 2:
            IOWR(CS3, 0, fc);
            break;
        case 3:
            IOWR(CS3, 0, fc >> 16);
            break;
        case 4:
            IOWR(CS2, 0, 1); //fs
            break;
        case 5:
            IOWR(CS3, 0, fs);
            break;
        case 6:
            IOWR(CS3, 0, fs >> 16);
            break;
        case 7:
            IOWR(CS2, 0, 2); //ma
            break;
        case 8:
            IOWR(CS3, 0, ma);
            break;
        case 9:
            IOWR(CS2, 0, 3); //fd
            break;
        case 10:
            IOWR(CS3, 0, fd);
            break;
        case 11:
            IOWR(CS2, 0, 4);//pd
            break;
        case 12:
            IOWR(CS3, 0, pd);
            break;
        case 13:
            IOWR(CS2, 0, 5);//sequenceCode
            break;
        case 14:
            IOWR(CS3, 0, sequenceCode);
            sendFlag = 0;
            break;
        default:
            sendFlag = 0;
            break;
        }
        i++;
        if(i == 15)
        {
            i = 0;
        }
    }
}

void NameRoll()//名字循环函数
{
    static int bit[9] = {24, 40, 56, 80, 96, 112, 136, 152, 168};
    int i = 0;
    //    DispStringAt(6, 0, "                ");
    if(bit[0] >= 1 && bit[0] <= 127)
    {
        disp_graph_16x16(6, bit[0], Fu);
    }
    if(bit[1] >= 1 && bit[1] <= 127)
    {
        disp_graph_16x16(6, bit[1], Yu);
    }
    if(bit[2] >= 1 && bit[2] <= 127)
    {
        disp_graph_16x16(6, bit[2], Hao);
    }
    if(bit[3] >= 1 && bit[3] <= 127)
    {
        disp_graph_16x16(6, bit[3], Lu);
    }
    if(bit[4] >= 1 && bit[4] <= 127)
    {
        disp_graph_16x16(6, bit[4], Shou);
    }
    if(bit[5] >= 1 && bit[5] <= 127)
    {
        disp_graph_16x16(6, bit[5], Wen);
    }
    if(bit[6] >= 1 && bit[6] <= 127)
    {
        disp_graph_16x16(6, bit[6], Wang);
    }
    if(bit[7] >= 1 && bit[7] <= 127)
    {
        disp_graph_16x16(6, bit[7], Le);
    }
    if(bit[8] >= 1 && bit[8] <= 127)
    {
        disp_graph_16x16(6, bit[8], Ming);
    }
    for(i = 0; i < 9; i++)
    {
        bit[i]--;
        if(bit[i] == 0)
        {
            bit[i] = 168;
        }
    }
    DispStringAt(6, 0, "By");
}

void init()//初始化函数
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    SetClock_MCLK12MHZ_SMCLK12MHZ_ACLK32_768K();

    BUS_Init();
    Lcd_Init();

    Display();

    TA0CTL = TASSEL_1 + MC_1 + TACLR;//100Hz
    TA0CCR0 = 327;
    TA0CCTL0 = CCIE;

    TA1CTL = TASSEL_1 + MC_1 + TACLR;//1000Hz
    TA1CCR0 = 33;
    TA1CCTL0 = CCIE;

    __bis_SR_register(GIE);
}
