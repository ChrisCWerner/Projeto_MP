//Main

#include "funcoes.h"
#include <conio.h>

int main(){
<<<<<<< HEAD
	
	FILE *fp = fopen("Arquivo2.txt", "r");
=======
	char arquivo[20];
	int tempo, i = 0, espera = 0;

	printf("\033[2J\033[1;1H");

	printf("Digite o nome do arquivo a ser analisado (incluir .txt): ");
	scanf("%[^\n]", arquivo);
	getchar();

	printf("Digite o tempo da simulação:");
	scanf("%d", &tempo);

	FILE *fp = fopen(arquivo, "r");
>>>>>>> 1ce8b8b859635be87e9ce2745a780ebe52161a03
	
	Listas *inicio = NULL;
	int tempo = 0;
	
	srand(1);
	
	inicio = Le_Arquivo(fp);
	fclose(fp);
	
	inicio->p_record = Inicializa_Record();
	Localiza_Paths(inicio);
<<<<<<< HEAD
	
	puts("GO!!!");
	while(tempo < 3){
//		getchar();
		if(getch() == 's')	break;
		Distribui_Recursos(inicio);
		
		Imprime(inicio);
		tempo++;
	}
	
	
=======
	for(; i<tempo; i++){
		printf("\033[2J\033[1;1H");
		Distribui_Recursos(inicio, i);
		Imprime(inicio);
	do{
		        espera++;
	}while(espera <150000000);
	espera = 0;
	Interface_Grafica (inicio);
	}
	Relatorio(inicio,inicio->p_record,tempo);

>>>>>>> 1ce8b8b859635be87e9ce2745a780ebe52161a03
	inicio = Destroi(inicio);
	free(inicio);
	getchar();
	printf("Pressione Enter para sair...");
	getchar();
	return 0;
}

