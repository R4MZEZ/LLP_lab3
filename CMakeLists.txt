cmake_minimum_required(VERSION 3.16)
project(LLP3 C)

set(CMAKE_C_STANDARD 99)

include_directories(parser)

include_directories(proto)
include_directories(proto/nanopb)

add_executable(LLP3_client
        proto/message.pb.c
        proto/nanopb/pb_common.c
        proto/nanopb/pb_decode.c
        proto/nanopb/pb_encode.c
        parser/lex.yy.c
        parser/y.tab.c
        parser/common.c parser/headers/common.h)


add_executable(LLP3_server server.c parser/common.c
        proto/message.pb.c
        proto/nanopb/pb_common.c
        proto/nanopb/pb_decode.c
        proto/nanopb/pb_encode.c
        db/src/filetools/basic_file_manager.c
        db/src/filetools/big_data_tools.c
        db/src/generator/empty_generator.c
        db/src/interface/basic_crud.c
        db/src/interface/crud_interface.c
        db/src/ui/commands/tools/string_tools.c
        db/src/ui/commands/add_command.c
        db/src/ui/commands/find_by_command.c
        db/src/ui/commands/help_command.c
        db/src/ui/commands/update_command.c
        db/src/ui/interactive.c
        db/src/initializer.c
        )