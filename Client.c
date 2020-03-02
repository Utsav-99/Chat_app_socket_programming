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

    
    char srvr_rspns[1024],clnt_rspns[1024];
    char tr[5]="BYE";
    bzero(clnt_rspns,1024);
    bzero(srvr_rspns,1024);
    printf("\nClient: ");
    fgets(clnt_rspns,1024,stdin);
    write(srvr_fd,clnt_rspns,sizeof(clnt_rspns));
    while(1)
	{
		bzero(clnt_rspns,1024);
		bzero(srvr_rspns,1024);
		listen(srvr_fd,1);
		read(srvr_fd,srvr_rspns,sizeof(srvr_rspns));
		printf("\nServer: %s",srvr_rspns);
		printf("\nClient: ");
		fgets(clnt_rspns,1024,stdin);
		write(srvr_fd,clnt_rspns,sizeof(clnt_rspns));
		if(strncmp(clnt_rspns, tr, 3)==0)
			break;
	}  
    close(srvr_fd);
    return 0;
}

