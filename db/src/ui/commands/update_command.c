#include "include/update_command.h"

size_t update_item(FILE *f, uint64_t id, Query_tree_Value_setting* settings, size_t settings_count,
                   size_t pattern_size, const uint32_t *pattern_types, char **pattern_names) {
    int8_t par_pos = -1;
    uint64_t value;

    for (int s_idx = 0; s_idx < settings_count; ++s_idx) {

        for (size_t in_iter = 0; in_iter < pattern_size; in_iter++) {
            if (strcmp(settings[s_idx].fv.field, pattern_names[in_iter]) == 0) {
                par_pos = in_iter;
                break;
            }
        }
        if (par_pos == -1) {
            printf("'%s' field does not match pattern.\n", settings->fv.field);
            return 3;
        }

        double val;
        switch (pattern_types[par_pos]) {
            case BOOLEAN_TYPE:
                if (settings[s_idx].fv.int_val == 1)
                    value = true;
                else if (settings[s_idx].fv.int_val == 0)
                    value = false;
                else {
                    printf("Not-bool '%lu'\n", settings[s_idx].fv.int_val);
                    return 4;
                }
                break;
            case FLOAT_TYPE:
                if (settings[s_idx].fv.val_type != 2) {
                    printf("Not-float '%f'\n", settings[s_idx].fv.real_val);
                    return 4;
                }
                val = settings[s_idx].fv.real_val;
                memcpy(&value, &val, sizeof(val));
                break;
            case INTEGER_TYPE:
                if (settings[s_idx].fv.val_type != 1) {
                    printf("Not-int '%lu'\n", settings[s_idx].fv.int_val);
                    return 4;
                }
                value = settings[s_idx].fv.int_val;
                break;
            case STRING_TYPE:
                if (settings[s_idx].fv.val_type != 0) {
                    printf("Not-str '%s'\n", settings[s_idx].fv.str_val);
                    return 4;
                }
                char* tmp = malloc(64);
                strcpy(tmp, settings[s_idx].fv.str_val);
                value = (uint64_t) tmp;
                break;
        }

        update_tuple(f, par_pos, &value, id);
        par_pos = -1;
    }
    return 0;
}

