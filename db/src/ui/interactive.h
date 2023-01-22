#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "../interface/crud_interface.h"
#include <stdbool.h>
#include "commands/add_command.h"
#include "commands/find_by_command.h"
#include "commands/help_command.h"
#include "commands/update_command.h"
#include "../../../parser/headers/signatures.h"
#include "message.pb.h"


void interactive_mode(FILE* f);
void handle_query(FILE *f, Query_tree tree);

#endif
