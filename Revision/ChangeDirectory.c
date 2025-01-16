#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <errno.h>
#include <string.h>
#include <Windows.h>

/* Changement/Actuel espace de travail *//*
	ENOENT = "L'adresse n'a pas était trouvé";
	_getcwd = "Renvoie l'espace de travail actuel si la chaine n'est pas assez grande cela renvoie NULl";
	_chdir = "Changement l'espace de travail actuel par la nouvel adresse
	Un nouveau espace de travail ne peut se faire via [fgets,scanf] cela donnera une erreur a _chdir";
*/

int main(int argc, char** argv) {
	char cdir[1024];
	if (_getcwd(cdir, 1024) == NULL) {
		printf("Getting the current directory failed.\n");
		if (errno == ENOENT) printf("Path not found correctly\n");
		return 1;
	};
	char ndir[1024] = "C:\\test";
	if (_chdir(ndir) == -1) {
		printf("Making the new directory failed.\n");
		if (errno == ENOENT) printf("Path not found correctly\n");
		return 1;
	};
	return 0;
}
