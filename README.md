# STC32_Project
一、遥控小车

1、遥控手柄

硬件：

主控芯片：STM32F103C8T6

输入设备：摇杆、8个独立按键、MPU6050

输出设备：OLED、NRF24L01


软件：


    采用Keil 编程软件编写，使用C语言编程。

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


硬件：


    主控芯片：STC32G12K128
    
    驱动模块：L298N驱动4个直流电机
    
    通信模块：NRF24L01无线模块和蓝牙模块
    
    控制模块：手柄控制和手机APP控制
    
    传感器模块：超声波测距模块、舵机、WS2812 LED灯和MP3模块


该项目的软件部分包括以下模块：


    无线通信模块驱动：包括NRF24L01和蓝牙模块的驱动和通信协议实现。
    
    手柄控制模块：将手柄输入转换为小车运动指令，并将指令通过无线通信模块发送给小车。
    
    手机APP控制模块：通过手机APP将指令发送给小车控制模块，实现远程控制小车运动。
    
    传感器数据采集模块：包括超声波测距模块、舵机、WS2812 LED灯和MP3模块的驱动和数据采集。
    
    运动控制模块：通过驱动模块控制小车四个直流电机的转速和方向，实现小车运动。
    
    LED灯效果控制模块：通过控制WS2812 LED灯的颜色和亮度，实现LED灯效果控制。
    
    声音播放模块：通过MP3模块实现声音的播放。
    

该项目的软件部分包括以下模块：


    无线通信模块驱动：包括NRF24L01和蓝牙模块的驱动和通信协议实现。

    手柄控制模块：将手柄输入转换为小车运动指令，并将指令通过无线通信模块发送给小车。

    手机APP控制模块：通过手机APP将指令发送给小车控制模块，实现远程控制小车运动。

    波测距模块：模块测得距离并配合舵机，实现避障功能。

    WS2812模块：控制WS2812灯光的颜色、亮度、动画效果

    运动控制模块：通过驱动模块控制小车四个直流电机的转速和方向，实现小车运动。

    LED灯效果控制模块：通过控制WS2812 LED灯的颜色和亮度，实现LED灯效果控制。

    声音播放模块：通过MP3模块实现声音的播放。

<img src="https://github.com/MOMINGXX/Picture/blob/main/IMG_20230310_213952.jpg" width="800" height="650" alt="手柄"/><br/>
