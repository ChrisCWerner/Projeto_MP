//Main

#include "leitura.h"

int main(){
	
	FILE *fp = fopen("Arquivo.txt", "r");
	
	Listas *inicio = NULL;
	
	inicio = Le_Arquivo(fp);
	fclose(fp);
	
	Imprime(inicio);
	
	Destroi(inicio);
	
	getchar();
	return 0;
}
