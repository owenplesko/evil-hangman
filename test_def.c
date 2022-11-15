#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "unit_test.h"
#include "generic.h"

Status test_init_default_returns_nonNULL(char *buffer, int length)
{
    Item hString = NULL;

    hString = (Item) my_string_init_default();

    if (hString == NULL)
    {
        strncpy(buffer, "test_init_default_returns_nonNULL\n"
                        "my_string_init_default returns NULL",
                length);
        return FAILURE;
    }
    else
    {
        my_string_destroy(&hString);
        strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
        return SUCCESS;
    }
}

Status test_get_size_on_init_default_returns_0(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_default();

    if (my_string_get_size(hString) != 0)
    {
        status = FAILURE;
        printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
        strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
                        "Did not receive 0 from get_size after init_default\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
    }

    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_compare_works_with_no_alphanumeric_chars(char *buffer, int length)
{
    MY_STRING hRstring = NULL;
    MY_STRING hLstring = NULL;
    Status status = FAILURE;

    int test = 0;
    hRstring = my_string_init_c_string("^$% @");
    hLstring = my_string_init_c_string("^$% @? ");

    test = my_string_compare(hLstring, hRstring);

    if (test <= 0)
    {
        strncpy(buffer, "test_oplesko_compare_works_with_no_alphanumeric_chars\nmy_string_compare returned incorrect value", length);
        status = FAILURE;
    }
    else
    {
        strncpy(buffer, "test_oplesko_compare_works_with_no_alphanumeric_chars\n", length);
        status = SUCCESS;
    }

    my_string_destroy(&hRstring);
    my_string_destroy(&hLstring);
    return status;
}

Status test_oplesko_get_capacity_on_init_default_returns_7(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_default();

    if (my_string_get_capacity(hString) != 7)
    {
        status = FAILURE;
        printf("Expected a capacity of 7 but got %d\n", my_string_get_size(hString));

        strncpy(buffer, "test_oplesko_get_capacity_on_init_default_returns_7\nDid not receive 7 from my_string_get_capacity after init_default\n", length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_oplesko_get_capacity_on_init_default_returns_7\n", length);
    }

    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_my_string_c_str_keeps_same_size(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;
    hString = my_string_init_c_string("TestString");
    my_string_c_str(hString);
    if (my_string_get_size(hString) != 10)
    {
        strncpy(buffer, "test_oplesko_my_string_c_str_keeps_same_size\n"
                        "my_string_c_string altered the size of string for some reason",
                length);
        status = FAILURE;
    }
    else
    {
        strncpy(buffer, "test_oplesko_my_string_c_str_keeps_same_size\n", length);
        status = SUCCESS;
    }

    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_destroy_makes_handle_NULL(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;

    int *t;
    hString = my_string_init_c_string("TestString");
    my_string_destroy(&hString);

    t = (int *)hString;

    if (t != NULL)
    {
        strncpy(buffer, "test_oplesko_destroy_makes_handle_NULL\n"
                        "my_string_destroy does not return NULL",
                length);
        status = FAILURE;
    }
    else
    {
        strncpy(buffer, "test_oplesko_destroy_makes_handle_NULL\n", length);
        status = SUCCESS;
    }

    return status;
}

Status test_oplesko_init_c_string_returns_nonNULL(char *buffer, int length)
{
    MY_STRING hString = NULL;

    hString = my_string_init_c_string("TestString");

    if (hString == NULL)
    {
        strncpy(buffer,
                "test_oplesko_init_c_string_returns_nonNULL\n"
                "my_string_init_c_string returns NULL",
                length);
        return FAILURE;
    }

    else
    {
        my_string_destroy(&hString);
        strncpy(buffer, "test_oplesko_init_c_string_returns_nonNULL\n", length);
        return SUCCESS;
    }
}

Status test_oplesko_pop_back_lowers_size(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_c_string("TestString");
    my_string_pop_back(hString);

    if (my_string_get_size(hString) != 9)
    {
        strncpy(buffer, "test_oplesko_my_string_pop_back_lowers_size\n"
                        "my_string_pop_back did not reduce the size of hString",
                length);
        status = FAILURE;
    }
    else
    {
        strncpy(buffer,
                "test_oplesko_my_string_pop_back_lowers_size\n", length);
        status = SUCCESS;
    }

    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_pop_back_returns_success_on_nonempty_string(char *buffer, int length)
{

    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_c_string("TestString");

    if (my_string_pop_back(hString))
    {

        status = SUCCESS;
        strncpy(buffer, "test_oplesko_pop_back_returns_success_on_nonempty_string\n", length);
    }
    else
    {

        status = FAILURE;
        strncpy(buffer, "test_oplesko_pop_back_returns_success_on_nonempty_string\n"
                        "my_string_pop_back returned failure\n",
                length);
    }

    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_empty_returns_true_on_an_empty_string(char *buffer, int length)
{

    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_default();

    if (my_string_empty(hString))
    {

        status = SUCCESS;
        strncpy(buffer, "test_oplesko_empty_returns_true_on_an_empty_string\n", length);
    }
    else
    {

        status = FAILURE;
        strncpy(buffer, "test_oplesko_empty_returns_true_on_an_empty_string\n"
                        "my_string_empty returned false\n",
                length);
    }

    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_my_string_empty_true_on_string_popped_back(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_c_string("Test");

    my_string_pop_back(hString); // T
    my_string_pop_back(hString); // e
    my_string_pop_back(hString); // s
    my_string_pop_back(hString); // t

    if (!my_string_empty(hString))
    {
        strncpy(buffer,
                "test_oplesko_my_string_empty_true_on_string_popped_back\n"
                "my_string_empty did not work when hString is popped empty",
                length);
        status = FAILURE;
    }
    else
    {
        strncpy(buffer,
                "test_oplesko_my_string_empty_true_on_string_popped_back\n", length);
        status = SUCCESS;
    }

    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_my_string_c_str_return_address_of_data(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status = SUCCESS;

    char *t;
    int i;
    char test_string[10] = "TestString";

    hString = my_string_init_c_string(test_string);
    t = my_string_c_str(hString);

    for (i = 0; i < 10; i++, t++)
    {
        if (*t != test_string[i])
        {
            status = FAILURE;
        }
    }

    if (status == FAILURE)
    {
        strncpy(buffer,
                "test_oplesko_my_string_c_str_return_address_of_data\n"
                "Address returned by my_string_c_str did not align.",
                length);
    }
    else
    {
        strncpy(buffer,
                "test_oplesko_my_string_c_str_return_address_of_data\n", length);
    }

    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_my_string_concat_adjusts_size_correctly(char *buffer, int length)
{
    MY_STRING hString1 = NULL;
    MY_STRING hString2 = NULL;
    Status status;

    hString1 = my_string_init_c_string("TestString");
    hString2 = my_string_init_c_string("Working");

    my_string_concat(hString1, hString2);

    if (my_string_get_size(hString1) != 17)
    {
        strncpy(buffer, "test_oplesko_my_string_concat_adjusts_size_correctly\n"
                        "my_string_concat did not properly adjust size",
                length);
        status = FAILURE;
    }
    else
    {
        strncpy(buffer,
                "test_oplesko_my_string_concat_adjusts_size_correctly\n", length);
        status = SUCCESS;
    }

    my_string_destroy(&hString1);
    my_string_destroy(&hString2);
    return status;
}

Status test_oplesko_compare_returns_0_if_same(char *buffer, int length)
{
    MY_STRING hLString = NULL;
    MY_STRING hRString = NULL;
    Status status;

    hLString = my_string_init_c_string("OhMyWord");
    hRString = my_string_init_c_string("OhMyWord");

    if (my_string_compare(hLString, hRString) == 0)
    {
        status = SUCCESS;
        strncpy(buffer, "test_oplesko_compare_returns_0_if_same\n", length);
    }
    else
    {
        status = FAILURE;
        strncpy(buffer, "test_oplesko_compare_returns_0_if_same\n"
                        "my_string_compare returned a value greater or less than 0\n",
                length);
    }
    my_string_destroy(&hLString);
    my_string_destroy(&hRString);
    return status;
}

Status test_oplesko_compare_returns_greater_than_0_when_left_bigger(char *buffer, int length)
{

    MY_STRING hLString = NULL;
    MY_STRING hRString = NULL;
    Status status;

    hLString = my_string_init_c_string("absolutelywow");
    hRString = my_string_init_c_string("absolutely");

    if (my_string_compare(hLString, hRString) > 0)
    {

        status = SUCCESS;
        strncpy(buffer, "test_oplesko_compare_returns_greater_than_0_when_left_bigger\n", length);
    }
    else
    {

        status = FAILURE;
        strncpy(buffer, "test_oplesko_compare_returns_greater_than_0_when_left_bigger\n"
                        "my_string_compare returned a value less than or equal to zero\n",
                length);
    }

    my_string_destroy(&hLString);
    my_string_destroy(&hRString);
    return status;
}

Status test_oplesko_compare_returns_less_than_0_when_left_smaller(char *buffer, int length)
{

    MY_STRING hLString = NULL;
    MY_STRING hRString = NULL;
    Status status;

    hLString = my_string_init_c_string("Test");
    hRString = my_string_init_c_string("Testing");

    if (my_string_compare(hLString, hRString) < 0)
    {

        status = SUCCESS;
        strncpy(buffer, "test_oplesko_compare_returns_less_than_0_when_left_smaller\n", length);
    }
    else
    {

        status = FAILURE;
        strncpy(buffer, "test_oplesko_compare_returns_less_than_0_when_left_smaller\n"
                        "my_string_compare returned a value greater than or equal to zero\n",
                length);
    }

    my_string_destroy(&hLString);
    my_string_destroy(&hRString);
    return status;
}

Status test_oplesko_my_string_at_returns_right_address(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status = SUCCESS;

    char test_string[10] = "TestString";
    int i = 0;

    hString = my_string_init_c_string(test_string);

    for (i = 0; i < 10; i++)
    {
        if (*my_string_at(hString, i) != test_string[i])
        {
            status = FAILURE;
        }
    }

    if (status == FAILURE)
    {
        strncpy(buffer,
                "test_oplesko_my_string_at_returns_right_address\n"
                "Address returned by my_string_at was not the correct address.",
                length);
    }
    else
    {
        strncpy(buffer,
                "test_oplesko_my_string_at_returns_right_address\n", length);
    }

    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_extraction_returns_right_size(char *buffer, int length)
{

    MY_STRING hString = NULL;
    Status status;
    FILE *fp;

    hString = my_string_init_default();

    fp = fopen("testfile.txt", "w");
    fprintf(fp, "  TestString Working  ");
    fclose(fp);

    fp = fopen("testfile.txt", "r");

    my_string_extraction(hString, fp);
    if (my_string_get_size(hString) != 10)
    {
        strncpy(buffer,
                "test_oplesko_extraction_returns_right_size\n"
                "my_string_extraction set incorrect size or included spaces.",
                length);
        status = FAILURE;
    }
    else
    {
        strncpy(buffer,
                "test_oplesko_extraction_returns_right_size\n", length);
        status = SUCCESS;
    }

    fclose(fp);
    remove("testfile.txt");
    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_extraction_captures_properly_from_file(char *buffer, int length)
{

    MY_STRING hString = NULL;
    char* test_string = "TestString";
    Status status = SUCCESS;

    FILE *fp;
    int i = 0;

    hString = my_string_init_default();

    fp = fopen("testfile.txt", "w");
    fprintf(fp, "  TestString Working  ");
    fclose(fp);

    fp = fopen("testfile.txt", "r");
    my_string_extraction(hString, fp);
    fclose(fp);

    for (i = 0; i < 10; i++)
    {
        if (*my_string_at(hString, i) != test_string[i])
            status = FAILURE;
    }

    if (status == FAILURE)
    {
        strncpy(buffer,
                "test_oplesko_extraction_captures_properly_from_file\n"
                "my_string_extraction did not copy properly from file.",
                length);
        status = FAILURE;
    }
    else
    {
        strncpy(buffer,
                "test_oplesko_extraction_captures_properly_from_file\n", length);
        status = SUCCESS;
    }

    remove("testfile.txt");
    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_insertion_properly_prints_c_string(char *buffer, int length)
{
    MY_STRING hString = NULL;
    char test_string[10] = "TestString";
    Status status = SUCCESS;

    int i = 0;
    FILE *fp;

    hString = my_string_init_c_string(test_string);

    fp = fopen("testfile.txt", "w");
    my_string_insertion(hString, fp);
    fclose(fp);

    fp = fopen("testfile.txt", "r");

    for (i = 0; i < 10; i++)
    {
        if (fgetc(fp) != test_string[i])
        {
            status = FAILURE;
        }
    }

    if (status == FAILURE)
    {
        strncpy(buffer,
                "test_oplesko_insertion_properly_prints_c_string\n"
                "my_string_insertion did not copy properly",
                length);
        status = FAILURE;
    }
    else
    {
        strncpy(buffer,
                "test_oplesko_insertion_properly_prints_c_string\n", length);
        status = SUCCESS;
    }

    fclose(fp);
    remove("testfile.txt");
    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_concat_returns_success(char *buffer, int length)
{

    MY_STRING hLString = NULL;
    MY_STRING hRString = NULL;
    Status status = SUCCESS;

    hLString = my_string_init_c_string("concat");
    hRString = my_string_init_c_string("worked");

    if (my_string_concat(hLString, hRString))
    {
        status = SUCCESS;
        strncpy(buffer, "test_oplesko_concat_returns_success\n", length);
    }
    else
    {
        status = FAILURE;
        strncpy(buffer, "test_oplesko_concat_returns_success\n"
                        "my_string_concat did not return success.\n",
                length);
    }

    my_string_destroy(&hLString);
    my_string_destroy(&hRString);
    return status;
}

Status test_oplesko_concat_returns_success_when_one_string_empty(char *buffer, int length)
{
    MY_STRING hLString = NULL;
    MY_STRING hRString = NULL;
    Status status;

    hLString = my_string_init_c_string("concatting");
    hRString = my_string_init_default();

    if (my_string_concat(hLString, hRString))
    {
        status = SUCCESS;
        strncpy(buffer, "test_oplesko_concat_returns_success_when_one_string_empty\n", length);
    }
    else
    {
        status = FAILURE;
        strncpy(buffer, "test_oplesko_concat_returns_success_when_one_string_empty\n"
                        "my_string_concat return success with empty string.\n",
                length);
    }

    my_string_destroy(&hLString);
    my_string_destroy(&hRString);
    return status;
}

Status test_oplesko_concat_allocated_more_memory(char *buffer, int length)
{
    MY_STRING hLString = NULL;
    MY_STRING hRString = NULL;
    Status status;

    hLString = my_string_init_c_string("concat");
    hRString = my_string_init_c_string("worked");
    int capacity = my_string_get_capacity(hLString);
    my_string_concat(hLString, hRString);

    if (capacity < my_string_get_size(hLString))
    {
        status = SUCCESS;
        strncpy(buffer, "test_oplesko_concat_allocated_more_memory\n", length);
    }
    else
    {
        status = FAILURE;
        strncpy(buffer, "test_oplesko_concat_allocated_more_memory\n"
                        "my_string_concat does not allocate additional memory.\n",
                length);
    }

    my_string_destroy(&hLString);
    my_string_destroy(&hRString);
    return status;
}

Status test_oplesko_push_back_allocates_more_memory(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_c_string("TestString");
    status = my_string_push_back(hString, ' ');

    if (status == SUCCESS)
        strncpy(buffer, "test_oplesko_push_back_allocates_more_memory\n", length);
    else
    {
        status = FAILURE;
        strncpy(buffer, "test_oplesko_push_back_allocates_more_memory\n"
                        "my_string_push_back does not allocate additional memory.\n",
                length);
    }

    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_empty_returned_false_on_nonempty_string(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_c_string("TestString");

    if (!my_string_empty(hString))
    {
        status = SUCCESS;
        strncpy(buffer, "test_oplesko_empty_returned_false_on_nonempty_string\n", length);
    }
    else
    {
        status = FAILURE;
        strncpy(buffer, "test_oplesko_empty_returned_false_on_nonempty_string\n"
                        "my_string_empty returned true.\n",
                length);
    }

    my_string_destroy(&hString);
    return status;
}

Status test_oplesko_my_string_assignment_copies_properly(char *buffer, int length) {
    int arrayLen = 100;
    Boolean printStrings = FALSE;
    MY_STRING* stringArray = (MY_STRING*) malloc(sizeof(MY_STRING) * arrayLen);
    stringArray[0] = my_string_init_c_string("COPY ME!");
    for(int i = 1; i < arrayLen; i++)
        stringArray[i] = NULL;
    for(int i = 1; i < arrayLen; i++)
        my_string_assignment(&stringArray[i], stringArray[0]);
    for(int i = 0; i < arrayLen; i++) {
        if(printStrings)
            my_string_insertion(stringArray[i], stdout);
        my_string_destroy(&stringArray[i]);
    }
    free(stringArray);
    strncpy(buffer, "test_oplesko_my_string_assignment_copies_properly\n", length);
    return SUCCESS;
}
