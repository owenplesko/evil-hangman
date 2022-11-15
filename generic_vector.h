#ifndef GENERIC_VECTOR_H
#define GENERIC_VECTOR_H
#include "generic.h"

typedef void* GENERIC_VECTOR;

//init
GENERIC_VECTOR generic_vector_init_default(
	Status(*Item_assignment)(Item* phLeft, Item hRight),
	void (*Item_destroy)(Item* phItem)
	);


Status generic_vector_push_back(GENERIC_VECTOR hVector, Item hItem);

Status generic_vector_pop_back(GENERIC_VECTOR hVector);
//at
Item* generic_vector_at(GENERIC_VECTOR hVector, int index);

Boolean generic_vector_is_empty(GENERIC_VECTOR hVector);


int generic_vector_get_size(GENERIC_VECTOR hVector);
int generic_vector_get_capacity(GENERIC_VECTOR hVector);

//destroy
void generic_vector_destroy(GENERIC_VECTOR* phVector);

#endif
