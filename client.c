/**********************************************************
*client.c -->program to calculate tax
*Authors:MWAI MOSES MURAGURI    i39/4458/2014       
       :GITAU KELVIN             i39//2014
*Platform:linux

*Date Created:24/5/2017
*Usage:Runs the program and outputs the the number of characters in a string
**********************************************************/

//declare header files
#include <stdio.h> //header file for i/o
#include <sys/types.h> //header file for socket
#include <sys/socket.h>//for socket
#include <netinet/in.h>//for in_addr structure
#include <string.h>//for manipulating strings and arrays
#include <stdlib.h>//for standard library in c
#include <unistd.h>//for null pointer definition
#include <errno.h>//header file for perror
#include <arpa/inet.h>//for type in_port_t and in_addr_t
	
	

int main(int argc ,char *argv[]){
   //check if only 1 parameter is passed at terminal
   if(argc==1){
	
	//declare variables to be used        
	char buff[5000];
	char sendmsg[5000];
	int sock,sent;
         
        //create a socket structure
       	struct sockaddr_in client;
	
	//get the user input
	printf("Enter a server request\n");
	fgets(sendmsg,5000,stdin);
	
	//check if user input is less than 5 chars
	if(strlen(sendmsg)<6)
	{
		exit(1);
	}

	else
	{
		//create a tcp/ip socket
		sock =socket(AF_INET,SOCK_STREAM,0);
	        //check if there was an error in creating socket
		if(sock<0){
		perror("socket failed");
		exit(1);
		}
	        //use the ipv4 family
		client.sin_family =AF_INET;
	        //set the port to 12244
		client.sin_port =htons(12244);
	        //set the address to localhost
		client.sin_addr.s_addr = inet_addr("127.0.0.1");
	        //get size of client structure
		int sizeofclient = sizeof(client);
	        //clear the buffer of buff variable and set to zero
		bzero(buff,5000);
	        //connect tothe server and check if there was error
		if(connect(sock, (struct sockaddr *)&client ,sizeof(client))<0){
		perror("connect failed");
		exit(-1);
		
		}
	
		else{
	              //if no error send msg
			printf("Sending %s",sendmsg);		            
	                
	  		sent = send(sock,sendmsg,sizeof(sendmsg),0);
			//check if error in sent
			if(sent>0){
	                       //receive the message from server and store in buff variable
				recv(sock , buff , sizeof(buff), 0);
	                      //print output from server 
	        		printf("Received: %s\n",buff);
			}
			else{
				perror("send");	
				exit(-1);
			}
		}
		
	}//end of checking if user input is > 5 chars	
	
	
  return 0;
  }//end of checking argc

  else
   {
     return -1;
   }  
          
	
}//end of int main

