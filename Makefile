CC = gcc
CFLAGS = -Wall --std=c99
HANGMAN_OBJECTS = main.o my_string.o generic_vector.o word_family.o
TEST_OBJECTS = unit_test.o test_def.o my_string.o
KEY_TEST_OBJECTS = my_string.o word_family.o key_tester.o generic_vector.o

evil_hangman: $(HANGMAN_OBJECTS)
	$(CC) $(CFLAGS) -o evil_hangman $(HANGMAN_OBJECTS)
unit_test: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(TEST_OBJECTS)
key_tester: $(KEY_TEST_OBJECTS)
	$(CC) $(CFLAGS) -o key_tester $(KEY_TEST_OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
unit_test.o: unit_test.c
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o
my_string.o: my_string.c
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
generic_vector.o: generic_vector.c
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o
word_family.o: word_family.c
	$(CC) $(CFLAGS) -c word_family.c -o word_family.o

clean:
	rm evil_hangman unit_test key_tester $(HANGMAN_OBJECTS) $(TEST_OBJECTS) $(KEY_TEST_OBJECTS)
