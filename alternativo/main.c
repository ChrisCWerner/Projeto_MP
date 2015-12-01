//Main

#include "funcoes.h"
#include <conio.h>

int main(){
	
	FILE *fp = fopen("Arquivo2.txt", "r");
	
	Listas *inicio = NULL;
	int tempo = 0;
	
	srand(1);
	inicio = Le_Arquivo(fp);
	fclose(fp);
	
	inicio->p_record = Inicializa_Record();
	
	Localiza_Paths(inicio);
	
	puts("GO!!!");
	while(tempo < 25){
		if(getch() == 's')	break;
		Distribui_Recursos(inicio);
		
		printf("Segundo %d\n", tempo+1);
		Imprime(inicio);
		tempo++;
	}
	
	Relatorio(inicio);
	
	Limpa_Casa();
	
	printf("Pressione Enter para sair...");
	getchar();
	return 0;
}
