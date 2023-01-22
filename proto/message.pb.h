/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.8-dev */

#ifndef PB_MESSAGE_PB_H_INCLUDED
#define PB_MESSAGE_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _Query_tree_Field_value_pair {
    char field[64];
    int32_t val_type;
    int64_t int_val;
    float real_val;
    char str_val[64];
} Query_tree_Field_value_pair;

typedef struct _Query_tree_Value_setting {
    Query_tree_Field_value_pair fv;
} Query_tree_Value_setting;

typedef struct _Query_tree_Comparator {
    int32_t operation;
    Query_tree_Field_value_pair fv;
} Query_tree_Comparator;

typedef struct _Query_tree_Filter {
    pb_size_t comp_list_count;
    Query_tree_Comparator comp_list[20];
} Query_tree_Filter;

typedef struct _Query_tree {
    int32_t command;
    pb_size_t filters_count;
    Query_tree_Filter filters[20];
    pb_size_t settings_count;
    Query_tree_Value_setting settings[20];
} Query_tree;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define Query_tree_init_default                  {0, 0, {Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default, Query_tree_Filter_init_default}, 0, {Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default, Query_tree_Value_setting_init_default}}
#define Query_tree_Filter_init_default           {0, {Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default, Query_tree_Comparator_init_default}}
#define Query_tree_Value_setting_init_default    {Query_tree_Field_value_pair_init_default}
#define Query_tree_Comparator_init_default       {0, Query_tree_Field_value_pair_init_default}
#define Query_tree_Field_value_pair_init_default {"", 0, 0, 0, ""}
#define Query_tree_init_zero                     {0, 0, {Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero, Query_tree_Filter_init_zero}, 0, {Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero, Query_tree_Value_setting_init_zero}}
#define Query_tree_Filter_init_zero              {0, {Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero, Query_tree_Comparator_init_zero}}
#define Query_tree_Value_setting_init_zero       {Query_tree_Field_value_pair_init_zero}
#define Query_tree_Comparator_init_zero          {0, Query_tree_Field_value_pair_init_zero}
#define Query_tree_Field_value_pair_init_zero    {"", 0, 0, 0, ""}

/* Field tags (for use in manual encoding/decoding) */
#define Query_tree_Field_value_pair_field_tag    1
#define Query_tree_Field_value_pair_val_type_tag 2
#define Query_tree_Field_value_pair_int_val_tag  3
#define Query_tree_Field_value_pair_real_val_tag 4
#define Query_tree_Field_value_pair_str_val_tag  5
#define Query_tree_Value_setting_fv_tag          1
#define Query_tree_Comparator_operation_tag      1
#define Query_tree_Comparator_fv_tag             2
#define Query_tree_Filter_comp_list_tag          1
#define Query_tree_command_tag                   1
#define Query_tree_filters_tag                   2
#define Query_tree_settings_tag                  3

/* Struct field encoding specification for nanopb */
#define Query_tree_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, INT32,    command,           1) \
X(a, STATIC,   REPEATED, MESSAGE,  filters,           2) \
X(a, STATIC,   REPEATED, MESSAGE,  settings,          3)
#define Query_tree_CALLBACK NULL
#define Query_tree_DEFAULT NULL
#define Query_tree_filters_MSGTYPE Query_tree_Filter
#define Query_tree_settings_MSGTYPE Query_tree_Value_setting

#define Query_tree_Filter_FIELDLIST(X, a) \
X(a, STATIC,   REPEATED, MESSAGE,  comp_list,         1)
#define Query_tree_Filter_CALLBACK NULL
#define Query_tree_Filter_DEFAULT NULL
#define Query_tree_Filter_comp_list_MSGTYPE Query_tree_Comparator

#define Query_tree_Value_setting_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, MESSAGE,  fv,                1)
#define Query_tree_Value_setting_CALLBACK NULL
#define Query_tree_Value_setting_DEFAULT NULL
#define Query_tree_Value_setting_fv_MSGTYPE Query_tree_Field_value_pair

#define Query_tree_Comparator_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, INT32,    operation,         1) \
X(a, STATIC,   REQUIRED, MESSAGE,  fv,                2)
#define Query_tree_Comparator_CALLBACK NULL
#define Query_tree_Comparator_DEFAULT NULL
#define Query_tree_Comparator_fv_MSGTYPE Query_tree_Field_value_pair

#define Query_tree_Field_value_pair_FIELDLIST(X, a) \
X(a, STATIC,   REQUIRED, STRING,   field,             1) \
X(a, STATIC,   REQUIRED, INT32,    val_type,          2) \
X(a, STATIC,   REQUIRED, INT64,    int_val,           3) \
X(a, STATIC,   REQUIRED, FLOAT,    real_val,          4) \
X(a, STATIC,   REQUIRED, STRING,   str_val,           5)
#define Query_tree_Field_value_pair_CALLBACK NULL
#define Query_tree_Field_value_pair_DEFAULT NULL

extern const pb_msgdesc_t Query_tree_msg;
extern const pb_msgdesc_t Query_tree_Filter_msg;
extern const pb_msgdesc_t Query_tree_Value_setting_msg;
extern const pb_msgdesc_t Query_tree_Comparator_msg;
extern const pb_msgdesc_t Query_tree_Field_value_pair_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define Query_tree_fields &Query_tree_msg
#define Query_tree_Filter_fields &Query_tree_Filter_msg
#define Query_tree_Value_setting_fields &Query_tree_Value_setting_msg
#define Query_tree_Comparator_fields &Query_tree_Comparator_msg
#define Query_tree_Field_value_pair_fields &Query_tree_Field_value_pair_msg

/* Maximum encoded size of messages (where known) */
#define Query_tree_Comparator_size               171
#define Query_tree_Field_value_pair_size         157
#define Query_tree_Filter_size                   3480
#define Query_tree_Value_setting_size            160
#define Query_tree_size                          72931

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
