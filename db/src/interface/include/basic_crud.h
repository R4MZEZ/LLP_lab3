#ifndef BASIC_CRUD_H
#define BASIC_CRUD_H
#include "../../filetools/include/big_data_tools.h"
#include <unistd.h>
#include <string.h>


/**
 * Вставляет на позицию кортеж
 * @param file файл
 * @param pos_from откуда скопировать
 * @param pos_to куда скопировать
 * @return статус операции
 */
enum crud_operation_status swap_last_tuple_to(FILE *file, uint64_t pos_to, size_t tuple_size);

/**
 * Вставляет в конец файла новый кортеж
 * @param file файл
 * @param tuple кортеж
 * @param full_tuple_size размер одного кортежа вместе с заголовком
 * @return статус операции
 */
enum crud_operation_status insert_string_tuple(FILE *file, char *string, size_t tuple_size, uint64_t *str_pos);
enum crud_operation_status insert_new_tuple(FILE *file, struct tuple *tuple, size_t full_tuple_size, uint64_t *tuple_pos);
void get_types(FILE *file, uint32_t **types, size_t *size);
size_t append_to_id_array(FILE *file, uint64_t offset);
enum crud_operation_status remove_from_id_array(FILE *file, uint64_t id, uint64_t* offset);
enum crud_operation_status id_to_offset(FILE *file, uint64_t id, uint64_t* offset);
enum crud_operation_status offset_to_id(FILE *file, uint64_t* id, uint64_t offset);
enum crud_operation_status change_string_tuple(FILE *file, uint64_t offset, char *new_string,  uint64_t size);
enum crud_operation_status link_strings_to_tuple(FILE *file, struct tuple* tpl, uint64_t tpl_offset);
/**
 * Статус операции
 */
enum crud_operation_status {
    CRUD_OK = 0,
    CRUD_END_OF_FILE,
    CRUD_INVALID
};

#endif
