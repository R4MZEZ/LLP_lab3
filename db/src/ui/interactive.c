#include "interactive.h"

void handle_query(FILE *f, Query_tree tree){
    size_t pattern_size;
    size_t err_code;
    struct tree_header *header = malloc_test(sizeof(struct tree_header));

    read_tree_header(header, f);
    pattern_size = header->subheader->pattern_size;
    uint32_t *pattern_types = malloc_test(sizeof(uint32_t) * pattern_size);
    char **pattern_names = malloc_test(sizeof(char *) * pattern_size);

    for (int i = 0; i < pattern_size; i++) {
        pattern_types[i] = header->pattern[i]->header->type;
        pattern_names[i] = header->pattern[i]->key_value;
    }

    struct result_list_tuple *result = NULL;
    switch (tree.command) {
        case 0:
            find_by_filters(f, tree.filters, tree.filters_count, &result, pattern_names);
            if (result != NULL) {
                printf("--- FIND RESULT ---\n");
                do {
                    printf("--- TUPLE %3zu ---\n", result->id);
                    for (size_t iter = 0; iter < pattern_size; iter++) {
                        if (pattern_types[iter] == STRING_TYPE) {
                            char *s;
                            read_string_from_tuple(f, &s, pattern_size, result->value->data[iter]);
                            printf("%-20s %s\n", pattern_names[iter], s);
                            free_test(s);
                        } else if (pattern_types[iter] == INTEGER_TYPE || pattern_types[iter] == BOOLEAN_TYPE) {
                            printf("%-20s %lu\n", pattern_names[iter], result->value->data[iter]);
                        } else if (pattern_types[iter] == FLOAT_TYPE) {
                            double res;
                            memcpy(&res, &(result->value->data[iter]), sizeof(result->value->data[iter]));
                            printf("%-20s %.6f\n", pattern_names[iter], res);
                        }
                    }
                    result = result->prev;
                } while (result != NULL);
            }else
                printf("--- NO RESULTS ---\n");
            break;
        case 1:
            find_by_filters(f, tree.filters, tree.filters_count, &result, pattern_names);
            if (result != NULL) {
                printf("--- REMOVE RESULT ---\n");
                do {
                    if (remove_tuple(f, result->id, 0) == CRUD_INVALID)
                        printf("Already removed ");
                    else
                        printf("Removed successfully ");
                    printf("id: %lu\n", (uint64_t) result->id);
                    result = result->prev;
                } while (result != NULL);
            }else
                printf("--- NO RESULTS ---\n");
            break;
        case 2:
            err_code = add_input_item_new(f, tree.settings, tree.settings_count,
                                          tree.filters[0].comp_list[0].fv.int_val,
                                          pattern_size, pattern_types, pattern_names);
            if (err_code != 0) {
                printf("Error code: %zu\n", err_code);
            }
            break;
        case 3:
            find_by_filters(f, tree.filters, tree.filters_count, &result, pattern_names);
            if (result != NULL) {
                printf("--- UPDATE RESULT ---\n");
                do {
                    err_code = update_item(f, result->id, tree.settings, tree.settings_count, pattern_size,
                                           pattern_types, pattern_names);
                    if (err_code != 0) {
                        printf("Error code: %zu\n", err_code);
                    }
                    printf("Updated id: %lu\n", (uint64_t) result->id);
                    result = result->prev;
                } while (result != NULL);
            }else
                printf("--- NO RESULTS ---\n");
            break;

    }

    free_test_tree_header(header);
    free_test(pattern_names);
    free_test(pattern_types);
}
