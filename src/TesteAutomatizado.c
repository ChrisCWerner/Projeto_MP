#include "funcoes.h"
#include "gtest/gtest.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

Listas *sts = NULL;
Listas *inicio = NULL;
Cidade *cidade = NULL;
Gerador *gerador = NULL;
Interc *interc = NULL;
Adapter *adaptador = NULL;

TEST(Alocando_as_Estruturas, Inicializa){

	sts = Inicializa ();
	ASSERT_EQ(NULL, sts->p_cidade);
	ASSERT_EQ(NULL, sts->p_gerador);
	ASSERT_EQ(NULL, sts->p_interc);
	ASSERT_EQ(NULL, sts->p_adapter);
}

TEST(Alocando_a_Estrutura_que_armazena_informacoes_para_o_relatorio, Inicializa2){
	sts->p_record = Inicializa_Record();
	ASSERT_EQ(0, sts->p_record->numero_de_falhas);
	ASSERT_EQ(0, sts->p_record->tempo_de_falha);
	ASSERT_EQ(0, sts->p_record->custo_total);
	ASSERT_EQ(0, sts->p_record->tempo_total);
	ASSERT_EQ(0, sts->p_record->total_geradores);
	ASSERT_EQ(0, sts->p_record->total_cidades);
	ASSERT_EQ(0, sts->p_record->energia_total_geradores);
	ASSERT_EQ(0, sts->p_record->energia_gasta_cidades);
	ASSERT_EQ(0, sts->p_record->tamanho_interc);
	ASSERT_EQ(0, sts->p_record->cidades_sem_recurso);
	ASSERT_EQ(0, sts->p_record->tempo_cidades_sem_recurso);
	ASSERT_EQ(0, sts->p_record->cidades_sem_30porcento);
	ASSERT_EQ(0, sts->p_record->tempo_sem_30porcento);
}
TEST(Inseri_na_Lista_Cidade, Cidade){
	cidade = (Cidade *) malloc(sizeof(Cidade));
	strcpy(cidade->nome_cidade, "A_City");
	cidade->pos_x = 20;
	cidade->pos_y = 15;
	cidade->recurso_necessario = 100;
	Insere_Lista('C', sts, cidade);
	EXPECT_STREQ("A_City", sts->p_cidade->nome_cidade);
	EXPECT_EQ(20, sts->p_cidade->pos_x);
	EXPECT_EQ(15,sts->p_cidade->pos_y);
}

TEST(Inseri_na_Lista_Gerador, Gerador){
	gerador = (Gerador *) malloc(sizeof(Gerador));
	strcpy(gerador->nome_gerador, "A_Gen");
	gerador->pos_x = 7;
	gerador->pos_y = 48;
	gerador->recurso_produzido = 110;
	gerador->custo_gerador = 1000;
	Insere_Lista('G', sts, gerador);
	EXPECT_STREQ("A_Gen", sts->p_gerador->nome_gerador);
	EXPECT_EQ(07, sts->p_gerador->pos_x);
	EXPECT_EQ(48, sts->p_gerador->pos_y);
	EXPECT_EQ(110, sts->p_gerador->recurso_produzido);
	EXPECT_EQ(1000, sts->p_gerador->custo_gerador);
}

TEST(Inseri_na_Lista_Interconexao, Interconexao){
	interc = (Interc *) malloc(sizeof(Interc));
	strcpy(interc->nome_interc, "A_Path");
	interc->pos_inic_x = 07;
	interc->pos_inic_y = 48;
	interc->pos_final_x = 21;
	interc->pos_final_y = 40;
	interc->capacidade_max = 140;
	interc->chance_falha = 0.1;
	interc->tempo_conserto = 14;
	interc->custo_conserto = 20;
	Insere_Lista('I', sts, interc);
	EXPECT_STREQ("A_Path", sts->p_interc->nome_interc);
	EXPECT_EQ(07,  sts->p_interc->pos_inic_x);
	EXPECT_EQ(48,  sts->p_interc->pos_inic_y);
	EXPECT_EQ(21,  sts->p_interc->pos_final_x);
	EXPECT_EQ(40, sts->p_interc->pos_final_y);
	EXPECT_EQ(140, sts->p_interc->capacidade_max);
	EXPECT_EQ(0.1*10, 10*sts->p_interc->chance_falha);
	EXPECT_EQ(14,  sts->p_interc->tempo_conserto);
	EXPECT_EQ(20,  sts->p_interc->custo_conserto);
}

TEST(Inseri_na_Lista_Adaptador, Adaptador){
	adaptador = (Adapter *) malloc(sizeof(Adapter));
	strcpy(adaptador->nome_adapter, "A_dapt");
	adaptador->pos_x = 21;
	adaptador->pos_y = 40;
	Insere_Lista('A', sts, adaptador);
	EXPECT_STREQ("A_dapt", sts->p_adapter->nome_adapter);
	EXPECT_EQ(21,  sts->p_adapter->pos_x);
	EXPECT_EQ(40,  sts->p_adapter->pos_y);
}


TEST(Destroi_Listas1, Destruir1){
	sts = Destroi(sts);
	EXPECT_EQ(NULL, sts->p_cidade);
	EXPECT_EQ(NULL, sts->p_gerador);
	EXPECT_EQ(NULL, sts->p_interc);
	EXPECT_EQ(NULL, sts->p_adapter);
}

TEST(Leitura_do_arquivo_de_entrada, Leitura){
	FILE *fp = fopen("Arquivo.txt", "r");
	int i;
	ASSERT_EQ(NULL, inicio);
	inicio = Le_Arquivo(fp);
	fclose(fp);
	inicio->p_record = Inicializa_Record();
	ASSERT_EQ(0, inicio->p_record->numero_de_falhas);
	ASSERT_EQ(0, inicio->p_record->tempo_de_falha);
	ASSERT_EQ(0, inicio->p_record->custo_total);
	ASSERT_EQ(0, inicio->p_record->tempo_total);
	ASSERT_EQ(0, inicio->p_record->total_geradores);
	ASSERT_EQ(0, inicio->p_record->total_cidades);
	ASSERT_EQ(0, inicio->p_record->energia_total_geradores);
	ASSERT_EQ(0, inicio->p_record->energia_gasta_cidades);
	ASSERT_EQ(0, inicio->p_record->tamanho_interc);
	ASSERT_EQ(0, inicio->p_record->cidades_sem_recurso);
	ASSERT_EQ(0, inicio->p_record->tempo_cidades_sem_recurso);
	ASSERT_EQ(0, inicio->p_record->cidades_sem_30porcento);
	ASSERT_EQ(0, inicio->p_record->tempo_sem_30porcento);	
}

TEST(Destroi_Listas2, Destruir2){
	inicio = Destroi(inicio);
	EXPECT_EQ(NULL, inicio->p_cidade);
	EXPECT_EQ(NULL, inicio->p_gerador);
	EXPECT_EQ(NULL, inicio->p_interc);
	EXPECT_EQ(NULL, inicio->p_adapter);
	EXPECT_EQ(NULL, inicio->p_record);
}
void delay(){
 for ( int c = 1 ; c <= 25000 ; c++ )
       for (int d = 1 ; d <= 25000 ; d++ )
       {}
}
int main(int argc, char **argv){
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
			if(i==0) getchar();
			Imprime(inicio);
			delay();
	
		}
	}else{
		for(; i<tempo; i++){
			Distribui_Recursos(inicio);
		}
	}
	printf("\nSimulação terminada\n");
	
	printf("Pressione Enter para criar relatório dentro da pasta /src/");
	getchar();
	assert(fp);
	Relatorio(inicio);
	printf("\nRelatório criado com sucesso\n\n");

	inicio = Destroi(inicio);
	free(inicio);
	
	printf("Pressione Enter para visualizar gcov e gtest...");
	getchar();

        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
