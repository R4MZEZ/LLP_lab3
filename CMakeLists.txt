cmake_minimum_required(VERSION 3.16)
project(LLP3 C)

set(CMAKE_C_STANDARD 99)

include_directories(parser)

include_directories(proto)
include_directories(proto/nanopb)

add_executable(LLP3
        proto/message.pb.c
        proto/nanopb/pb_common.c
        proto/nanopb/pb_decode.c
        proto/nanopb/pb_encode.c
        parser/lex.yy.c
        parser/y.tab.c
        parser/common.c parser/common.h)

add_executable(LLP3_server server.c parser/common.c
        proto/message.pb.c
        proto/nanopb/pb_common.c
        proto/nanopb/pb_decode.c
        proto/nanopb/pb_encode.c)