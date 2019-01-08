#ifndef SCR_CONTROL_H
#define SCR_CONTROL_H

#define SCR_NUM     3          /// 可控硅数量
#define SCR_HOLD_TICK   5      /// 可控硅使能电平持续时间
#define SCR_LOWSTART_ENABLE    /// 可控硅缓启动使能,无需该功能则注释


void f_SCR_init(unsigned char id, unsigned char port, unsigned char openLevel);
void f_SCR_enable(unsigned char id, unsigned char enable);
void f_set_SCR_duty(unsigned char id, unsigned char duty);

///循环调用
void zero_detection(void);
void f_SCR_control_tick(void);

/// 缓启动
void f_SCR_SetLowStartEnable(unsigned char id, unsigned char perDuty, unsigned char perCycle);
void f_SCR_SetLowStartDisable(unsigned char id);
#endif
