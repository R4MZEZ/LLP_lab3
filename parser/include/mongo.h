#ifndef LLP3_MONGO_H
#define LLP3_MONGO_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "signatures.h"
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "common.h"
#include "../proto/message.pb.h"
#include <pb_encode.h>
#include <pb_decode.h>
#include <arpa/inet.h>


void print_tree();
void set_cur_operation(uint8_t operation);
void set_cur_value(char* field, uint64_t val, double fval);
void append_val_setting(char* field, uint64_t val, double fval);
void switch_filter();
void set_comp();
void set_command(uint8_t command);
void *test_malloc(size_t size_of);
void print_ram();
void send_data();

#endif
