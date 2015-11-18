//Main

#include "funcoes.h"

int main(){
	
	FILE *fp = fopen("Arquivo2.txt", "r");
	
	Listas *inicio = NULL;
	
	inicio = Le_Arquivo(fp);
	fclose(fp);
	
	Localiza_Paths(inicio);
	Distribui_Recursos0(inicio);
	
	Imprime(inicio);
	
	inicio = Destroi(inicio);
	free(inicio);
	
	printf("Pressione Enter para sair...");
	getchar();
	return 0;
}
