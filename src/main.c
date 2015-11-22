//Main

#include "funcoes.h"


void delay(){
 for ( int c = 1 ; c <= 25000 ; c++ )
       for (int d = 1 ; d <= 25000 ; d++ )
       {}
}
int main(){
	int opcao;
	char arquivo[20];
	int tempo, i = 0;
	printf("\e[1;1H\e[2J");
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
	Imprime(inicio);
	printf("\nModelo de simulação detalhada acima.\n");
	printf("\nDeseja realizar a simulação de forma detalhada ou apenas gerar o relatório?\n1- Detalhada\n2- Simples\n");
	scanf("%d",&opcao);	
	while(opcao != 1 && opcao !=2) {
		printf("\nDigite apenas 1 ou 2\n");
		scanf("%d",&opcao);
	}
	
	if(opcao == 1){
		for(; i<tempo; i++){
			printf("\033[2J\033[1;1H\n----------------------------SEGUNDO %d----------------------------", i+1);
			Distribui_Recursos(inicio);
			ReunirDados(inicio);
			if(i==0) getchar();
			Imprime(inicio);
			Interface_Grafica (inicio);
			delay();
	
		}
	}else{
		for(; i<tempo; i++){
			Distribui_Recursos(inicio);
			ReunirDados(inicio);
			Interface_Grafica (inicio);
		}
	}
	printf("\nSimulação terminada\n");
	
	printf("Pressione Enter para criar relatório dentro da pasta /src/");
	getchar();
	assert(fp);
	Relatorio(inicio,tempo);
	printf("\nRelatório criado com sucesso\n\n");

	inicio = Destroi(inicio);
	free(inicio);
	
	printf("Pressione Enter para visualizar gcov e gtest...");
	getchar();
	return 0;
}
