#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#pragma once
#include "commands/include/add_command.h"
#include "commands/include/find_by_command.h"
#include "commands/include/update_command.h"
#include "message.pb.h"

void handle_query(FILE *f, Query_tree tree, char **response_);

#endif
