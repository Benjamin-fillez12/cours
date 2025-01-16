#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "PyString.h"

char* _capitalize(char* s) {
	char* capMessage = s;
	char firstCharacter[1] = "l"; /* lettre aleatoire pour l'initialisation de la variable. */
	for (int i = 0; i < strlen(capMessage); i++) {
		if (iscntrl(capMessage[i]) || isspace(capMessage[i])) continue;
		firstCharacter[0] = capMessage[i];
		break;
	};
	strupr(firstCharacter);
	for (int i = 0; i < strlen(capMessage); i++) {
		if (iscntrl(capMessage[i]) || isspace(capMessage[i])) continue;
		capMessage[i] = firstCharacter[0];
		break;
	};
	return capMessage;
}

const bool _islower(char* s) {
	int allCharIsLwr = 0;
	int charLenNoSpace = 0;
	for (int i = 0; i < strlen(s); i++) {
		if (iscntrl(s[i]) || isspace(s[i])) continue;
		if (islower(s[i])) allCharIsLwr++;
		charLenNoSpace++;
	};
	if (allCharIsLwr == charLenNoSpace) return true;
	return false;
}

const bool _isUpper(char* s) {
	int allCharIsUppr = 0;
	int charLenNoSpace = 0;
	for (int i = 0; i < strlen(s); i++) {
		if (iscntrl(s[i]) || isspace(s[i])) continue;
		if (isupper(s[i])) allCharIsUppr++;
		charLenNoSpace++;
	};
	if (allCharIsUppr == charLenNoSpace) return true;
	return false;
}

char* _swapCase(char* s) {
	char* swap = s;
	for (int i = 0; i < strlen(s); i++) {
		if (islower(swap[i])) {
			swap[i] = toupper(swap[i]);
		}
		else if (isupper(swap[i])) {
			swap[i] = tolower(swap[i]);
		};
	};
	return swap;
}
