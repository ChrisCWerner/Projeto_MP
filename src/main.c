//Main

#include "funcoes.h"

int main(){
	
	FILE *fp = fopen("Arquivo.txt", "r");
	
	Listas *inicio = NULL;
	
	inicio = Le_Arquivo(fp);
	fclose(fp);
	
	Localiza_Paths(inicio);
	
	Imprime(inicio);
	
	Destroi(inicio);
	
	getchar();
	return 0;
}
