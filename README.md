# BroadcastChat


This program have the following features implemented:

- Each Client connected to the Server via TCP/IP.
- The Server can host until 10 clients.
- Each Client connected to the Server is able to send to the Server a character string passed by argument via command line arguments. 
- Server forward the received messages to all connected Clients.
- The Server identify the client that has sent the message. 
- Usage of POSIX Threads and device drivers.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

## To compile:

### server.c
The server.c must be compiled to the host:
you can use: gcc tcpserver.c -o <name_executable_server> -pthread

### client.c
The client.c can be compile for raspberry pi
you can use:  ~/buildroot/buildroot-2021.02.5/output/host/bin/aarch64-buildroot-linux-gnu-gcc tcpclient.c -o <name_executable_client>-pthread

if you not want to use raspberry pi
you just do: gcc tcpclient.c -o <name_executable_client> -pthread

#### NOTE
This program has the functionality, if the client is a raspberry, to turn on a led when the connection is made and turn off when it ends. For this purpose it is necessary to compile, and to this:
you can do: make
and then send executable to  the rasp using the scp command
If sucess you will se: 

[
![Captura de ecrã de 2021-12-08 16-24-30](https://user-images.githubusercontent.com/95348254/145245680-36ef5901-d67a-42ba-9a7d-728d976155e7.png)
](url)

------------------------------------------------------------------------------------------------------------------------------------------------------------------

## To run:

 ### tcpserver.c
you can use: ./<name_executable_server> <protocol_portnum>

 ### tcpclient.c
you can use: ./<name_executable_client>   <servername> <protocol_portnum>
If your client is the raspberry pi:
 if successful you should have the following output:
 
 ![2](https://user-images.githubusercontent.com/95348254/145248548-9a4b3f03-cbe5-4c61-a61f-a746ebad0a1c.png)

if the client is not raspberry pi
you shoul have the same output but with: 
 - insmod: ERROR: could not insert module led.ko: Operation not permitted
 - sh: 1: cannot create /sys/class/leds/led0/trigger: Directory nonexistent
 
 ##Attention
This only indicates that as the client is not raspberry, then it is not able to turn on the led when it starts the connection and turn it off when it finishes, the rest of the program should work in the same way.


------------------------------------------------------------------------------------------------------------------------------------------------------------------

 ## How it works:
 
Below is an example of communication using the server and two clients, one of them is on raspberry. 
 
 -1 
 
 
 









