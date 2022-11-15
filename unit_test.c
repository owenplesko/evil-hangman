#include <stdio.h>
#include "unit_test.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    Status (*tests[])(char *, int) = {
        test_init_default_returns_nonNULL,
        test_get_size_on_init_default_returns_0,
        test_oplesko_compare_works_with_no_alphanumeric_chars,
        test_oplesko_get_capacity_on_init_default_returns_7,
        test_oplesko_my_string_c_str_keeps_same_size,
        test_oplesko_destroy_makes_handle_NULL,
        test_oplesko_init_c_string_returns_nonNULL,
        test_oplesko_pop_back_lowers_size,
        test_oplesko_pop_back_returns_success_on_nonempty_string,
        test_oplesko_empty_returns_true_on_an_empty_string,
        test_oplesko_my_string_empty_true_on_string_popped_back,
        test_oplesko_my_string_c_str_return_address_of_data,
        test_oplesko_my_string_concat_adjusts_size_correctly,
        test_oplesko_compare_returns_0_if_same,
        test_oplesko_compare_returns_greater_than_0_when_left_bigger,
        test_oplesko_compare_returns_less_than_0_when_left_smaller,
        test_oplesko_my_string_at_returns_right_address,
        test_oplesko_extraction_returns_right_size,
        test_oplesko_extraction_captures_properly_from_file,
        test_oplesko_insertion_properly_prints_c_string,
        test_oplesko_insertion_properly_prints_c_string,
        test_oplesko_concat_returns_success_when_one_string_empty,
        test_oplesko_concat_allocated_more_memory,
        test_oplesko_push_back_allocates_more_memory,
        test_oplesko_empty_returned_false_on_nonempty_string,
        test_oplesko_my_string_assignment_copies_properly
        };

    int num_test_functions = sizeof(tests) / sizeof(tests[0]);
    int max_message_len = 500;
    char *message = (char *)malloc(sizeof(char) * max_message_len);
    int success_count = 0;
    int fail_count = 0;

    for (int i = 0; i < num_test_functions; i++)
    {
        if ((tests[i])(message, max_message_len) == FAILURE)
        {
            printf("%d\n", i);
            fail_count++;
            printf("FAIL: Test %d failed!\n", i);
            printf("%s\n", message);
        }
        else
        {
            success_count++;
            printf("PASS: Test %d passed!\n", i);
            printf("%s\n", message);
        }
    }
    free(message);

    printf("--------------------\n");
    printf("%d tests ran.\n", num_test_functions);
    printf("%d tests passed and %d tests failed.\n", success_count, fail_count);

    return 0;
}