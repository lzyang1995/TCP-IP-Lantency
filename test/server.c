#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#define SRVPORT 11111
#define MAX_NUM 80
int main()
{
    int serverSock=-1,clientSock=-1;
    struct sockaddr_in serverAddr;

    serverSock=socket(AF_INET,SOCK_STREAM,0);
    if(serverSock<0)
    {
        printf("socket creation failed\n");
        exit(-1);
    }
    printf("socket create successfully.\n");

    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons((u_short) SRVPORT);
    serverAddr.sin_addr.s_addr=htons(INADDR_ANY);
    if(bind(serverSock,&serverAddr,sizeof(struct sockaddr_in))==-1)
    {
        printf("Bind error.\n");
        exit(-1);
    }
    printf("Bind successful.\n");

    if(listen(serverSock,10)==-1)
    {
        printf("Listen error!\n");
    }
    printf("Start to listen!\n");

    char revBuf[MAX_NUM]={0};
    char sedBuf[MAX_NUM]={0};
    sedBuf[0] = 's';
    while(1)
    {
        clientSock=accept(serverSock,NULL,NULL);
        printf("Client connected.\n");
        while(1)
        {
            if(read(clientSock,revBuf,MAX_NUM)==-1)
            {
                printf("read error.\n");
                exit(-1);
            }
            printf("Client Msg: %s\n", revBuf);
            
            if(write(clientSock,sedBuf,2)==-1)
            {
                printf("Send error!\n");
                exit(-1);
            }
        }
        close(clientSock);
    }
    close(serverSock);
    return 0;
}
