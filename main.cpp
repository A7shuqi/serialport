#include "sport.h"

int main (int argc, char *argv[])
{

    // set object
    int  fd  =  open(argv[1],O_WRONLY);    // set read write  
    int nread;
    char *ptr=argv[2];


    //distribute  object
    if(argc<3)
    {
		printf("pls usage %s /dev/ttyS[n] your_message.\n",argv[1]);
		exit(EXIT_FAILURE);
    }
    if( fd == -1 )
    {
		perror("open");
		exit(EXIT_FAILURE);
    }    
    set_speed(fd,19200);

    if (set_Parity(fd,8,1,'N')== FALSE)
    {
    	    	printf("Set Parity Error\n");
        		exit(EXIT_FAILURE);
    }

     //use object 
   if(write(fd,ptr,strlen(ptr))<0)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
    printf("pls check the tty data\n");
    close(fd);

    return 0;
}