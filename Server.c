
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<netinet/tcp.h>
#include<netdb.h>
#include<ctype.h>

int main()
{

    
    int skt_fd, bndd, clnt_fd;
    char fname[50];
    struct sockaddr_in my_add;
    struct sockaddr_in clnt_add;


    //creating socket
    skt_fd=socket(AF_INET,SOCK_STREAM,0);
    if(skt_fd == -1)
    {

        perror("Socket can't be created.\n Exiting.");
        exit(1);
    }


    
    my_add.sin_family = AF_INET;
    my_add.sin_port = htons(9002);
    my_add.sin_addr.s_addr = INADDR_ANY;
    memset(my_add.sin_zero,'\0',sizeof(my_add.sin_zero));


	//binding


    bndd = bind(skt_fd, (struct sockaddr*)&my_add, sizeof(my_add));
    if(bndd == -1)
    {

        perror("Error in binding.\n Exiting.");
        exit(1);
    }


    //listen
    while(listen(skt_fd,1) >=0)
    {

        break;
    }

    //accept
	
        clnt_fd=accept(skt_fd,NULL,NULL);
        if(clnt_fd==-1)
        {

            perror("Error in accepting the client.");
        }
        printf("Connected with client!\n");
        char sm[1024],cm[1024];
 	char tr[5]="BYE";
	while(1)
		{
			bzero(cm,1024);
			listen(clnt_fd,1);
        		read(clnt_fd,cm,sizeof(cm));
			printf("\n Client: %s",cm);
			if(strncmp(cm, tr, 3)==0)
				break;
			bzero(sm,1024);
			printf("\n Server: ");
			fgets(sm,1024,stdin);
			write(clnt_fd,sm,sizeof(sm));
		}
	close(clnt_fd);
        close(skt_fd);
    
    return 0;
}

