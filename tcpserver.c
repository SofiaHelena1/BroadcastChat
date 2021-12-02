
/*****************************************************************************/
/*** tcpserver.c                                                           ***/
/***                                                                       ***/
/*** Demonstrate an TCP server.                                            ***/
/*****************************************************************************/

#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <pthread.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

void panic(char *msg);
#define panic(m)	{perror(m); abort();}

/*The set of possible commands*/
#define NULL_COMMAND			0

#define MAX_CLIENT_NUM			10

struct messages
{
	char name[20];
	char message[20];	
}; 

typedef struct client_socket_into client_socket_info_t;
struct client_socket_into
{
	int socket;
	int state;
	int index;
	char name[50];
	//char message[20];
}; 


client_socket_info_t socket_table[MAX_CLIENT_NUM];



int newclient;

/*  From 5sec to5sec this function will send a request to all 
the client for check their states

static void sendPeriodicUpdate(int signo)
{
	int i;
	command_t cmd;
	struct messages ClientMessage;

	if(signo==SIGALRM)
	{

		for(i=0; i<MAX_CLIENT_NUM; i++)
		{
			if(socket_table[i].state)
				send(socket_table[i].socket,&ClientMessage.message,sizeof(ClientMessage.message),0);
		}
	}
}*/





/*This funtion sends the messages received to all 
customers indicating who sent the respective message */

void *threadfuntion(void *arg)                    
{	
	
 	client_socket_info_t *info = (client_socket_info_t *)arg; //guardar
  	int i;
	struct messages ClientMessage;

	while(1)
	{
		
		if (recv(info->socket,ClientMessage.message,sizeof(ClientMessage),0))
		{
			strcpy(ClientMessage.name,socket_table[info->index].name);

			printf("%s send : %s\n",info->name,ClientMessage.message);
			//send(info->socket,buffer,sizeof(buffer),0);

			for(i=0; i<MAX_CLIENT_NUM; i++)
			{
				if(socket_table[i].state)
					send(socket_table[i].socket,&ClientMessage,sizeof(ClientMessage),0);
			}
		}
		
	}

	shutdown(info->socket,SHUT_RD);
	shutdown(info->socket,SHUT_WR);
	shutdown(info->socket,SHUT_RDWR);

	//socket_table[info->index].state = 0;	/* marked as a already closed channel*/
	
	return 0;                           /* terminate the thread */
}

int main(int count, char *args[])
{	struct sockaddr_in addr;
	int listen_sd, port;

	if ( count != 2 )
	{
		printf("usage: %s <protocol or portnum>\n", args[0]);
		exit(0);
	}

	/*---Get server's IP and standard service connection--*/
	if ( !isdigit(args[1][0]) )
	{
		struct servent *srv = getservbyname(args[1], "tcp");
		if ( srv == NULL )
			panic(args[1]);
		printf("%s: port=%d\n", srv->s_name, ntohs(srv->s_port));
		port = srv->s_port;
	}
	else
		port = htons(atoi(args[1]));

	/*--- create socket ---*/
	listen_sd = socket(PF_INET, SOCK_STREAM, 0);
	if ( listen_sd < 0 )
		panic("socket");

	/*--- bind port/address to socket ---*/
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = INADDR_ANY;                   /* any interface */
	if ( bind(listen_sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		panic("bind");

	/*--- make into listener with 10 slots ---*/
	if ( listen(listen_sd, MAX_CLIENT_NUM) != 0 )
		panic("listen")

	/*--- begin waiting for connections ---*/
	else
	{	
		//struct itimerval itv;
		//Register the handler
		//signal(SIGALRM,sendPeriodicUpdate);	
		//itv.it_interval.tv_sec = 0;
		//itv.it_value.tv_sec = 0;
		//setitimer (ITIMER_REAL, &itv, NULL);

		int i=0;

		while (1)                         /* process all incoming clients */
		{
						
			int n = sizeof(addr);
			int sd = accept(listen_sd, (struct sockaddr*)&addr, &n);     /* accept connection */

			if(sd!=-1 && i<10)
			{

				//recebe o nome do cliente
            	recv(sd, socket_table[i].name , sizeof(socket_table[i].name),0);
	
				pthread_t child;
				socket_table[i].socket=sd;
				socket_table[i].state=1;		/*means connection opened*/
				socket_table[i].index=i;

				printf(" %s enter in chat\n", socket_table[i].name); //informs the server who joined the session
				pthread_create(&child, 0, threadfuntion, &socket_table[i]);       /* start thread */
				i++;
				pthread_detach(child);                      /* don't track it */
			}
		}
	}
}
