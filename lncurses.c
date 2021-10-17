//
// CM4Industrial TEST code V1.1
// Created by andy sheng in Nov 2020
//
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROW      3                        /*框架有ROW行*/    
#define COLUMN   6						  /*框架有COLUMN行*/  
#define OFFSET   2                        /*向右偏移OFFSET后，更加美观*/  
int max_y,max_x;                     	/*屏幕的最大尺寸边框*/
typedef struct funciton_link_list       //定义功能结构体
{
	char index;                           /*功能的序号*/
	char name[50];                       /*功能的名字*/
	char shell_name[50];                 /*要调用脚本文件*/
	int result;	                         /*功能测试的结果 0:unknow  1:pass  -1:fail*/
	int x_pos;							 /*功能名显示的X位置*/
	int y_pos;                           /*功能名显示的Y位置*/
	
}FUNCITON_LINK_LIST;


FUNCITON_LINK_LIST fun[]={	
	{'1',"1-RTC","sudo bash /home/pi/work/rtc.sh ",0,0,0},                 /*RTC测试*/
	//{'2',"2-uhost2.0","sudo bash /home/pi/work/uhost2.0.sh",0,0,0},   	 /*USB2.0测试    因为烧写mac地址时,会包含对U盘的读写操作*/
	{'3',"3-RS232"," sudo bash /home/pi/work/RS232.sh",0,0,0},           	 /*RS232测试*/
	{'4',"4-RS485_1"," sudo bash /home/pi/work/RS485_1.sh",0,0,0},         /*RS485_1测试*/
	{'5',"5-RS485_2"," sudo bash /home/pi/work/RS485_1.sh",0,0,0},         /*RS485_1测试*/
	{'6',"6-RS485_3"," sudo bash /home/pi/work/RS485_2.sh",0,0,0},         /*RS485_2测试*/
	{'7',"7-RS485_4"," sudo bash /home/pi/work/RS485_2.sh",0,0,0},         /*RS485_2测试*/
	{'8',"8-CAN"," sudo bash /home/pi/work/RS485_2.sh",0,0,0},         /*RS485_2测试*/
	{'9',"9-eth0","sudo bash /home/pi/work/eth0.sh",0,0,0},                /*网口0测试*/
	{'a',"a-buzzer","sudo bash /home/pi/work/buzzer.sh",0,0,0},	         /*buzzer测试*/
	{'b',"b-SD Card","sudo bash /home/pi/work/SDCard.sh",0,0,0},          	  /*camera测试*/ 
	{'c',"c-4G ","sudo bash /home/pi/work/camera.sh",0,0,0},          	  /*camera测试*/ 
	 
	
	
	/*DO需要在下一版再用*/
	
	/*以下待测项目经过和苏总讨论，去掉不用测试*/
//	{'c',"d-fan","sudo bash /home/pi/work/fan.sh",0,0,0},             	 /*fan测试*/
//	{'g',"g-4G","sudo bash /home/pi/work/4G.sh ",0,0,0},              	 /*4G测试*/
//  {'8',"8-bluetooth"," sudo bash /home/pi/work/bluetooth.sh",0,0,0},     /*bluetooth测试*/
//  {'b',"b-WIFI"," sudo bash /home/pi/work/wifi.sh",0,0,0},               /*WIFI测试*/
//	{'I',"I-UART"," sudo bash UART.sh",0,0,0},     /*bluetooth测试*/

    //最后要调换以下顺序	
};
/*******************************************************************************   
Function:    init_setpos_function
Description: 初始化功能名显示的起始坐标    
Input:       屏幕的最大尺寸   
Output:      无  
Return:      无 
 *******************************************************************************/
int init_setpos_function(int max_y ,int max_x)  
{

	int x,y;                      								/*循环坐标的变量*/
	int fun_index=0;              								/*功能函数的下标*/	
	int length = sizeof(fun)/sizeof(fun[0]);    				/*获取功能函数的个数*/	
	for(y=max_y/(ROW*2);y<max_y;y=y+(max_y/ROW))      		    /*因为显示的是ROW行格，需要在每一行的中间显示*/
	{
		for(x=0;x<max_x-(max_x/COLUMN);x=x+max_x/COLUMN)        /*因为显示的是COLUMN列，需要在每一列的开头显示*/
		{
			fun[fun_index].x_pos=x;
			fun[fun_index].y_pos=y;
            fun_index++;
			if(fun_index > length-1)                             /*超过功能函数的个数，退出内部循环*/
			{
				break;
			}
		}
		if(fun_index > length-1)       			                /*超过功能函数的个数，退出外部循环*/
			{
				break;
			}
	}
	refresh();
	return 0;
}
/*******************************************************************************   
Function:    frame_show
Description: 初始化框架线条    
Input:       屏幕的最大尺寸    
Output:      无  
Return:      无 
 *******************************************************************************/
int frame_show(int max_y ,int max_x)
{											
	int x,y;                                                  /*定义打印框架点的坐标*/
	initscr();     									 		  //初始化虚拟屏幕
	for(y=max_y/(ROW);y<=max_y;y=y+max_y/(ROW))               //打印横线
	{
		for(x=0;x<max_x;x++)  
		{
		   mvprintw(y,x,"-");
		}
	}
	
	x=max_x/COLUMN;	   
	for(;x<max_x-max_x/COLUMN;x=x+max_x/COLUMN)                           //打印竖线
	{
	  for(y=0;y<max_y;y++)
	  {
		 mvprintw(y,x,"|");	
	  }
	}	
	mvprintw(0,max_x/2-10,"CM4Industrial TEST V1.1");       /*打印测试详情*/
	refresh();
	return 0;
}
/*******************************************************************************   
Function:    function_show
Description: 在屏幕上显示待测试的功能模块   
Input:       无   
Output:      无  
Return:      无 
 *******************************************************************************/
int function_show(void)
{
	int x,y;
	int fun_index=0;
	int length = sizeof(fun)/sizeof(fun[0]);
	initscr();
	for(fun_index=0;fun_index<length;fun_index++)
	{
		mvprintw(fun[fun_index].y_pos,fun[fun_index].x_pos+OFFSET,fun[fun_index].name);
	}
	refresh();
	return 0;
}
/*******************************************************************************   
Function:    run_test
Description: 执行模块的功能测试，该函数会对所有的功能循环一遍测试
Input:       无   
Output:      无  
Return:      无 
 *******************************************************************************/
int run_test(void)
{
	int fun_index=0;
	int ret_value;
	char key_value;
	WINDOW *my_win;
	int length = sizeof(fun)/sizeof(fun[0]);
	
	for(fun_index=0;fun_index<length;fun_index++)
	{
		ret_value = system(fun[fun_index].shell_name);
	    //sprintf(str, "ret_value = %d     ", ret_value);
	    initscr();
		if(ret_value == 0)      				 //结果为0表示shell调用成功并且功能测试成功。
		{				
			init_pair(1,COLOR_GREEN,COLOR_BLACK);
			attron(COLOR_PAIR(1));
			mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos+OFFSET,"PASS");
			attroff(COLOR_PAIR(1));	
			fun[fun_index].result = 1;
		}
		else if (ret_value == 256) 				//结果为256表示shell调用成功但是功能测试失败。
		{
			init_pair(2,COLOR_RED,COLOR_BLACK);
			attron(COLOR_PAIR(2));
			mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos+OFFSET,"FAIL");
			attroff(COLOR_PAIR(2));
			fun[fun_index].result = -1;
		}
		else  									//其它值表示shell调用失败。
		{
			init_pair(2,COLOR_RED,COLOR_BLACK);
			attron(COLOR_PAIR(2));
			mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos+OFFSET,"ERROR");
			attroff(COLOR_PAIR(2)); 
			fun[fun_index].result = -1;
		}	
		refresh();
	}
	return 0;
}
/*******************************************************************************   
Function:    retest
Description: 对功能的单个测试，由键盘的字母对应确定。
Input:       无   
Output:      无  
Return:      无 
 *******************************************************************************/
void retest(void)
{
	int fun_index=0;
	int ret_value;
	int length = sizeof(fun)/sizeof(fun[0]);
	while(1)
	{
		char key_value;
		key_value = getchar();
		for(fun_index=0;fun_index<length;fun_index++)
		{
			if((key_value == fun[fun_index].index)||(key_value+32 == fun[fun_index].index))
			{
				
				//sprintf(str, "ret_value = %d     ", ret_value);
				initscr();
	            
				init_pair(0,COLOR_BLACK,COLOR_BLACK);
				attron(COLOR_PAIR(0));
				mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos+OFFSET,"    ");
				attroff(COLOR_PAIR(0));
				refresh();
				
				ret_value = system(fun[fun_index].shell_name);
				
				if(ret_value == 0)      				 //结果为0表示shell调用成功并且功能测试成功。
				{

					init_pair(1,COLOR_GREEN,COLOR_BLACK);
					attron(COLOR_PAIR(1));
					mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos+OFFSET,"PASS");
					attroff(COLOR_PAIR(1));
					fun[fun_index].result = 1;
					
				}
				else if (ret_value == 256) 				//结果为256表示shell调用成功但是功能测试失败。
				{
					init_pair(2,COLOR_RED,COLOR_BLACK);
					attron(COLOR_PAIR(2));
					mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos+OFFSET,"FAIL");
					attroff(COLOR_PAIR(2));
					fun[fun_index].result = -1;
				}
				else  									//其它值表示shell调用失败。
				{
					init_pair(2,COLOR_RED,COLOR_BLACK);
					attron(COLOR_PAIR(2));
					mvprintw(fun[fun_index].y_pos+1,fun[fun_index].x_pos+OFFSET,"ERROR");
					attroff(COLOR_PAIR(2)); 
					fun[fun_index].result = -1;
				}	
				refresh();
				break;
			}
					
		}
		
	}
}
/*******************************************************************************   
Function:    main
Description: 测试文件的主函数入口
Input:       argc:输入字符串个数  argv：输入的每个字符串的内容   
Output:      无  
Return:      无 
 *******************************************************************************/
int main(int argc, char *argv[])
{
	
	//WINDOW *local_win;
	//char str[80];
	//sleep(3);
	initscr();
	start_color();
	getmaxyx(stdscr,max_y,max_x);
	box(stdscr, 0, 0);  				   //打印四周的边框
	frame_show(max_y,max_x);
	init_setpos_function(max_y,max_x);
	function_show();
    run_test();
	refresh();
	retest();
	endwin();
	return 0;
}




	
