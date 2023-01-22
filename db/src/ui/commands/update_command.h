#ifndef LOW_LEVEL_PROGRAMMING_LAB_1_UPDATE_COMMAND_H
#define LOW_LEVEL_PROGRAMMING_LAB_1_UPDATE_COMMAND_H

#include "tools/string_tools.h"

size_t update_item(FILE *f, char **str, size_t pattern_size, const uint32_t *pattern_types, char **pattern_names, size_t fields_count);
size_t update_item_new(FILE *f, uint64_t id, Query_tree_Value_setting* settings, size_t settings_count,
                       size_t pattern_size, const uint32_t *pattern_types, char **pattern_names) ;
#endif