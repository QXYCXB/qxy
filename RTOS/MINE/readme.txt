串口dma,freertos,双can,pid(HAL库)





2022 ROBOCON比赛 R2程序简介：
	pid.c:PID算法
	JG.c:激光测距数据解析(DMA接收)
	launch.c:M3508发射，8电机控制协议
	motor.c:M3508底盘，4电机控制协议
	oled.c:oled显示相关函数
	SBUS.c:遥控器接收协议(DMA接收)
	action.c:码盘数据解析协议(DMA接收)
	control.c:三轮运动学解析(逆解) 遥控器控制函数


当前程序共有四个任务
		POSHandle   电机上电,整车转到指定角度
		
		ClampHandle 发射击塔并移到左边球架
		
		KEYHandle   扫描遥控器按键
		
		OLEDHandle 部分数据显示以及prntf;
	
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	