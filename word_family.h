#ifndef WORD_FAMILY_H
#define WORD_FAMILY_H

#include "generic_vector.h"
#include "my_string.h"
#include "generic.h"

typedef void* WORD_FAMILY;

void word_family_get_word_key(MY_STRING* pKey, MY_STRING word, MY_STRING guessedLetters);

WORD_FAMILY word_family_init_vector(GENERIC_VECTOR pVector, MY_STRING guessed_letters);

GENERIC_VECTOR word_family_get_largest_family(WORD_FAMILY pWord_family);

MY_STRING word_family_get_largest_family_key(WORD_FAMILY pWord_family);

void word_family_destroy(WORD_FAMILY* pHWord_family);

#endif