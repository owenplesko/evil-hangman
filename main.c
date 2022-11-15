#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include "generic_vector.h"
#include "word_family.h"
#include "ctype.h"

const int MAX_WORD_LEN = 29;

GENERIC_VECTOR* load_dictionary(void);
void free_dictionary(GENERIC_VECTOR* dictionary);
int prompt_word_len(GENERIC_VECTOR* dictionary);
Boolean prompt_show_words_remaining(void);
char prompt_char_guess(MY_STRING guessed_letters);
int prompt_num_guesses(void);
Boolean prompt_play_again(void);
void clear_keyboard_buffer(void);


int main(int argc, char *argv[])
{
	GENERIC_VECTOR* dictionary = load_dictionary();

	do {
		int wordLen = prompt_word_len(dictionary);
		int guesses = prompt_num_guesses();
		Boolean showWordsRemaining = prompt_show_words_remaining();

		MY_STRING guessed_letters = my_string_init_default();
		GENERIC_VECTOR largest_word_family = dictionary[wordLen];
		WORD_FAMILY word_families = word_family_init_vector(largest_word_family, guessed_letters);
		MY_STRING largest_word_family_key = word_family_get_largest_family_key(word_families);
		
		while(guesses > 0) {
			if(!my_string_contains_letter(largest_word_family_key, '-'))
				break;

			printf("Guesses Remaining: %d\n", guesses);
			printf("Letters Guessed: %s\n", my_string_c_str(guessed_letters));
			printf("Word Family: %s\n", my_string_c_str(largest_word_family_key));
			if(showWordsRemaining)
				printf("Possible Words Remaining: %d\n", generic_vector_get_size(largest_word_family));

			my_string_push_back(guessed_letters, prompt_char_guess(guessed_letters));

			WORD_FAMILY temp = word_family_init_vector(largest_word_family, guessed_letters);
			word_family_destroy(&word_families);
			word_families = temp;
			largest_word_family = word_family_get_largest_family(word_families);
			largest_word_family_key = word_family_get_largest_family_key(word_families);

			guesses--;
		}

		if(!my_string_contains_letter(largest_word_family_key, '-'))
			printf("Congratulations! You correctly guessed the word: %s\n", my_string_c_str(largest_word_family_key));
		else 
			printf("The correct word was: %s\n", my_string_c_str(*generic_vector_at(largest_word_family, 0)));
		
		my_string_destroy(&guessed_letters);
		word_family_destroy(&word_families);

	} while(prompt_play_again());

	for(int i = 0; i <= MAX_WORD_LEN; i++) 
		generic_vector_destroy(dictionary + i);
	free(dictionary);
	return 0;
}

GENERIC_VECTOR* load_dictionary() {
	FILE* fp = fopen("dictionary.txt", "r");
	GENERIC_VECTOR* dictionary = (GENERIC_VECTOR*) malloc(sizeof(GENERIC_VECTOR) * (MAX_WORD_LEN + 1));
	for(int i = 0; i < 30; i++)
		dictionary[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);
	MY_STRING my_string = my_string_init_default();
	while(my_string_extraction(my_string, fp)) {
		if(my_string_get_size(my_string) <= MAX_WORD_LEN)
			generic_vector_push_back(dictionary[my_string_get_size(my_string)], (Item) my_string);
	}
	my_string_destroy(&my_string);
	fclose(fp);
	return dictionary;
}

int prompt_word_len(GENERIC_VECTOR* dictionary) {
	int wordLen;
	do {
		printf("Word Length: ");
		scanf("%d", &wordLen);
		clear_keyboard_buffer();
	} while(wordLen <= 0 || wordLen > MAX_WORD_LEN || generic_vector_get_size(dictionary[wordLen]) <= 0);
	return wordLen;
}

int prompt_num_guesses(void) {
	int numGuesses;
	do {
		printf("Number Of Guesses: ");
		scanf("%d", &numGuesses);
		clear_keyboard_buffer();
	} while(numGuesses <= 0);
	return numGuesses;
}

Boolean prompt_show_words_remaining(void) {
	char c;
	do {
		printf("Show Remaining Words?: ");
		scanf("%c", &c);
		c = tolower(c);
		clear_keyboard_buffer();
	} while(c != 'y' && c != 'n');
	return c == 'y';
}

char prompt_char_guess(MY_STRING guessed_letters) {
	char c;
	do {
		printf("Guess A Letter: ");
		scanf("%c", &c);
		clear_keyboard_buffer();
		c = tolower(c);
	}  while(!isalpha(c) || my_string_contains_letter(guessed_letters, c));
	return c;
}

Boolean prompt_play_again(void) {
	char c;
	do {
		printf("Would you like to play again?: ");
		scanf("%c", &c);
		c = tolower(c);
		clear_keyboard_buffer();
	} while(c != 'y' && c != 'n');
	return c == 'y';
}

void clear_keyboard_buffer(void) {
    char c;
    do {
        scanf("%c", &c) ;
    } while (c != '\n' ) ;
}
