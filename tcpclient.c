
/*****************************************************************************/
/*** tcpclient.c                                                           ***/
/***                                                                       ***/
/*** Demonstrate an TCP client.                                            ***/
/*****************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <pthread.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


    
/*The set of possible commands*/
#define NULL_COMMAND			0

 int fd0 ;
 char ledOn = '1', ledOff = '0';
 
//typedef struct messages  message;
struct messages
{
	char name[20];
	char message[20];	
}; 

void panic(char *msg);
#define panic(m)	{perror(m); abort();}


/* This function receive the message from server and show it to the client*/
void *threadRec(void *arg)                    
{	
	int sd = *(int*)arg;       
	char buffer[256];
 	struct messages ClientMessage;

	while(1)
	{
		if(recv(sd,&ClientMessage,sizeof(ClientMessage),0))
			printf("%s sent : %s\n",ClientMessage.name, ClientMessage.message );
	}
	

/* close the client's channel */                          
	shutdown(sd,SHUT_RD);
	shutdown(sd,SHUT_WR);
	shutdown(sd,SHUT_RDWR);

 /* terminate the thread */
	return 0;                           
}

/*This function send to the server the message from the client
  This function also  check if the command receive ia a CLOSE
  or not and if it is the the led before ON will be set to OFF
  and the connection will be shutdown
  */
void *threadSend(void *arg)                    
{	
	struct messages ClientMessage;
	int sd = *(int*)arg;
	
	while(1)
	{
		scanf("%s",ClientMessage.message);
		
		
		if( strcmp(ClientMessage.message, "CLOSE")==0)
		{ 
		//led off
       	 write(fd0, &ledOff, 1);
        	 printf("\noff!");
        	 sleep(4);
        	 printf("Closing Device Driver.\n");
  		 close(fd0);
  		 putchar('\n');
   		 printf("Removing Device Driver.\n");
    		 system("rmmod led");
    		 /* close the client's channel */  
		 shutdown(sd,SHUT_RD);
		 shutdown(sd,SHUT_WR);
		 shutdown(sd,SHUT_RDWR);
   		 }
   		 else
		 send(sd,ClientMessage.message,sizeof(ClientMessage.message),0);
	}

 /* close the client's channel */  
	shutdown(sd,SHUT_RD);
	shutdown(sd,SHUT_WR);
	shutdown(sd,SHUT_RDWR);

/* terminate the thread */
	return 0;                           
}
/****************************************************************************/
/*** This program opens a connection to a server using either a port or a ***/
/*** service.  Once open, it sends the message from the command line.     ***/
/*** some protocols (like HTTP) require a couple newlines at the end of   ***/
/*** the message.                                                         ***/
/*** Compile and try 'tcpclient lwn.net http "GET / HTTP/1.0" '.          ***/
/****************************************************************************/
int main(int count, char *args[])
{	struct hostent* host;
	struct sockaddr_in addr;
	int sd, port;

	if ( count != 3 )
	{
		printf("usage: %s <servername> <protocol or portnum>\n", args[0]);
		exit(0);
	}

	/*---Get server's IP and standard service connection--*/
	host = gethostbyname(args[1]);
	//printf("Server %s has IP address = %s\n", args[1],inet_ntoa(*(long*)host->h_addr_list[0]));
	if ( !isdigit(args[2][0]) )
	{
		struct servent *srv = getservbyname(args[2], "tcp");
		if ( srv == NULL )
			panic(args[2]);
		printf("%s: port=%d\n", srv->s_name, ntohs(srv->s_port));
		port = srv->s_port;
	}
	else
		port = htons(atoi(args[2]));

	/*---Create socket and connect to server---*/
	sd = socket(PF_INET, SOCK_STREAM, 0);        /* create socket */
	if ( sd < 0 )
		panic("socket");
	memset(&addr, 0, sizeof(addr));       /* create & zero struct */
	addr.sin_family = AF_INET;        /* select internet protocol */
	addr.sin_port = port;                       /* set the port # */
	addr.sin_addr.s_addr = *(long*)(host->h_addr_list[0]);  /* set the addr */

	/*---If connection successful, send the message and read results---*/
	if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) == 0)
	{
		
//led on

    printf("\n\nInserting Device Driver...\n");
    system("insmod led.ko");

    printf("\nCheck devicer driver:\n");
    system("lsmod");

    printf("\nIs the device driver in /dev:\n");
    system("ls -l /dev/led0");

fd0= open("/dev/led0", O_WRONLY);
   
    system("echo none >/sys/class/leds/led0/trigger");
 
        write(fd0, &ledOn, 1);
        printf("\non!");

			struct messages ClientMessage;

			//submit your name
	   	 	printf("What's your name?");
			scanf("%s",ClientMessage.name);
			send(sd,ClientMessage.name,sizeof(ClientMessage.name),0);		
			


		   	pthread_t send ,rec;

		   	pthread_create(&send, 0, threadSend, &sd);    /* start thread to send */
			pthread_create(&rec, 0, threadRec, &sd);   /* start thread to receive */

			
			pthread_join(rec,NULL); 
			
	}

	else
		panic("connect");
}




