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
	while(tempo < 3){
//		getchar();
		if(getch() == 's')	break;
		Distribui_Recursos(inicio);
		
		Imprime(inicio);
		tempo++;
	}
	
	
	inicio = Destroi(inicio);
	free(inicio);
	
	printf("Pressione Enter para sair...");
	getchar();
	return 0;
}
