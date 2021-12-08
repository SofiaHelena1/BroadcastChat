# BroadcastChat


This program has the following features implemented:

- Each Client is connected to the Server via TCP/IP.
- The Server can host until 10 clients.
- Each Client connected to the Server is able to send to the Server a character string passed by argument via command line arguments. 
- Server will forward the received messages to all connected Clients.
- The Server can identify the client that has sent the message. 
- Usage of POSIX Threads and device drivers.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

## To compile:

### server.c
The server.c must be compiled to the host:
you can use: gcc tcpserver.c -o <name_executable_server> -pthread

### client.c
The client.c can be compiled for raspberry pi
you can use:  ~/buildroot/buildroot-2021.02.5/output/host/bin/aarch64-buildroot-linux-gnu-gcc tcpclient.c -o <name_executable_client>-pthread

if don't want to use raspberry pi
you just do: gcc tcpclient.c -o <name_executable_client> -pthread

#### NOTE
if the client is a raspberry, this program has the functionality, of turning on a led when the connection is made and turn off when it ends. For this purpose it is necessary to compile, and to this:
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
 
 ## Attention
 This only indicates that the client is not raspberry, then it is not able to turn on the led when it starts the connection and turn it off when it finishes, the rest of the program should work in the same way.


------------------------------------------------------------------------------------------------------------------------------------------------------------------

 ## How it works:
 
Below is an example of communication using the server and two clients, one of them is a raspberry. 
 
 - 1 As you can see in the previous section, when you run the program on the client, you are asked for its name. After answering as you can see on the left side, the server, on the right side, informs you who entered the chat. As this client is on raspberry then you are supposed to see the led light up as soon as the connection is made.
 

 ![1](https://user-images.githubusercontent.com/95348254/145256231-03a06918-7c1e-4f99-888e-bcc43d9cfb01.png)
 
 
 - 2 Then another client connects to the server and the server retains its name and informs who entered.
  
 ![3](https://user-images.githubusercontent.com/95348254/145257498-d5ef8652-d4b8-4a10-b350-695148477fbe.png)
 
 
 - 3 An exchange of greetings is made between the first and second created clients, respectively. The server is able to always identify who sends the message and informs each client as well.
 
![4](https://user-images.githubusercontent.com/95348254/145257509-acce0ed8-a727-4a08-81ae-93cd291e872a.png)
 
 - 4 if a client writes CLOSE, the connection is terminated.
 
![6](https://user-images.githubusercontent.com/95348254/145259623-d1df73cb-1c9a-45f7-9a39-9db79ea9fed9.png)

 
 
 









