/**
 * @file         sport.h
 * @author zk (zk@domain.com)
 * @brief  serial port .h
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include     <stdio.h>      /*标准输入输出定义*/
 
#include     <stdlib.h>     /*标准函数库定义*/
 
#include     <unistd.h>     /*Unix 标准函数定义*/
 
#include     <sys/types.h> 
 
#include     <sys/stat.h>  
 
#include     <fcntl.h>      /*文件控制定义*/
 
#include     <termios.h>    /*POSIX 终端控制定义*/
 
#include     <errno.h>      /*错误号定义*/
 
#include   <string.h>       /*字符串功能函数*/

#define     TRUE      0
#define     FALSE    1

/**
 * @brief 
 * 
 * @param fd 
 * @param path 
 * @return int 
 */
int  return_descriptor(int &fd,char*path);

/**
 * @brief Set the speed object
 * 
 * @param fd 
 * @param speed 
 */
void set_speed(int &fd, int speed);

/**
 * @brief Set the Parity object
 * 
 * @param fd 
 * @param databits 
 * @param stopbits 
 * @param parity 
 * @return int 
 */
int    set_Parity(int fd,int databits,int stopbits,int parity);

