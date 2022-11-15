#include "word_family.h"
#include "my_string.h"
#include <stdio.h>

#define NUM_TEST_WORDS 4

int main(int argc, char **argv)
{
    MY_STRING testWords[NUM_TEST_WORDS];
    testWords[0] = my_string_init_c_string("the");
    testWords[1] = my_string_init_c_string("truck");
    testWords[2] = my_string_init_c_string("happy");
    testWords[3] = my_string_init_c_string("awesome");

    MY_STRING testGuesses[NUM_TEST_WORDS];
    testGuesses[0] = my_string_init_c_string("t");
    testGuesses[1] = my_string_init_c_string("r");
    testGuesses[2] = my_string_init_c_string("hpy");
    testGuesses[3] = my_string_init_c_string("e");

    MY_STRING key = NULL;

    for (int i = 0; i < NUM_TEST_WORDS; i++)
    {
        word_family_get_word_key(&key, testWords[i], testGuesses[i]);
        printf("Word: %s Guessed Letters: %s Key: %s\n",
               my_string_c_str(testWords[i]),
               my_string_c_str(testGuesses[i]),
               my_string_c_str(key));
        my_string_destroy(testWords + i);
        my_string_destroy(testGuesses + i);
    }

    my_string_destroy(&key);
    return 0;
}
