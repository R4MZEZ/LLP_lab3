#include "interactive.h"

void handle_query(FILE *f, Query_tree tree, char **response_) {
    char *response = "";
    char tmp[256];
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
            err_code = find_by_filters(f, tree.filters, tree.filters_count, &result, pattern_names);
            if (err_code == 3) {
                response = concat(response, "At least one of your fields doesn't exist.\n");
                break;
            }
            if (result != NULL) {
                response = concat(response, "--- FIND RESULT ---\n");
                do {
                    sprintf(tmp, "--- TUPLE %3zu ---\n", result->id);
                    response = concat(response, tmp);
                    for (size_t iter = 0; iter < pattern_size; iter++) {
                        if (pattern_types[iter] == STRING_TYPE) {
                            char *s;
                            if (tree.filters_count == 1 && tree.filters[0].comp_list_count == 1 &&
                                strcmp(tree.filters[0].comp_list[0].fv.field, "id") == 0) {
                                s = (char*) result->value->data[iter];
                            }else{
                                read_string_from_tuple(f, &s, pattern_size, result->value->data[iter]);
                            }
                            sprintf(tmp, "%-20s %s\n", pattern_names[iter], s);
                            response = concat(response, tmp);
                            free_test(s);
                        } else if (pattern_types[iter] == INTEGER_TYPE || pattern_types[iter] == BOOLEAN_TYPE) {
                            sprintf(tmp, "%-20s %lu\n", pattern_names[iter], result->value->data[iter]);
                            response = concat(response, tmp);
                        } else if (pattern_types[iter] == FLOAT_TYPE) {
                            double res;
                            memcpy(&res, &(result->value->data[iter]), sizeof(result->value->data[iter]));
                            sprintf(tmp, "%-20s %.6f\n", pattern_names[iter], res);
                            response = concat(response, tmp);
                        }
                    }
                    result = result->prev;
                } while (result != NULL);
            } else
                response = concat(response,"--- NO RESULTS ---\n");
            break;
        case 1:
            err_code = find_by_filters(f, tree.filters, tree.filters_count, &result, pattern_names);
            if (err_code == 3) {
                response = concat(response,"At least one of your fields doesn't exist.\n");
                break;
            }
            if (result != NULL) {
                response = concat(response,"--- REMOVE RESULT ---\n");
                do {
                    if (remove_tuple(f, result->id, 0) == CRUD_INVALID)
                        response = concat(response,"Already removed ");
                    else
                        response = concat(response, "Removed successfully ");
                    sprintf(tmp, "id: %lu\n", (uint64_t) result->id);
                    response = concat(response, tmp);
                    result = result->prev;
                } while (result != NULL);
            } else
                response = concat(response, "--- NO RESULTS ---\n");
            break;
        case 2:
            err_code = add_input_item_new(f, tree.settings, tree.settings_count,
                                          tree.filters[0].comp_list[0].fv.int_val,
                                          pattern_size, pattern_types, pattern_names);
            switch (err_code) {
                case 1:
                    sprintf(tmp, "Field does not match pattern.\n");
                    response = concat(response, tmp);
                    break;
                case 2:
                    sprintf(tmp, "Not-bool value.\n");
                    response = concat(response, tmp);
                    break;
                case 3:
                    sprintf(tmp, "Not-float value.\n");
                    response = concat(response, tmp);
                    break;
                case 4:
                    sprintf(tmp, "Not-int value.\n");
                    response = concat(response, tmp);
                    break;
                case 5:
                    sprintf(tmp, "Not-str value.\n");
                    response = concat(response, tmp);
                    break;
                case 6:
                    sprintf(tmp, "Wrong number of parameters.\n");
                    response = concat(response, tmp);
                    break;
                default:
                    sprintf(tmp, "Added successfully.\n");
                    response = concat(response, tmp);
            }
            break;
        case 3:
            err_code = find_by_filters(f, tree.filters, tree.filters_count, &result, pattern_names);
            if (err_code == 3) {
                response = concat(response,"At least one of your fields doesn't exist.");
                break;
            }
            if (result != NULL) {
                response = concat(response,"--- UPDATE RESULT ---\n");
                do {
                    err_code = update_item(f, result->id, tree.settings, tree.settings_count, pattern_size,
                                           pattern_types, pattern_names);
                    if (err_code != 0) {
                        sprintf(tmp, "Error code: %zu\n", err_code);
                        response = concat(response, tmp);
                    }
                    sprintf(tmp, "Updated id: %lu\n", (uint64_t) result->id);
                    response = concat(response, tmp);
                    result = result->prev;
                } while (result != NULL);
            } else
                response = concat(response, "--- NO RESULTS ---\n");
            break;

    }

    *response_ = response;
    free_test_tree_header(header);
    free_test(pattern_names);
    free_test(pattern_types);
}
