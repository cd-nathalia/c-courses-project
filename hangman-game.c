#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hangman.h"

char secret_word[WORD_LENGHT];
int guesses[26];
int tries = 0;

void guess() {
	char guess;
	printf("Which letter? ");
	scaf(" %c", &guess);

	guesses[tries] = guess;
	tries++;
}

int guessed_letter(char letter) {
	int letter_found = 0;
	for(int j = 0; j < tries; j++) {
		if(guesses[j] == letter) {
			letter_found = 1;
			break;
		}
	}
	return letter_found;
}

void draw_hangman() {
	printf("You guessed %d times\n", tries);
	for(int i = 0; i < strlen(secret_word); i++) {
		if(guessed_letter(secret_word[i])) {
			printf("%c ", secret_word[i]);
		} else {
			printf("_ ");
		}
	}
	printf("\n")
}

void choose_word() {
	FILE* f;
	f = fopen("palavras.txt", "r");
	if(f == 0) {
		printf("Dataset unavailable.");
		exit(1);
	}
	int words_quantity;
	fscanf(f, "%d", &words_quantity);

	srand(time(0));
	int random = rand() % words_quantity;

	for(int i = 0; i <= random; i++) {
		fscanf(f, "%s", secret_word);
	}
	fclose(f);
}

void add_word() {
	char add_word;

	printf("Do you want to add a new word to the game? Y/N");
	scanf(" %c", &add_word);

	if(add_word == "Y") {
		char new_word[WORD_LENGHT];

		printf("Enter the new word in capslock: ");
		scanf("%s", new_word);

		f = fopen("palavras.txt", "r+");
		if(f == 0) {
			printf("Dataset unavailable.");
			exit(1);
		}

		int quantity;
		fscanf(f, "%d", &quantity);
		quantity++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "\n%s", new_word);

		fclose(f);
	}
}

int letter_exists(char letter) {
	for(int j = 0; j < strlen(secret_word); j++) {
		if(letter == secret_word[j]) {
			return 1;
		}
	}
	return 0;
}

int mistakes() {
	int mistakes = 0;

	for(int i = 0; i < tries; i++) {
		if(!letter_exists(guesses[i])) {
			mistakes++;
		}
	}
	return mistakes;
}

int hanged() {
	return mistakes() >= 5;
}

int guessed_right() {
	for(int i = 0; i < strlen(secret_word); i++) {
		if(!guessed_letter(secret_word[i])) {
			return 0;
		}
	}
	return 1;
}

int main() {

	choose_word();

	do {

		draw_hangman();
		guess();

	} while(!guessed_right() && !hanged());

	if(guessed_right()) {
		printf("Congratulations! You won.");
	} else {
		printf("You were hanged. Try again.");
	}

	add_word();
}
