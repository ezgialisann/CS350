#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include <pthread.h> 
#include <sys/time.h>

#define CLIENT_COUNT 3
#define CLIENTS_IN_CHAT 2

pthread_mutex_t clients_mutex;

int total_client = 0;
struct timeval client_start_time;


void *client_connection (void *socket_desc)
{
    int client_sock = *(int *)socket_desc;
    char client_message[2000];
    int read_size;
	
    char queue_msg[] = "You are in the queue!";
    char chat_msg[] = "You are in the chat!";

	if (total_client==CLIENT_COUNT){
        write(client_sock, queue_msg, strlen(queue_msg));
        while (total_client==CLIENT_COUNT) {
    	}
	}
	memset(client_message, 0, sizeof(client_message));
    write(client_sock, chat_msg, strlen(chat_msg));
	gettimeofday(&client_start_time, NULL);
	struct timeval current_time;
    // Receive a message from the client
    while (((read_size = recv(client_sock, client_message, 2000, 0)) > 0))
    {	gettimeofday(&current_time,NULL);
		double elapsed_time = (current_time.tv_sec - client_start_time.tv_sec) + (current_time.tv_usec - client_start_time.tv_usec) / 1000000.0;
        if(elapsed_time<=10.0){
			write(client_sock, client_message, strlen(client_message));
        	memset(client_message, 0, sizeof(client_message));
		}else{
			pthread_mutex_lock(&clients_mutex);
			total_client--;
			pthread_mutex_unlock(&clients_mutex);
			close(client_sock);
            break;
		}
    }
    if (read_size == 0)
    {	
        puts("Client disconnected");
		pthread_mutex_lock(&clients_mutex);
		total_client--;
		pthread_mutex_unlock(&clients_mutex);
		close(client_sock);
        fflush(stdout);
		return NULL;
    }
    else if (read_size == -1)
    {
        perror("recv failed");
    } 
	
    return NULL;
}

void start_chat_timer();

int main(int argc , char *argv[])
{	
	
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[2000];
	pthread_t client_threads;
	pthread_mutex_init(&clients_mutex, NULL);

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	//accept connection from an incoming client
	while(1){
		if (total_client >= CLIENT_COUNT) {
			client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
        	if (client_sock >= 0) {
            	char full_message[] = "Server is full!";
            	write(client_sock, full_message, strlen(full_message));
            	close(client_sock);
        	}
			
		}else if(total_client<CLIENT_COUNT ){
			client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
			if (client_sock < 0){
			perror("accept failed");
			return 1; 
			}
			puts("Connection accepted");
			pthread_mutex_lock(&clients_mutex);
			total_client++;
			pthread_mutex_unlock(&clients_mutex);
			pthread_create(&client_threads, NULL,client_connection, (void *)&client_sock);
			}
		
	}
	
	return 0;
}