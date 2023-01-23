#ifndef LOW_LEVEL_PROGRAMMING_LAB_1_ADD_COMMAND_H
#define LOW_LEVEL_PROGRAMMING_LAB_1_ADD_COMMAND_H
#include "../tools/string_tools.h"


size_t add_input_item(FILE *f, char **str, size_t pattern_size, const uint32_t *pattern_types, char **pattern_names);
size_t add_input_item_new(FILE *f,
                          Query_tree_Value_setting *settings,
                          size_t settings_count,
                          uint64_t parent_id,
                          size_t pattern_size,
                          const uint32_t *pattern_types,
                          char **pattern_names);

#endif
