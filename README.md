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


## To run:

 ### tcpserver.c
you can use: ./<name_executable_server> <protocol_portnum>

 ### tcpclient.c
you can use: ./<name_executable_client>   <servername> <protocol_portnum>

3- Run using this format: ./<name_executable>   <servername> <protocol_portnum>
 
4- The server will ask for the name and the you have to respond

5- You can then send the messages you want

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------












