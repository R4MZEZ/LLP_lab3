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

enum ERR_CODES{
    OK,
    PATTERN_ERROR,
    BOOL_ERROR,
    FLOAT_ERROR,
    INT_ERROR,
    STR_ERROR,
    COUNT_ERROR
};

#endif
