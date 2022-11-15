#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "my_string.h"

Status test_init_default_returns_nonNULL(char *error_message, int max_message_len);

Status test_get_size_on_init_default_returns_0(char *error_message, int max_message_len);

Status test_oplesko_compare_works_with_no_alphanumeric_chars(char *error_message, int max_message_len);

Status test_oplesko_get_capacity_on_init_default_returns_7(char *error_message, int max_message_len);

Status test_oplesko_my_string_c_str_keeps_same_size(char *error_message, int max_message_len);

Status test_oplesko_destroy_makes_handle_NULL(char *error_message, int max_message_len);

Status test_oplesko_init_c_string_returns_nonNULL(char *error_message, int max_message_len);

Status test_oplesko_pop_back_lowers_size(char *error_message, int max_message_len);

Status test_oplesko_pop_back_returns_success_on_nonempty_string(char *error_message, int max_message_len);

Status test_oplesko_empty_returns_true_on_an_empty_string(char *error_message, int max_message_len);

Status test_oplesko_my_string_empty_true_on_string_popped_back(char *error_message, int max_message_len);

Status test_oplesko_my_string_c_str_return_address_of_data(char *error_message, int max_message_len);

Status test_oplesko_my_string_concat_adjusts_size_correctly(char *error_message, int max_message_len);

Status test_oplesko_compare_returns_0_if_same(char *error_message, int max_message_len);

Status test_oplesko_compare_returns_greater_than_0_when_left_bigger(char *error_message, int max_message_len);

Status test_oplesko_compare_returns_less_than_0_when_left_smaller(char *error_message, int max_message_len);

Status test_oplesko_my_string_at_returns_right_address(char *error_message, int max_message_len);

Status test_oplesko_extraction_returns_right_size(char *error_message, int max_message_len);

Status test_oplesko_extraction_captures_properly_from_file(char *error_message, int max_message_len);

Status test_oplesko_insertion_properly_prints_c_string(char *error_message, int max_message_len);

Status test_oplesko_insertion_properly_prints_c_string(char *error_message, int max_message_len);

Status test_oplesko_concat_returns_success_when_one_string_empty(char *error_message, int max_message_len);

Status test_oplesko_concat_allocated_more_memory(char *error_message, int max_message_len);

Status test_oplesko_push_back_allocates_more_memory(char *error_message, int max_message_len);

Status test_oplesko_empty_returned_false_on_nonempty_string(char *error_message, int max_message_len);

Status test_oplesko_my_string_assignment_copies_properly(char *buffer, int length);

#endif