#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 256
#define MAX_WORD_LEN 16
#define MAX_WORDS_COUNT 128

#define TOO_LONG_STR 101
#define TOO_LONG_WORD 102

#define RIGHT_INPUT 0

char enter_string(char str[], size_t *str_len, size_t max_len)
{
	for (char symbol; (symbol = getchar()) != '\n' && symbol != EOF;)
	{
		if (*str_len < max_len - 1)
			str[(*str_len)++] = symbol;
		else
			return TOO_LONG_STR;
	}

	str[*str_len] = '\0';

	return RIGHT_INPUT;
}

void add_to_array(char words[][MAX_WORD_LEN + 1], char word[], size_t *words_count, size_t *word_len)
{
	word[*word_len] = '\0';
	strcpy(words[(*words_count)++], word);
	*word_len = 0;
}

char split(char str[], char words[][MAX_WORD_LEN + 1], size_t* words_count, size_t max_len, size_t max_count)
{
	char word[MAX_WORD_LEN + 1];
	size_t word_len = 0;

	for (; *str != '\0'; str++)
	{
		if (isalpha(*str))
		{
			if (word_len >= max_len)
				return TOO_LONG_WORD;

			word[word_len++] = *str;
		}

		else if (isspace(*str) || ispunct(*str))
		{
			if (word_len >= max_len)
				return TOO_LONG_WORD;

			if (word_len > 0)
				add_to_array(words, word, words_count, &word_len);
		}
	}

	if (word_len)
		add_to_array(words, word, words_count, &word_len);

	return RIGHT_INPUT;
}

void print_array(char words[][MAX_WORD_LEN + 1], size_t len)
{
	for (size_t i = 0; i < len; i++)
		printf("%s | ", words[i]);
	printf("counter = %zu\n", len);
}

size_t in_arrays
(
	char word[],
	char words1[][MAX_WORD_LEN + 1], size_t words_count1,
	char words2[][MAX_WORD_LEN + 1], size_t words_count2
)
{
	size_t counter = 0;

	for (size_t i = 0; i < words_count1; i++)
	{
		if (strcmp(words1[i], word) == 0)
			counter++;
	}

	for (size_t i = 0; i < words_count2; i++)
	{
		if (strcmp(words2[i], word) == 0)
			counter++;
	}

	return counter;
}

char get_keys
(
	size_t keys_array[],
	char words1[][MAX_WORD_LEN + 1], size_t words_count1,
	char words2[][MAX_WORD_LEN + 1], size_t words_count2
)
{
	for (size_t i = 0; i < words_count1; i++)
		keys_array[i] = in_arrays(words1[i], words1, words_count1, words2, words_count2);

	for (size_t i = 0; i < words_count2; i++)
		keys_array[i + words_count1] = in_arrays(words2[i], words1, words_count1, words2, words_count2);

	return EXIT_SUCCESS;
}

void print_words
(
	size_t keys_array[],
	char words1[][MAX_WORD_LEN + 1], size_t words_count1,
	char words2[][MAX_WORD_LEN + 1], size_t words_count2
)
{
	for (size_t i = 0; i < words_count1 + words_count2; i++)
	{
		if (i < words_count1 || keys_array[i] == 1)
			printf("%s\n", words1[i]);
		else if (i >= words_count1 || keys_array[i] == 1)
			printf("%s\n", words2[i - words_count1]);
	}
}

int main(void)
{
	char str1[MAX_STR_LEN], str2[MAX_STR_LEN];
	size_t len1 = 0, len2 = 0;

	printf("Enter first string: ");
	char check = enter_string(str1, &len1, MAX_STR_LEN);
	if (check != EXIT_SUCCESS)
		return check;

	printf("Enter second string: ");
	check = enter_string(str2, &len2, MAX_STR_LEN);
	if (check != EXIT_SUCCESS)
		return check;

	printf(">> %s\n>> %s\n", str1, str2);

	char words1[MAX_WORDS_COUNT][MAX_WORD_LEN + 1], words2[MAX_WORDS_COUNT][MAX_WORD_LEN + 1];
	size_t words_count1 = 0, words_count2 = 0;

	check = split(str1, words1, &words_count1, MAX_WORD_LEN, MAX_WORDS_COUNT);
	if (check != EXIT_SUCCESS)
		return check;

	check = split(str2, words2, &words_count2, MAX_WORD_LEN, MAX_WORDS_COUNT);
	if (check != EXIT_SUCCESS)
		return check;

	//print_array(words1, words_count1);
	//print_array(words2, words_count2);

	size_t keys_array[MAX_WORDS_COUNT * 2] = { 0 };
	check = get_keys(keys_array, words1, words_count1, words2, words_count2);
	if (check != EXIT_SUCCESS)
		return check;

	printf("[ ");
	for (size_t i = 0; i < words_count1 + words_count2; i++)
		printf("%d ", keys_array[i]);
	printf("]\n");

	print_words(keys_array, words1, words_count1, words2, words_count2);

	return EXIT_SUCCESS;
}