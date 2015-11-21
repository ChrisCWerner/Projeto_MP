//Main

#include "funcoes.h"

int main(){
	char arquivo[20];
	int tempo, i = 0, espera = 0;

	printf("\033[2J\033[1;1H");

	printf("Digite o nome do arquivo a ser analisado (incluir .txt): ");
	scanf("%[^\n]", arquivo);
	getchar();

	printf("Digite o tempo da simulação:");
	scanf("%d", &tempo);

	FILE *fp = fopen(arquivo, "r");
	
	Listas *inicio = NULL;
	
	srand(1);
	
	inicio = Le_Arquivo(fp);
	fclose(fp);
	
	inicio->p_record = Inicializa_Record();
	Localiza_Paths(inicio);
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

	inicio = Destroi(inicio);
	free(inicio);
	getchar();
	printf("Pressione Enter para sair...");
	getchar();
	return 0;
}

