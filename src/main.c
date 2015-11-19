//Main

#include "funcoes.h"

int main(){
	
	FILE *fp = fopen("Arquivo.txt", "r");
	
	Listas *inicio = NULL;
	
	srand(1);
	
	inicio = Le_Arquivo(fp);
	fclose(fp);
	
	inicio->p_record = Inicializa_Record();
	
	Localiza_Paths(inicio);
	Distribui_Recursos(inicio);
	
	Imprime(inicio);
	Relatorio(inicio,inicio->p_record,20);
	getchar();


	inicio = Destroi(inicio);
	free(inicio);
	
	printf("Pressione Enter para sair...");
	getchar();
	return 0;
}
