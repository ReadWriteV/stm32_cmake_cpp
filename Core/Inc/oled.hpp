#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"

// 1 2 3 4 5 6 7 8 9 ...... 127 128
// B B B B B B B B B B B B B B B B  1
// B B B B B B B B B B B B B B B B  2
// B B B B B B B B B B B B B B B B  3
// B B B B B B B B B B B B B B B B  4
// B B B B B B B B B B B B B B B B  5
// B B B B B B B B B B B B B B B B  6
// B B B B B B B B B B B B B B B B  7
// B B B B B B B B B B B B B B B B  8

/// @brief 每个显示单元高为16，宽为8
class OLED
{
public:
    /// @brief 初始化SSD1306
    OLED();

    /// @brief 设置显示地址，要求为页面寻址模式
    /// @param column 列地址，0 ~ 127
    /// @param page 页地址，0 ~ 7
    void set_position(uint8_t column, uint8_t page);

    /// @brief 设置OLED是否显示
    /// @param on 是否显示
    void display(bool on);

    /// @brief 清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!
    void clear();

    /// @brief 在指定位置显示一个字符
    /// @param row 指定显示的行，1 ~ 7，（第8行显示不全字符）
    /// @param column 指定显示的列，1 ~ 121，（第121列后换行显示字符）
    /// @param ch 显示的字符
    void show(uint8_t row, uint8_t column, char ch);

    /// @brief 在指定位置显示一个数字
    /// @param row 指定显示的行，1 ~ 7，（第8行显示不全字符）
    /// @param column 指定显示的列，1 ~ 121，（第121列后换行显示字符）
    /// @param num 要显示的数字
    /// @param len 要显示的位数
    void show(uint8_t row, uint8_t column, uint32_t num, uint8_t len);

    /// @brief 在指定位置显示一个字符串
    /// @param row 指定显示的行，1 ~ 7，（第8行显示不全字符）
    /// @param column 指定显示的列，1 ~ 121，（第121列后换行显示字符）
    /// @param str 要显示的字符串
    void show(uint8_t row, uint8_t column, const char *str);

    /// @brief 显示汉字
    /// @param x 起点坐标
    /// @param y 起点坐标
    /// @param no 汉字编号
    [[deprecated]] void show_chinese(uint8_t x, uint8_t y, uint8_t no);

    /// @brief 显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7
    /// @param x0
    /// @param y0
    /// @param x1
    /// @param y1
    /// @param BMP
    [[deprecated]] void show(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t BMP[]);

private:
    //-----------------OLED端口定义----------------
    inline void CS_Clr() { GPIO_ResetBits(GPIOB, GPIO_Pin_12); } // CS
    inline void CS_Set() { GPIO_SetBits(GPIOB, GPIO_Pin_12); }

    inline void RST_Clr() { GPIO_ResetBits(GPIOA, GPIO_Pin_4); } // RES
    inline void RST_Set() { GPIO_SetBits(GPIOA, GPIO_Pin_4); }

    inline void DC_Clr() { GPIO_ResetBits(GPIOC, GPIO_Pin_6); } // DC
    inline void DC_Set() { GPIO_SetBits(GPIOC, GPIO_Pin_6); }

    inline void SCLK_Clr() { GPIO_ResetBits(GPIOB, GPIO_Pin_13); } // CLK
    inline void SCLK_Set() { GPIO_SetBits(GPIOB, GPIO_Pin_13); }

    inline void SDIN_Clr() { GPIO_ResetBits(GPIOB, GPIO_Pin_15); } // DIN
    inline void SDIN_Set() { GPIO_SetBits(GPIOB, GPIO_Pin_15); }

    static constexpr inline uint8_t unit_width = 8;
    static constexpr inline uint8_t unit_height = 16;
    static constexpr inline uint8_t max_column = 128;
    static constexpr inline uint8_t max_row = 8;

    /// @brief 计算 m 的 n 次幂，即 m^n
    /// @param m 底数
    /// @param n 指数
    /// @return m 的 n 次幂，即 m^n
    static u32 pow(uint8_t m, uint8_t n);

    /// @brief 向SSD1106写入一个字节
    /// @param byte 要写入的字节
    void write_byte(uint8_t byte);

    /// @brief 向SSD1106写入一个命令
    /// @param command 写入的命令
    void write_command(uint8_t command);

    /// @brief 向SSD1106写入一个数据
    /// @param data 写入的数据
    void write_data(uint8_t data);

    // private:
    //     GPIO_TypeDef *SDI_port;
    //     uint16_t SDI_pin;
    //     GPIO_TypeDef *SCL_port;
    //     uint16_t SCL_pin;
    //     GPIO_TypeDef *SDI_port;
    //     uint16_t SDI_pin;
    //     GPIO_TypeDef *CS_port;
    //     uint16_t CS_pin;
    //     GPIO_TypeDef *RESET_port;
    //     uint16_t RESET_pin;
    //     GPIO_TypeDef *A0_port;
    //     uint16_t A0_pin;
};

#endif
