/**********************************************************
*client.c -->program to calculate tax,count strings and convert to uppercase
*Authors:MWAI MOSES MURAGURI    i39/4458/2014       
       :GITAU KELVIN             i39//2014
*Platform:linux

*Date Created:24/5/2017
*Usage:Runs the program waits for connection from clients
***********************************************************/

//declare header files
#include<stdio.h>//header file for i/o
#include <unistd.h>//for null pointer definition
#include<stdlib.h>//for standard library in c
#include<sys/types.h>//header file for socket
#include<sys/socket.h>//for socket
#include<netinet/in.h>//for in_addr structure
#include <arpa/inet.h>//for type in_port_t and in_addr_t
#include<errno.h>//header file for perror
#include <ctype.h>
#include<string.h>
//declare global varibles
char msg[5000];

char *msgarr[2];
char str[5000];
char *str_2;
char *str_upper;	
char *msg2;
char msg_output[5000];
char *rcv_msg;
	
char clp[]="error occured";
int a,cli,sent,rcv,sock;
unsigned int len,clilen;

//function declaration
float getTax(float basic);

int main(){	
	     
	//clear buffer of msg variable;
	bzero(msg,sizeof(msg));
	bzero(msg_output,sizeof(msg_output));
	

	//create tcp/ip socket and check for errors
	if((sock =socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket ");
		exit(-1);	
	}
        
        //create socket structure
	struct sockaddr_in server,client;
        //set the family to use ipv4
	server.sin_family =AF_INET;
        //set port and convert from host to network byte order
	server.sin_port =htons(12244);
        //set the ip address
	server.sin_addr.s_addr =inet_addr("127.0.0.1");
        //clearing the buffer of server struct;
	bzero(&server.sin_zero,8);
       //get the size of server and client structure	
	len =sizeof(server);
	clilen =sizeof(client);
		//bind socket
	if((bind(sock,(struct sockaddr *)&server,len)) ==-1){
		perror("bind ");
		exit(-1);
	}
		//listen
	int listn =listen(sock,5);
	if(listn ==-1){
		perror("listen ");
		exit(-1);
	}
		printf("Server waiting for incoming connections !\n");   

		//wait for connection
                	
	   
	
     while(1){
                //accept connection from client  
		cli =accept(sock, (struct sockaddr *) &client , &clilen);
		//clear the msg output buffer		
		bzero(msg_output,sizeof(msg_output));
                 if(cli>0){
			
                        //receive message from client
			 rcv = recv(cli,(char*)&msg,sizeof(msg),0);

                         char *pch;
			 int i =0;
			 float tax;			 
			 int u =0;
		         int j =0;
			 int count =-1;
		         
			
			//split the msg into 2 parts using collon as delimeter
			//store each part in variable pch;	
                         pch =strtok(msg,":");
				         while(pch !=NULL){
				         msgarr[i]=pch;					 
				         pch=strtok(NULL,":");  
				         i++ ;
				         } 
					
				
			if(rcv>0){//start of checking if recv is succesful
					  //compare if 1st input from client is upper
				          if(strcmp(msgarr[0],"upper")==0){ 
						
						msg2 = msgarr[1];
						while (j<strlen(msg2))
						{
							a = toupper(msg2[j]);sprintf(str,"%c",a);strcat(msg_output,str);
							j++;
						}
	                                       
							  
					         //send output to client
		 				sent =send(cli,msg_output,strlen(msg_output),0);
						
						printf("Received string: %s:%s\n",msgarr[0],msgarr[1]);
						printf("Sending string: %s\n",msg_output);
                         	        	 
			                      	
					         close(cli);   
					   }//end of checking if upper: is set

				           //compare if 1st input from client is tax
				          else if(strcmp(msgarr[0],"tax")==0){ 
													
						tax = getTax(atof(msgarr[1]));			
	                                       sprintf(msg_output,"%.2f",tax);
													  
					         //send output to client
		 				sent =send(cli,msg_output,strlen(msg_output),0);
						
						printf("Received: string %s:%s",msgarr[0],msgarr[1]);
						printf("Sending: string tax for: %.2f is %.2f to client:%s\n",
							atof(msgarr[1]),tax,
							inet_ntoa(client.sin_addr));      	        	 
			                      	
					         close(cli);   
					   }//end of checking if tax: is set

					   //compare if 1st input from client is count
				          else if(strcmp(msgarr[0],"count")==0){ 
						str_2 = msgarr[1];							
						while (str_2[u] !='\0')
						{
							
							count++;
							u++;
						}
	                                       sprintf(msg_output,"%d",count);
							  
					         //send output to client
		 				sent =send(cli,msg_output,strlen(msg_output),0);
						
						printf("Received %s:%s",msgarr[0],msgarr[1]);
						printf("Sending string: %d characters to client:%s\n",count,
							inet_ntoa(client.sin_addr));      	        	 
			                      	
					         close(cli);   
					   }//end of checking if count: is set
					   
					 
                                                          
                                        
                                         else{
                                           //send error message for unspecified input                                     
		 				sent =send(cli,clp,strlen(clp),0);
						
                         	        	 printf("sent error occured to client:%s\n",inet_ntoa(client.sin_addr));
			                      	
					         close(cli);   
					 }	
                                    			
			}//end of checking rcv
				else{
					perror("rcv");
					exit(-1);
				}
		}
			else{
	                  perror("accept");
	   	            exit(-1);
	                }
		
    }//end of while loop


	return 0;
	
}//end of main function

float getTax(float basic)
{
	float tax = 0, taxable = 0;
	 if (basic > 0) {
            taxable = (basic >= 10000) ? 10000 : basic;
            tax += taxable * 0.12;
            
        }
        if (basic >= 10001) {
            taxable = (basic >= 20000) ? 10000 : basic - 10000;
            tax += taxable * 0.10;
            
        }
        if (basic >= 20001) {
            taxable = (basic >= 40000) ? 20000 : basic - 20000;
            tax += taxable * 0.08;
            
        }
        if (basic >= 40001) {
            taxable = (basic >= 60000) ? 20000 : basic - 40000;
            tax += taxable * 0.06;
            
        }
        if (basic >= 60001) {
            taxable = (basic >= 80000) ? 20000 : basic - 60000;
            tax += taxable * 0.04;
            
        }
        if (basic >= 80001) {
            taxable = basic - 80000;
            tax += taxable * 0.02;
            
        }
        return tax;
    
}//end of function getTax

