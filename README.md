# BroadcastChat

This program have:

Each Client connected to the Server via TCP/IP.
The Server can host until 10 clients.
Each Client connected to the Server is able to send to the Server a character string passed by argument via command line arguments. 
Server forward the received messages to all connected Clients.
The Server identify the client that has sent the message. 
Usage of POSIX Threads and device drivers.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------


 *tcpserver*

1-Compile for host

2-Run using this format: ./<name_executable> <protocol or portnum>

3- whenever a new client enters the chat, the server will print who enter in the chat

*Makefile*

for works:

1-Open makefile

2-change KDIR

3-change ARCH

4-CROSS_COMPILE 


 *tcpclient.c*

1-Compile for raspberry pi

2-We must do make and this will compile the led.ko for raspberry pi

(In this file whenever the connection was stable we will turn on a 
raspberry led and whenever the connection ends the led will have to 
turn off so we need this make)

3- Run using this format: ./<name_executable>   <servername> <protocol or portnum>
 
4- The server will ask for the name and the you have to respond

5- You can then send the messages you want

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------












