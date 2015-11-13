//Arquivo de header para leitura de dados

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cidade{
	char nome_cidade[16];
	int pos_x, pos_y;
	int recurso_necessario;
	struct cidade *prox;
} Cidade;

typedef struct gerador{
	char nome_gerador[16];
	int pos_x, pos_y;
	int recurso_produzido;
	int custo_gerador;
	struct gerador *prox;
} Gerador;

typedef struct interc{
	char nome_interc[16];
	int pos_inic_x, pos_inic_y;
	int pos_final_x, pos_final_y;
	int capacidade_max;
	float chance_falha;
	int tempo_conserto;
	int custo_conserto;
	struct interc *prox;
	
	void *vem;	//vem de ...
	char vemc;
	void *vai;	//vai para ...
	char vaic;
} Interc;

typedef struct adapter{
	char nome_adapter[16];
	int pos_x, pos_y;
	struct adapter *prox;
} Adapter;

typedef struct listas{
	cidade *p_cidade;
	gerador *p_gerador;
	interc *p_interc;
	adapter *p_adapter;
} Listas;



//Funcoes

Listas *Le_Arquivo(FILE *fp);

void Insere_Lista(char tipo_elemento, Listas *top, void *elemento);

void Imprime(Listas *inicio);

void Destroi(Listas *inicio);

