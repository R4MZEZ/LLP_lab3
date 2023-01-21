#ifndef LOW_LEVEL_PROGRAMMING_LAB_1_FIND_BY_COMMAND_H
#define LOW_LEVEL_PROGRAMMING_LAB_1_FIND_BY_COMMAND_H
#include "../../interface/crud_interface.h"
#include <stdbool.h>
#include "tools/string_tools.h"
#include "../../../../parser/headers/signatures.h"
#include <string.h>

void find_by(FILE *f, char **arr, size_t pattern_size, const uint32_t *pattern_types, char **pattern_names, size_t count);
void find_by_qtree(FILE *f, struct query_tree queryTree, size_t pattern_size, char **pattern_names);

#endif
