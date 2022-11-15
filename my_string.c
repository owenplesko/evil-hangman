#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct my_string;
typedef struct my_string My_string;
struct my_string
{
	int size;
	int capacity;
	char *data;
};

MY_STRING my_string_init_default(void)
{
	My_string *my_string = (My_string *)malloc(sizeof(My_string));
	if (my_string == NULL)
		return NULL;

	my_string->capacity = 7;
	my_string->size = 0;
	my_string->data = (char *)malloc(sizeof(char) * my_string->capacity);
	if (my_string->data == NULL)
	{
		free(my_string);
		return NULL;
	}

	return my_string;
}

MY_STRING my_string_init_c_string(char *c_string)
{
	// find length of given string
	int strLen;
	for (strLen = 0; c_string[strLen] != '\0'; strLen++)
		;

	// init MY_STRING
	My_string *my_string = (My_string *)malloc(sizeof(My_string));
	my_string->capacity = strLen + 1;
	my_string->size = strLen;
	my_string->data = (char *)malloc(sizeof(char) * (my_string->capacity));

	// fill MY_STRING with string data
	for (int i = 0; i <= strLen; i++)
		my_string->data[i] = c_string[i];

	return my_string;
}

void my_string_destroy(Item *pItem)
{
	My_string *my_string = (My_string *)*pItem;

	if (my_string == NULL)
		return;

	free(my_string->data);
	free(my_string);
	*pItem = NULL;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
	My_string *my_string = (My_string *)hMy_string;
	return my_string->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
	My_string *my_string = (My_string *)hMy_string;
	return my_string->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_string *left_string = (My_string *)hLeft_string;
	My_string *right_string = (My_string *)hRight_string;

	if (left_string->size < right_string->size)
		return -1;
	if (right_string->size < left_string->size)
		return 1;
	
	for (int i = 0; i < left_string->size; i++)
	{
		if (left_string->data[i] < right_string->data[i])
			return -1;
		if (right_string->data[i] < left_string->data[i])
			return 1;
	}

	return 0;
}

Status my_string_extraction(MY_STRING hMy_string, FILE *fp)
{
	My_string *my_string = (My_string *)hMy_string;
	if (fp == NULL)
		return FAILURE;

	// pass over whitespace
	char c = fgetc(fp);
	while (isspace(c))
		c = fgetc(fp);
	if (feof(fp))
		return FAILURE;

	// find len of string in file
	int strLen = 0;
	while (!isspace(c) && !feof(fp))
	{
		strLen++;
		c = fgetc(fp);
	}

	// move file pointer back to beginning of string in file
	if (feof(fp))
		fseek(fp, -strLen, SEEK_CUR);
	else
		fseek(fp, -strLen - 1, SEEK_CUR);

	// resize my_string for new string
	my_string->size = strLen;
	my_string->capacity = strLen + 1;
	my_string->data = realloc(my_string->data, sizeof(char) * (my_string->capacity));
	if (my_string->data == NULL)
		return FAILURE;

	// copy chars from file to my_string
	for (int i = 0; i < my_string->size; i++)
		my_string->data[i] = fgetc(fp);
	my_string->data[strLen] = '\0';

	return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE *fp)
{
	My_string *my_string = (My_string *)hMy_string;
	char *c_str = my_string_c_str(my_string);
	if (c_str == NULL)
		return FAILURE;

	fprintf(fp, "%s\n", c_str);
	return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
	My_string *my_string = (My_string *)hMy_string;

	// resize my_string if needed
	if (my_string->size >= my_string->capacity)
	{
		char *resizedCharPtr = realloc(my_string->data, sizeof(char) * (my_string->capacity + 1));

		if (resizedCharPtr == NULL)
			return FAILURE;

		my_string->data = resizedCharPtr;
		my_string->capacity++;
	}

	// add char to end of data and update size
	my_string->data[my_string->size] = item;
	my_string->size++;

	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
	My_string *my_string = (My_string *)hMy_string;
	if (my_string->size == 0)
		return FAILURE;

	my_string->size--;
	return SUCCESS;
}

char *my_string_at(MY_STRING hMy_string, int index)
{
	My_string *my_string = (My_string *)hMy_string;
	if (index < 0 || index >= my_string->size)
		return NULL;

	return my_string->data + index;
}

char *my_string_c_str(MY_STRING hMy_string)
{
	My_string *my_string = (My_string *)hMy_string;
	if (my_string == NULL)
		return NULL;

	if (my_string_push_back(my_string, '\0') == FAILURE)
		return NULL;
	my_string->size--;

	return my_string->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	My_string *result_string = (My_string *)hResult;
	My_string *append_string = (My_string *)hAppend;

	// resize if neccesary
	if (result_string->capacity < result_string->size + append_string->size)
	{
		char *strPtr = realloc(result_string->data, sizeof(char) * (result_string->size + append_string->size));

		if (strPtr == NULL)
			return FAILURE;

		result_string->data = strPtr;
	}

	// add contents from hAppend to hResult
	for (int i = 0; i < append_string->size; i++)
		result_string->data[result_string->size + i] = append_string->data[i];
	result_string->size += append_string->size;

	return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
	My_string *my_string = (My_string *)hMy_string;
	return my_string->size == 0;
}

Status my_string_assignment(Item* pLeft, Item pRight) {
	My_string *leftString, *rightString;
	rightString = (My_string*) pRight;
	if(*pLeft == NULL)
		*pLeft = my_string_init_default();
	leftString = (My_string*) (*pLeft);
	leftString->data = realloc(leftString->data, sizeof(char) * rightString->capacity);
	for(int i = 0; i < rightString->size; i++)
		leftString->data[i] = rightString->data[i];
	leftString->size = rightString->size;
	return SUCCESS;
}

Boolean my_string_contains_letter(MY_STRING hMy_string, char c) {
	My_string* string = (My_string*) hMy_string;
	for(int i = 0; i < string->size; i++) {
		if(string->data[i] == c)
			return TRUE;
	}
	return FALSE;
}
