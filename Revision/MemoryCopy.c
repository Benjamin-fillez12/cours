#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Copie de la memoire /* 
	memmove() et memcpy() sont identique mais sont utilisé différemment car memmove() possède le problème du "Overlaped"
	ce problème apparait quand la destination est la même mais pas au même index (voir: move_memory() callback);
	memcpy() n'a dont pas ce problème enfin il existe mais n'est pas trouvable durant l'évenement.
	A noté que memcpy est plus perfomant que memmove donc il est préférable de utiliser memcpy() que memmove() en cas unique il faut utilisé
	memmove() pour plus de sécurité.
	-/ Paramètres /-
	@memmove(void *destination,const void *source,size_t size)
	@memcpy(void *destination,const void *source,size_t size)
*/

static void copy_memory(int s[10], int d[10], size_t size) {
	memcpy(d, s, size);
}

static void move_memory(int s[10], int d[10], size_t size) {
	memmove(d, s, size);
}

int main(int argc,char** argv) {
	int IntSource[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int IntDestination[10];
	//move_memory(IntSource + 2, IntSource, sizeof(int) * (sizeof(IntSource) / sizeof(IntSource)));
	copy_memory(IntSource, IntDestination, sizeof(int) * 10);
	for (int i = 0; i < sizeof(IntSource) / sizeof(IntSource[0]); i++) printf("Dest[%d]=%d\n",i, IntDestination[i]);
	return 0;
}
