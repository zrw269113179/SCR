# SCR
可控硅库函数

---
## 注意
文中使用`pin_write(unsigned char port,unsigned char level)`控制 GPIO 电平，具体实现未给出，用户可根据使用的芯片更改代码。

---
## 使用说明
1. 将`zero_detection()`函数放入过零信号端口的外部中断中。
2. 将`f_SCR_control_tick()`函数放入 100us 的定时器中断中（为了时间的准确，务必在中断中处理）
3. 在 SCR_Control.h 中设置
```
#define SCR_NUM     3          /// 可控硅数量
#define SCR_HOLD_TICK   5      /// 可控硅使能电平持续时间
#define SCR_LOWSTART_ENABLE    /// 可控硅缓启动使能,无需该功能则注释
```
4. 使用
`f_SCR_init(unsigned char id, unsigned char port, unsigned char openLevel)`对可控硅进行初始化,其中 id 编号为 0 ~ (SCR_NUM-1), port为可控硅输出端口，level 为可控硅输出电平。
5. 使用`f_SCR_enable(unsigned char id, unsigned char enable)`使能可控硅。
6. 使用`f_set_SCR_duty(unsigned char id, unsigned char duty)`设置可控硅输出占空比。默认占空比为 50% 。
7. 如果使能了缓启动，则可以使用`f_SCR_SetLowStartEnable(unsigned char id, unsigned char perDuty, unsigned char perCycle)`函数进行缓启动， perDuty 为每次增加的占空比， perCycle 为没过多少个半周期增加一次占空比。然后使用`f_SCR_SetLowStartDisable(unsigned char id)`使能缓启动。缓启动结束标志为增加的占空比达到了设定的占空比。