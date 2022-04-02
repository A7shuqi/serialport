/**
 * @file sport.cpp
 * @author zk (zk@domain.com)
 * @brief   
 * @version 0.1
 * @date 2022-04-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "sport.h"


int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300,
	    			B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  300,
	    			38400,  19200,  9600, 4800, 2400, 1200,  300, };

/**
 * @brief 
 * 
 *              open serial port
 * @param fd 
 * @param path 
 * @return int 
 */

int  returndescribe(int &fd,char*path)
{
    fd = open(path,   O_RDONLY|O_NOCTTY|O_NDELAY);
    if(fd > -1)
    {
        printf("open serial portsuccessful\n ");
    }
    else
    {
        printf("open error\n");

    }
    return fd;
}

/**
 * @brief Set the speed object
 * 
 * @param fd 
 * @param speed 
 */
void set_speed(int &fd,int speed)
{
  int   i;
  int   status;
  struct termios   Opt;
  tcgetattr(fd, &Opt);
  for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
  {
   	if  (speed == name_arr[i])
   	{
   	    tcflush(fd, TCIOFLUSH);
    	cfsetispeed(&Opt, speed_arr[i]);
    	cfsetospeed(&Opt, speed_arr[i]);
    	status = tcsetattr(fd, TCSANOW, &Opt);
    	if  (status != 0)
            perror("tcsetattr fd1");
     	return;
    }
    tcflush(fd,TCIOFLUSH);
  }
}

/**
 * @brief  Set the Parity object
 * 
 * @param fd 
 * @param databits 
 * @param stopbits 
 * @param parity 
 * @return int 
 */
int set_Parity(int fd,int databits,int stopbits,int parity)
{
    struct termios options;
 	if( tcgetattr( fd,&options)  !=  0)
  	{
 	 	perror("SetupSerial 1");
 	 	return(FALSE);
  	}
 	options.c_cflag &= ~CSIZE;
  	switch (databits)
  	{
  		case 7:
  			options.c_cflag |= CS7;
  			break;
  		case 8:
			options.c_cflag |= CS8;
			break;
		default:
			fprintf(stderr,"Unsupported data size\n");
			return (FALSE);
	}
	
   	switch (parity)
  	{
 	 	case 'n':
		case 'N':
			options.c_cflag &= ~PARENB;   	//Clear parity enable 
			options.c_iflag &= ~INPCK;     	// Enable parity checking
			break;
		case 'o':
		case 'O':
			options.c_cflag |= (PARODD | PARENB); //set as odd check 
			options.c_iflag |= INPCK;             		//Disenable parity check
			break;
		case 'e':
		case 'E':
			options.c_cflag |= PARENB;    		//Enable parity 
			options.c_cflag &= ~PARODD; 
			options.c_iflag |= INPCK;      		//Disenable parity checking
			break;		
		case 'S':
		case 's':  //as no parity
			options.c_cflag &= ~PARENB;
			options.c_cflag &= ~CSTOPB;
			break;
		default:
			fprintf(stderr,"Unsupported parity\n");
			return (FALSE);
		}

 	 switch (stopbits)
  	{
  		case 1:
  			options.c_cflag &= ~CSTOPB;
			break;
		case 2:
			options.c_cflag |= CSTOPB;
			break;
		default:
			fprintf(stderr,"Unsupported stop bits\n");
			return (FALSE);
	}
  	//Set input parity option
  	if (parity != 'n')
  		options.c_iflag |= INPCK;
    options.c_cc[VTIME] = 150; // 15 seconds
    options.c_cc[VMIN] = 0;

  	tcflush(fd,TCIFLUSH); 		// Update the options and do it NOW
  	if (tcsetattr(fd,TCSANOW,&options) != 0)
  	{
  		perror("SetupSerial 3");
		return (FALSE);
	}
  	return (TRUE);
}


