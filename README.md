# STC32_Project
一、遥控小车

1、遥控手柄

硬件：

主控芯片：STM32F103C8T6
输入设备：摇杆、8个独立按键、MPU6050
输出设备：OLED、NRF24L01
软件：

软件：

采用Keil C编程软件编写，使用C语言编程。

控制模式：摇杆控制、按键控制、陀螺仪控制、WS2812模式、MP3模式等。
显示信息：OLED显示当前模式、MPU6050原始值、摇杆值、手柄电量等。
通信协议：通过NRF24L01向小车发送控制信号。

功能实现：

使用左遥感上下预览各个控制模式，按键确定并通过NRF24L01发送给小车
摇杆控制：通过摇杆控制小车的前进、后退、转向等运动
按键控制：通过8个独立按键控制小车的运动、停止等运动
陀螺仪控制：通过MPU6050获取倾斜角度，控制小车的运动
WS2812模式：控制WS2812灯光的颜色、亮度、动画效果
MP3模式：通过独立按键控制MP3模块播放音乐、语音提示等

<img src="https://github.com/MOMINGXX/Picture/blob/main/IMG_20230310_213929.jpg" width="800" height="650" alt="手柄"/><br/>
2、小车

<img src="https://github.com/MOMINGXX/Picture/blob/main/IMG_20230310_213952.jpg" width="800" height="650" alt="手柄"/><br/>
