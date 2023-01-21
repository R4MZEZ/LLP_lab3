#include <pb_encode.h>
#include <pb_decode.h>
#include "proto/message.pb.h"
#include "headers/common.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 3939


int main(void) {
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    int reuse = 1;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    servaddr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    {
        perror("bind");
        return 1;
    }

    if (listen(listenfd, 5) != 0)
    {
        perror("listen");
        return 1;
    }

    printf("server: waiting for connection…\n");
    connfd = accept(listenfd, NULL, NULL);

    if (connfd < 0)
    {
        perror("accept");
        return 1;
    }

    printf("Got connection.\n");

    pb_istream_t input = pb_istream_from_socket(connfd);

    while (1) {
        Query_tree t = {};
        if (!pb_decode_delimited(&input, Query_tree_fields, &t))
        {
            printf("Decode failed: %s\n", PB_GET_ERROR(&input));
            return 2;
        }
        printf("server: received `%d`\n", t.command);

    }

}
