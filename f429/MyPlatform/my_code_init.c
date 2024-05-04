#include "my_code_init.h"
#include "cmsis_os.h"
#include "lvgl.h"
#include "lvgl_app.h"

#include "hardware.h"

#pragma diag_suppress 188

uint16_t times = 0;
uint8_t x = 0;
extern uint8_t recv_data;
extern uint8_t recv_buff[100];
extern uint8_t recv_one_frame;
extern uint16_t recv_len;

const uint8_t TEXT_Buffer[] = {"Apollo STM32F4 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)


void rtp_test(void)
{
	u8 key;
	u8 i=0;	  
  uint16_t x=0, y=0;

  POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"Apollo STM32f4/F7"); 
	LCD_ShowString(30,70,200,16,16,"TOUCH TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2016/1/16");	 

  while(1)
    {
        switch(x)
      {
        case 0:LCD_Clear(WHITE);      printf("WHITE\n");      break;
        case 1:LCD_Clear(BLACK);      printf("BLACK\n");      break;
        case 2:LCD_Clear(BLUE);       printf("BLUE\n");      break;
        case 3:LCD_Clear(RED);        printf("RED\n");      break;
        case 4:LCD_Clear(MAGENTA);    printf("MAGENTA\n");      break;
        case 5:LCD_Clear(GREEN);      printf("GREEN\n");      break;
        case 6:LCD_Clear(CYAN);       printf("CYAN\n");      break; 
        case 7:LCD_Clear(YELLOW);     printf("YELLOW\n");      break;
        case 8:LCD_Clear(BRRED);      printf("BRRED\n");      break;
        case 9:LCD_Clear(GRAY);       printf("GRAY\n");      break;
        case 10:LCD_Clear(LGRAY);     printf("LGRAY\n");      break;
        case 11:LCD_Clear(BROWN);     printf("BROWN\n");      break;
      }
      POINT_COLOR=RED;	  
      LCD_ShowString(10,40,240,32,32,"Apollo STM32F4/F7"); 	
      LCD_ShowString(10,80,240,24,24,"TFTLCD TEST");
      LCD_ShowString(10,110,240,16,16,"ATOM@ALIENTEK");
      // LCD_ShowString(10,130,240,16,16,lcd_id);		//显示LCD ID	      					 
      LCD_ShowString(10,150,240,12,12,"2016/1/6");	      					 
      x++;
      delay_ms(1000);	
	}
	// while(1)
	// {
	 	// key=Key_Scan(0);
		// touch_read(&x, &y);	 
		// if(touch_status())			//触摸屏被按下
		// {	
    //   printf("x = %d, y = %d\n", x, y);
		//  	if(x<LCD_WIDTH && y<LCD_HEIGHT)
		// 	{	
		// 		if(x>(LCD_WIDTH-24) && y<16)Load_Drow_Dialog();//清除
		// 		else TP_Draw_Big_Point(x,y,RED);		//画图	  			   
		// 	}
		// }else delay_ms(10);	//没有按键按下的时候 	    
		// if(key==KEY0_PRES)	//KEY0按下,则执行校准程序
		// {
		// 	LCD_Clear(WHITE);	//清屏
		//     TP_Adjust();  		//屏幕校准 
		// 	TP_Save_Adjdata();	 
		// 	Load_Drow_Dialog();
		// }
		// i++;
		// if(i%20==0)LED1_TRG;
	// }
}

void my_code_init(void)
{
  lv_init();
  lv_port_disp_init();
  lv_port_indev_init();
  lvgl_app();

  // AT24CXX_Init();
  // while (AT24CXX_Check())
  // { // 检测不到24c02
  //   printf("24C02 Check Failed!\n");
  //   delay_ms(500);
  //   printf("Please Check!      \n");
  //   delay_ms(500);
  // }


  HAL_UART_Receive_IT(&huart1, &recv_data, 1);

  POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"Apollo STM32f4/F7"); 
	LCD_ShowString(30,70,200,16,16,"TOUCH TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2016/1/16");	 
  LCD_Clear(RED);

  delay_ms(1000);
}

void my_gui_entry(void)
{
}

uint8_t key = 0;
uint8_t datatemp[SIZE];
void my_commc_loop(void)
{
  if (recv_one_frame == 1)
  {
    printf("%s\r\n", recv_buff);
    recv_buff[recv_len - 2] = '\0';
    // lcd_draw_str(50, 50, (const char *)recv_buff , &Font16, BLACK, GREEN);
    recv_len = 0;
    recv_one_frame = 0;
  }

  key = Key_Scan(0);
  if (key == KEY1_PRES) // KEY1按下,写入24C02
  {
    printf("Start Write 24C02....\n");
    // taskENTER_CRITICAL();
    osKernelLock();
    AT24CXX_Write(0, (uint8_t *)TEXT_Buffer, SIZE);
    // taskEXIT_CRITICAL();
    osKernelUnlock();
    printf("24C02 Write Finished!\n"); // 提示传送完成
  }
  if (key == KEY0_PRES) // KEY0按下,读取字符串并显示
  {
    printf("Start Read 24C02.... \n");
    taskENTER_CRITICAL();
    AT24CXX_Read(0, datatemp, SIZE);
    taskEXIT_CRITICAL();
    printf("The Data Readed Is:  \n"); // 提示传送完成
    printf("%s\n", datatemp);                // 显示读到的字符串
  }

  if(touch_status()){
    uint16_t x=0, y=0;
    touch_read(&x, &y);
    printf("x = %d, y = %d\n", x, y);
  }

  static int sec = 0;
  sec++;
  if (sec >= 1000)
  {
    sec = 0;
    LED1_TRG;
  }
}

void delay_us(uint16_t us)
{
  uint16_t differ = 0xffff - us - 5;
  __HAL_TIM_SET_COUNTER(&htim6, differ);
  HAL_TIM_Base_Start(&htim6);
  while (__HAL_TIM_GET_COUNTER(&htim6) < 0xffff - 6)
  {
  }
  HAL_TIM_Base_Stop(&htim6);
}

void delay_ms(uint16_t ms)
{
  for (int i = 0; i < 2 * ms; i++)
    delay_us(500);
}
