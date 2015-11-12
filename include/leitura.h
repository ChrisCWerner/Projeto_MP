//Arquivo de header para leitura de dados

#include <stdio.h>
#include <stdlib.h>

typedef struct Cidade{
	char *nome_cidade;
	int pos_x, pos_y;
	int recurso_necessario;
	struct Cidade *prox;
} cidade;

typedef struct Gerador{
	char *nome_gerador;
	int pos_x, pos_y;
	int recurso_produzido;
	int custo_gerador;
	struct Gerador *prox;
} gerador;

typedef struct Interc{
	char *nome_interc;
	int pos_inic_x, pos_inic_y;
	int pos_final_x, pos_final_y;
	int capacidade_max;
	float chance_falha;
	int tempo_conserto;
	int custo_conserto;
	struct Interc *prox;
} interc;

typedef struct Adaptador{
	char *nome_adaptador;
	int pos_x, pos_y;
	struct Adaptador *prox;
} adaptador;

typedef struct Listas{
	cidade *p_cidade;
	gerador *p_gerador;
	interc *p_interc;
	adaptador *p_adaptador;
} listas;





//Funcoes



listas *Le_Arquivo(FILE *fp);





