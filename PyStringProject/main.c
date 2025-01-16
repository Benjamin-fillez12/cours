/*
	Insertion par défault nécessaire.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*
	Insertion du module PyString.c
*/
#include "PyString.h"

/*
	Point d'entré
*/
int main(void) {
	/* 
		Explication des types: 

		char* messageTopCap: est un pointeur (*) qui fait donc une chaine de charactere (ex: une phrase un mot etc)
		le type char sans pointeur permet simplement de mettre une seule lettre ex: ('d'), Note! ('') les virgules comme celle si sont obligatoires
		pour le type (char) uniquement
		
		phrase faite avec l'allocation de la mémoire.

		ex1: char message_aleatoire[TAILLE_DU_MESSAGE] = "Je suis un message aleatoire";
		ex2: char* message_aleatore = malloc(taille_du_message + 1);
	
		après le malloc il est toujours important de vérifié si l'allocation a marché.
	*/

	/*
		Transformation de la fonction (_capitalize(source)):

		messageToCap est une chaine dont la premiere lettre est minuscule
		transformMessage transforme "messageToCap" qui est maintenant devenue: "Salut ma premiere lettre vas etre en MAJ.
		la première lettre ce change en MAJ.
	*/
	char* messageToCap = "salut ma premiere lettre vas etre en MAJ.";
	char* transformMessage = _capitalize(messageToCap);	

	/* Affiche le message dans la console. */
	printf("%s\n", transformMessage);

	/*
		Vérification, (boolean):
		Si toute les mettres sont en MAJ et que il n'y pas de ponctuation cela renverra TRUE (vrai) sinon FALSE (faux)
	*/
	char* messageIsUpper = "MESSAGE EN MAJ";
	const bool isUpperData = _isUpper(messageIsUpper);

	/* Affiche le message dans la console. */
	printf("%s\n", isUpperData? "true" : "false");

	/*
		Vérification, (boolean):
		Si toute les mettres sont en MIN et que il n'y pas de ponctuation cela renverra TRUE (vrai) sinon FALSE (faux)
	*/
	char* messageIsLower = "premiere annee en ciel";
	const bool isLowerData = _islower(messageIsLower);

	/* Affiche le message dans la console. */
	printf("%s\n", isLowerData ? "true" : "false");

	/*
		Transformation :
		TransforSwapMessage, renverra les lettres en MIN en MAJ et les lettres en MAJ en MIN. 
		
		ex:
		
		char* source = "bonJOUR";
		char* new_source = _swapCase(source) -> "BONjour"
	*/
	char* messageSwap = "CHANgement du message.";
	char* transformSwapMessage = _swapCase(messageSwap);

	/* Affiche le message dans la console. */
	printf("%s\n", transformSwapMessage);

	return 0;
}
