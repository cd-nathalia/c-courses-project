#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	printf("Welcome to our guessing game\n");

	int seconds = time(0);
	srand(seconds);

	int random_num = rand();

	int secret_number = random_num % 100;

	int guess;
	int tries = 1;

	double score = 1000;

	int right_guess = 0;

	int level;
	printf("Choose the difficulty level.\n");
	printf("(1) Easy | (2) Medium | (3) High\n");
	printf("Enter here: ");
	scanf("%d", &level);

	int number_of_tries;

	switch(level) {
	case 1:
		number_of_tries = 20;
		break;

	case 2:
		number_of_tries = 15;
		break;

	default:
		number_of_tries = 6;
		break;
	}

	for(int i = 1; i <= number_of_tries; i++) {
		printf("Number of tries: %d\n", tries);
		printf("Guess the number: ");

		scanf("%d", &guess);
		printf("Your guess was %d\n", guess);

		if(guess < 0) {
			printf("You can't guess negative numbers.\n");
			continue;
		}

		int right_guess = (guess == secret_number);
		int bigger = guess > secret_number;

		if(right_guess) {
			break;
		}

		else if(bigger) {
			printf("Your guess was bigger than the secret number.\n");
		}

		tries++;

		double lost_points = abs(guess - secret_number) / (double)2;
		score = score - lost_points;
	}

	printf("Endgame!\n");

	if(right_guess) {
		printf("You won the game!\n");
		printf("You guessed right in %d tries!\n", tries);
		printf("Total score: %.1f\n", score);
	}
	else {
		printf("You lost. Try agrain.\n");
	}

}
