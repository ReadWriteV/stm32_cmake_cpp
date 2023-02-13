#include "oled.hpp"
#include "oled_font.hpp"
#include "common.hpp"

// OLED的显存
// 存放格式如下.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127

OLED::OLED()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE); // 使能端口时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);            // 初始化

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);            // 初始化

    GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15);

    //  OLED_RST_Set(); // 复位使用系统复位，所以此处不需要再复位
    //  delay_ms(100);
    //  OLED_RST_Clr();
    //  delay_ms(200);
    //  OLED_RST_Set();

    write_command(0xAE); // 关闭OLED显示

    write_command(0x00); // set low column address X轴低位，起始X轴为0
    write_command(0x10); // set high column address X轴高位
    write_command(0x40); // set start line address, set Mapping RAM Display Start Line (0x40~0x7F) Y轴，可设区间[0x40,0x7F]，设置为0了

    write_command(0x81); // set contrast control register 命令头，调节亮度,对比度,变化很小，但是仔细可以观察出来
    write_command(0xCF); // set SEG Output Current Brightness 可设置区间[0x00,0xFF]

    write_command(0xA1); // set SEG/Column Mapping 设置X轴扫描方向，0xA0左右反置 ，0xA1正常（左边为0列）
    write_command(0xC8); // set COM/Row Scan Direction 设置Y轴扫描方向，0xc0上下反置 ，0xc8正常（上边为0行）
    write_command(0xA6); // set normal display 位值表示的意义，0xa6表示正常，1为点亮，0为关闭，0xa7显示效果相反

    write_command(0xA8); // set multiplex ratio(1 to 64) 命令头，设置多路复用率(1 to 64)
    write_command(0x3f); // 1/64 duty

    write_command(0xD3); // set display offset Shift Mapping RAM Counter (0x00~0x3F) 命令头，设置显示偏移移位映射RAM计数器(0x00~0x3F)
    write_command(0x00); // not offset 不偏移

    write_command(0xd5); // set display clock divide ratio/oscillator frequency 命令头，设置显示时钟分频比/振荡器频率
    write_command(0x80); // set divide ratio, set Clock as 100 Frames/Sec 设置分割比率，设置时钟为100帧/秒

    write_command(0xD9); // set pre-charge period 命令头
    write_command(0xF1); // set Pre-Charge as 15 Clocks & Discharge as 1 Clock

    write_command(0xDA); // set com pins hardware configuration 命令头
    write_command(0x12);

    write_command(0xDB); // set vcomh 命令头
    write_command(0x40); // set VCOM Deselect Level

    write_command(0x20); // set Page Addressing Mode (0x00/0x01/0x02) 命令头，设置寻址模式
    write_command(0x02); // 页面寻址模式(重置) (0x00/0x01/0x02)

    write_command(0x8D); // set Charge Pump enable/disable 命令头
    write_command(0x14); // set(0x10) disable

    write_command(0xA4); // disable Entire Display On (0xa4/0xa5) 恢复到RAM内容显示(重置)

    write_command(0xAF); // 开启OLED显示

    clear();
    set_position(0, 0);
}

void OLED::set_position(uint8_t column, uint8_t page)
{
    write_command(0xb0 + page);          // page address
    write_command(column & 0x0f);        // lower column start address
    write_command(0x10 + (column >> 4)); // higher column start address
}

void OLED::display(bool on)
{
    if (on)
    {
        write_command(0X8D); // SET DCDC命令
        write_command(0X14); // DCDC ON
        write_command(0XAF); // DISPLAY ON
    }
    else
    {
        write_command(0X8D); // SET DCDC命令
        write_command(0X10); // DCDC OFF
        write_command(0XAE); // DISPLAY OFF
    }
}

void OLED::clear()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        write_command(0xb0 + i); // 设置页地址 0 ~ 7
        write_command(0x00);     // 设置显示位置—列低地址
        write_command(0x10);     // 设置显示位置—列高地址
        for (uint8_t n = 0; n < 128; n++)
            write_data(0);
    }
}

void OLED::show(uint8_t row, uint8_t column, char ch)
{
    if (column > max_column - unit_width + 1) // 溢出换行
    {
        column %= max_column - unit_width + 1;
        row = row + 2; // 每个显示单元高为16
    }
    uint8_t c = ch - ' '; // 得到偏移后的值
    set_position(column - 1, row - 1);
    for (uint8_t i = 0; i < 8; i++)
        write_data(F8X16[c * 16 + i]);
    set_position(column - 1, row);
    for (uint8_t i = 0; i < 8; i++)
        write_data(F8X16[c * 16 + i + 8]);
}

void OLED::show(uint8_t row, uint8_t column, uint32_t num, uint8_t len)
{
    bool begin_flag = false;
    for (uint8_t t = 0; t < len; t++)
    {
        uint8_t temp = (num / pow(10, len - t - 1)) % 10;
        if (begin_flag == false && t < (len - 1))
        {
            if (temp == 0)
            {
                show(row, column + unit_width * t, ' ');
                continue;
            }
            else
                begin_flag = true;
        }
        show(row, column + unit_width * t, temp + '0');
    }
}

void OLED::show(uint8_t row, uint8_t column, const char *str)
{
    uint8_t j = 0;
    while (str[j] != '\0')
    {
        show(row, column, str[j]);
        column += 8;
        if (column > max_column - unit_width + 1)
        {
            column = 1;
            row += 2;
        }
        j++;
    }
}

uint32_t OLED::pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
        result *= m;
    return result;
}

void OLED::write_byte(uint8_t byte)
{
    CS_Clr();
    for (uint8_t i = 0; i < 8; i++)
    {
        SCLK_Clr();
        if (byte & 0x80)
        {
            SDIN_Set();
        }
        else
        {
            SDIN_Clr();
        }
        SCLK_Set();
        byte <<= 1;
    }
    CS_Set();
}

void OLED::write_command(uint8_t command)
{
    DC_Clr();
    write_byte(command);
    DC_Set();
}

void OLED::write_data(uint8_t data)
{
    DC_Set();
    write_byte(data);
}
