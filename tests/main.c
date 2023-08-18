#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
	char *words[] = {"Estou em $HOME", "Outra $VAR", "Texto simples"};
	int num_words = sizeof(words) / sizeof(words[0]);

	for (int i = 0; i < num_words; i++) {
		char *word = words[i];
		char new_word[100] = ""; // Initialize new_word as an empty string
		int j = 0;
		int m = 0;

		while (word[j] != '\0') {
			if (word[j] == '$') {
				// Find the end of the variable name
				int start = j + 1;
				int end = start;
				while (word[end] != '\0' && (isalnum(word[end]) || word[end] == '_')) {
					end++;
				}

				// Extract the variable name
				char var_name[end - start + 1];
				strncpy(var_name, word + start, end - start);
				var_name[end - start] = '\0';

				// Get the environment variable value
				char *var_value = getenv(var_name);
				if (var_value != NULL) {
					strcat(new_word, var_value);
					m += strlen(var_value);
				}

				j = end; // Move j to the end of the variable name
			} else {
				new_word[m] = word[j];
				m++;
				j++;
			}
		}

		new_word[m] = '\0';
		printf("Original: '%s'\n", word);
		printf("Modified: '%s'\n", new_word);
	}

	return 0;
}
