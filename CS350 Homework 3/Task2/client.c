#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <sys/time.h>
struct timeval client_start_time;

int main(int argc , char *argv[])
{
	int sock;
	int state =0;
	struct sockaddr_in server;
	char message[1000] , server_reply[2000];
	char queue_msg[100] = "You are in the queue!";
	char expected_chat_msg[100] = "You are in the chat!";
	char inform[2000] = "Server is full!";
	char timeout_msg[100] = "Timeout!";
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	puts("Connected\n");

	if (recv(sock, server_reply, 2000, 0) < 0){
        	puts("recv failed");
        	return 1;
    }
	puts(server_reply);

	if(strncmp(server_reply, inform, 12) == 0) {
    	//puts("Server is full! Connection refused.");
		close(sock);
    	return 0;
	}
    if(strncmp(server_reply, queue_msg,21)==0) {
    	state =0;
    }else if(strncmp(server_reply, expected_chat_msg,20)==0){
    	state = 1;
    }
    memset(server_reply, 0, sizeof(server_reply));
	if(!state){
		while(1){
			if (recv(sock, server_reply, 2000, 0) < 0) {
                puts("recv failed");
				memset(server_reply, 0, sizeof(server_reply));
                break;
            }
			if(strncmp(server_reply, expected_chat_msg,20)==0){
				state = 1;
				puts(server_reply);
				memset(server_reply, 0, sizeof(server_reply));
				break;
			}
		}
	}
	gettimeofday(&client_start_time, NULL);
	struct timeval current_time;
	while(1)
	{	
		gettimeofday(&current_time,NULL);
		double elapsed_time = (current_time.tv_sec - client_start_time.tv_sec) + (current_time.tv_usec - client_start_time.tv_usec) / 1000000.0;
        if(elapsed_time>10.0){
			printf("Time is over. Connection closed.\n");
            break;
		}
    	printf("Enter message : ");
		//scanf("%s" , message);
		fgets(message, sizeof(message), stdin);
		message[strcspn(message, "\n")] = '\0';

		//Send some data
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sock , server_reply , 2000 , 0) < 0)
		{
			puts("recv failed");
			break;
		}
		if(strncmp(server_reply, timeout_msg,21)==0)  {
            break;
        }
		puts("Server reply :");
		puts(server_reply);
		 // Reset the message array to zero
        memset(message, 0, sizeof(message));
		memset(server_reply, 0, sizeof(server_reply));
         // Reset the server array to zero	
	}
	
	close(sock);
	return 0;
}
