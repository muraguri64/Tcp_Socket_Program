all : calc 	

calc:client.c server.c
	gcc client.c -o client
	gcc server.c -o server
	
