#include <pb_encode.h>
#include <pb_decode.h>
#include "proto/message.pb.h"
#include "headers/common.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "db/src/initializer.h"
#include "db/src/ui/interactive.h"

#define PORT 3939


int main(int argc, char **argv) {
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

    while (1) {
        Query_tree t = {};
        if (!pb_decode_delimited(&input, Query_tree_fields, &t))
        {
            printf("Decode failed: %s\n", PB_GET_ERROR(&input));
            return 2;
        }

        handle_query(file, t);





//        struct query_tree qtree = {};
//        qtree.command = 1;
//        qtree.filters = malloc(sizeof(struct filter));
//        qtree.filters->next = NULL;
//
//        qtree.filters->comp_list = malloc(sizeof(struct comparator));
//        qtree.filters->comp_list->next = NULL;
//        qtree.filters->comp_list->operation = 3;
//        struct field_value_pair fv = {.field = "age", .int_value = 50000};
//        qtree.filters->comp_list->fv = fv;
//
//        handle_query(file, qtree);
//
//
//
//
//        qtree.command = 2;
//        qtree.filters = malloc(sizeof(struct filter));
//        qtree.filters->next = NULL;
//
//        qtree.filters->comp_list = malloc(sizeof(struct comparator));
//        qtree.filters->comp_list->next = NULL;
//        qtree.filters->comp_list->operation = 0;
//        struct field_value_pair fv2 = {.field = "parent", .int_value = 1};
//        qtree.filters->comp_list->fv = fv2;
//
//        qtree.settings = malloc(sizeof (struct value_setting));
//        qtree.settings->next = malloc(sizeof (struct value_setting));
//        qtree.settings->next->next = NULL;
//
//        struct field_value_pair fv3 = {.field = "age", .int_value = 9999, .val_type=1};
//        struct field_value_pair fv4 = {.field = "name", .int_value = (uint64_t)"mr white", .val_type=0};
//        qtree.settings->fv = fv3;
//        qtree.settings->next->fv = fv4;
//
//        handle_query(file, qtree);
//
//
//        qtree.command = 0;
//        qtree.filters = malloc(sizeof(struct filter));
//        qtree.filters->next = NULL;
//
//        qtree.filters->comp_list = malloc(sizeof(struct comparator));
//        qtree.filters->comp_list->next = NULL;
//        qtree.filters->comp_list->operation = 3;
//        struct field_value_pair fv1 = {.field = "age", .int_value = 0};
//        qtree.filters->comp_list->fv = fv1;
//
//        handle_query(file, qtree);

//        printf("server: received `%s : %s`\n",  t.settings[1].fv.field, t.settings[1].fv.str_val);
//        printf("server: received `%u`\n",  t.filters_count);

    }

}
