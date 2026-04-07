#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sfd, newsfd;
    char buffer[512];

    struct sockaddr_in server, client;
    socklen_t len;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0)
    {
        perror("socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(3050);
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(sfd,(struct sockaddr*)&server,sizeof(server)) < 0)
    {
        perror("bind");
        return 1;
    }

    listen(sfd,5);

    printf("Server waiting for connection...\n");

    len = sizeof(client);
    newsfd = accept(sfd,(struct sockaddr*)&client,&len);

    if(newsfd < 0)
    {
        perror("accept");
        return 1;
    }

    printf("Client connected\n");

    while(1)
    {
        memset(buffer,0,sizeof(buffer));

        int n = read(newsfd,buffer,sizeof(buffer));

        if(n <= 0)
        {
            printf("Client disconnected\n");
            break;
        }

        printf("%s",buffer);
    }

    close(newsfd);
    close(sfd);

    return 0;
}
// PR test change
