# SCR

可控硅库函数

---

## 可控硅介绍

可控硅也称晶闸管，具有体积小、效率高、寿命长等优点，一般用在大功率器件上，实现小功率控制大功率的作用。
具体工作原理不多做阐述，这里要实现控制双向可控硅只需知道以下几点。

* 可控硅在市电过零后即关断。
* 对控制极施加电压，使其电流达到触发电流即可导通。

因此只需要在接收到过零信号后开始计时，达到自己期望的占空比后给一段时间的电压即可导通。
注意：

* 可控硅电平不能一直施加，防止过零信号延迟带来的可控硅一直导通，即已经过零，由于过零信号有延迟，如果在接收到过零信号才关断输出电压的话，可能造成延时时间内施加的电压已经使可控硅导通。

---

## 使用注意

文中使用`pin_write(unsigned char port,unsigned char level)`控制 GPIO 电平，具体实现未给出，用户可根据使用的芯片更改代码。

---

## 使用说明

* 将`zero_detection()`函数放入过零信号端口的外部中断中。
* 将`f_SCR_control_tick()`函数放入 100us 的定时器中断中（为了时间的准确，务必在中断中处理）
* 在 SCR_Control.h 中设置

```c
#define SCR_NUM     1          /// 可控硅数量
#define SCR_HOLD_TICK   5      /// 可控硅使能电平持续时间
#define SCR_LOWSTART_ENABLE    /// 可控硅缓启动使能,无需该功能则注释
#define SCR_TRANSITION_ENABLE  /// 占空比改变时根据缓启动的速度过度，需先开启缓启动
```

* 使用`f_SCR_init(unsigned char id, unsigned char port, unsigned char openLevel)`对可控硅进行初始化,其中 id 编号为 0 ~ (SCR_NUM-1), port为可控硅输出端口，level 为可控硅输出电平。
* 使用`f_SCR_enable(unsigned char id, unsigned char enable)`使能可控硅。
* 使用`f_set_SCR_duty(unsigned char id, unsigned char duty)`设置可控硅输出占空比。默认占空比为 50% 。
* 如果使能了缓启动，则可以使用`void f_SCR_SetLowStartEnable(unsigned char id, unsigned char startDuty,unsigned char perDuty, unsigned char perCycle)`函数进行缓启动，startDuty 为起始占空比， perDuty 为每次增加的占空比， perCycle 为没过多少个半周期增加一次占空比。然后使用`f_SCR_SetLowStartDisable(unsigned char id)`使能缓启动。缓启动结束标志为增加的占空比达到了设定的占空比。

---

## 配置选项

* `SCR_NUM` 可控硅个数，该个数必须准确，否则可能因为初始化数值的问题导致程序陷入死循环。
* `SCR_HOLD_TICK` 可控硅导通时间，单位100us，根据不同可控硅，该值不同，需确保可控硅可以导通，但又不会进入下一个过零周期。
* `SCR_LOWSTART_ENABLE` 该语句控制可控硅缓启动，无需该功能则注释，缓启动参数可配置。
* `SCR_TRANSITION_ENABLE` 该语句控制占空比变换后是否需要过渡，该参数需要和缓启动同时使用，过度参数与缓启动参数相同。
* 缓启动和过度主要目的防止占空比跳变造成电流过大损坏元器件。