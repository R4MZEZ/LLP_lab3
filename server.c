#include <pb_encode.h>
#include <pb_decode.h>
#include "proto/message.pb.h"
#include "include/common.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "db/src/initializer.h"
#include "db/src/ui/interactive.h"

#define PORT 3939


int main(int argc, char **argv) {
    setbuf(stdout, 0);
    FILE* file = initializer(argc, argv);

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
    pb_ostream_t output = pb_ostream_from_socket(connfd);

    char* response = "";
    while (1) {
        Query_tree t = {};
        if (!pb_decode_delimited(&input, Query_tree_fields, &t))
        {
            printf("Decode failed: %s\n", PB_GET_ERROR(&input));
            return 2;
        }


        handle_query(file, t, &response);

        Response r = {};
        while(strlen(response) > 1023){
            strncpy(r.r_string, response, 1023);
            r.r_string[1023] = 0;
            r.last = 0;
            if (!pb_encode_delimited(&output, Response_fields, &r))
            {
                fprintf(stderr, "Encoding failed: %s\n", PB_GET_ERROR(&output));
            }
            response += 1023;
        }
        strcpy(r.r_string, response);
        r.last = 1;
        if (!pb_encode_delimited(&output, Response_fields, &r))
        {
            fprintf(stderr, "Encoding failed: %s\n", PB_GET_ERROR(&output));
        }


    }

}
