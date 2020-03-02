#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<netinet/tcp.h>
#include<netdb.h>
#include<ctype.h>

int main()
{
    int srvr_fd,cnnd;
    struct sockaddr_in my_add;
        //creating socket
    srvr_fd=socket(AF_INET,SOCK_STREAM,0);
    if(srvr_fd == -1)
    {

        perror("Socket can't be created.\n Exiting.");
        exit(1);
    }
        //create socket
    my_add.sin_family = AF_INET;
    my_add.sin_port = htons(9002);
    my_add.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(my_add.sin_zero,'\0',sizeof(my_add.sin_zero));
	//connect
    cnnd = connect(srvr_fd, (struct sockaddr*)&my_add, sizeof(my_add));
    if(cnnd == -1)
    {

        perror("Error in connecting.\t Exiting.");
        exit(1);
    }
	char buffer[1024];
	bzero(buffer,1024);
	FILE *f;
	int words=0;
	char c;
	f = fopen("SS.txt","r");
	while((c = getc(f)) != EOF)
	{
		fscanf(f , "%s" , buffer);
		if(isspace(c) || c == '\t')
		words++;
	}
	char wrd[1024];
	bzero(wrd,1024);
	sprintf(wrd,"%d",words);
	send(srvr_fd , wrd ,strlen(wrd),0);
	rewind(f);
	char cn;
	while(cn != EOF)
	{
		fscanf(f , "%s" , buffer);
		write(srvr_fd , buffer , 1024);
		cn = fgetc(f);
	}
	fclose(f);
	printf("The file has been successfully sent.\n");
    
    close(srvr_fd);
    return 0;
}

