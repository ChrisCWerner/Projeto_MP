//Arquivo de header para leitura de dados

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cidade{
	char nome_cidade[16];
	int pos_x, pos_y;
	int recurso_necessario;
	struct cidade *prox;
	
	int fluxo;		//Quantidade de rec. que chegam na cidade;
} Cidade;

typedef struct gerador{
	char nome_gerador[16];
	int pos_x, pos_y;
	int recurso_produzido;
	int custo_gerador;
	struct gerador *prox;
	
	int saida;				//quantidade de interc. que saem do gerador;
	int sobra;				//quantidade de rec. que sobra;
	int total;				//total de rec. que as interc. podem transportar;
	int works;				//n° de interc. funcionando;
	int cheio;				//n° de interc. lotadas;
	struct interc *prim;	//interc. que saem do mesmo gerador;
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
	
	int fluxo;				//quantidade de recursos que passa pela interc.
	float rel_flow;			//fluxo relativo da interc.
	int funciona;			//variavel booleana.
	struct interc *irmao;	//interc. que saem do mesmo lugar.
} Interc;

typedef struct adapter{
	char nome_adapter[16];
	int pos_x, pos_y;
	struct adapter *prox;
	
	int fluxo;				//quantidade de recursos que passa pelo adaptador;
	int saida;				//quantidade de interc. que saem do adaptador;
	int total;				//total de rec. que as interc. podem transportar;
	int sobra;				//quantidade de rec. que sobra;
	int works;				//n° de interc. funcionando;
	int cheio;				//n° de interc. lotadas;
	struct interc *prim;	//interc. que saem do mesmo adaptador;
} Adapter;

typedef struct listas{
	Cidade *p_cidade;
	Gerador *p_gerador;
	Interc *p_interc;
	Adapter *p_adapter;
} Listas;



//Funcoes

Listas *Inicializa(void);

Listas *Le_Arquivo(FILE*);

void Insere_Lista(char, Listas*, void*);

void Imprime(Listas*);

Listas *Destroi(Listas*);

