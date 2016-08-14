#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#define SRVPORT 11111
#define MAX_NUM 80
#define IP_ADDR "10.22.1.2"

int main()
{
    int clientSock=-1;
    struct sockaddr_in serverAddr;

    clientSock=socket(AF_INET,SOCK_STREAM,0);
    if(clientSock<0)
    {
        printf("socket creation failed\n");
        exit(-1);
    }
    printf("socket create successfully.\n");

    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons((u_short) SRVPORT);
    inet_aton(IP_ADDR, &serverAddr.sin_addr);

    if(connect(clientSock,&serverAddr,sizeof(struct sockaddr_in))<0)
    {
        printf("Connect error.\n");
        exit(-1);
    }
    printf("Connect successful.\n");

    char sedBuf[MAX_NUM]={0};
    char revBuf[MAX_NUM]={0};
    sedBuf[0] = 'c';

    if(write(clientSock,sedBuf,2)==-1)
    {
        printf("send error!\n");
        exit(-1);
    }
        
    if(read(clientSock,revBuf,MAX_NUM)==-1)
    {
        printf("rev error!\n");
        exit(-1);
    }
    printf("Server Msg: %s\n", revBuf);
    
    close(clientSock);
    return 0;
}