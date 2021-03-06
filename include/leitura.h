//Arquivo de header para leitura de dados
/**
 * @author Roberta Renally, Renn� Ruan, Christian Werner
 * @date 8 dez 2015
 * @brief *
 *
 * Biblioteca principal para as func�es da rede de distribuicao de energia
 */


/** @file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct cidade{
	char nome_cidade[16];
	int pos_x, pos_y;
	int recurso_necessario;
	struct cidade *prox;
	
	int fluxo;		//Quantidade de rec. que chegam na cidade;
	int sem_rec;	//Verifica se a cidade ja esteve sem rec.
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
	int works;				//n� de interc. funcionando;
	int cheio;				//n� de interc. lotadas;
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
	int time_wrk;			//tempo para voltar a funcionar.
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
	int works;				//n� de interc. funcionando;
	int cheio;				//n� de interc. lotadas;
	struct interc *prim;	//interc. que saem do mesmo adaptador;
} Adapter;

typedef struct record{
	int numero_de_falhas;
	int tempo_de_falha;
	int custo_total;
	int tempo_total;
	int total_geradores;
	int total_cidades;
	int energia_total_geradores;
	int energia_gasta_cidades;
	float tamanho_interc;
	int cidades_sem_recurso;
	int tempo_cidades_sem_recurso;
	int cidades_sem_30porcento;
	int tempo_sem_30porcento;
} Record;

typedef struct listas{
	Cidade *p_cidade;
	Gerador *p_gerador;
	Interc *p_interc;
	Adapter *p_adapter;
	Record *p_record;
} Listas;

//Funcoes

/*********************************************************************//**
* @brief Nome da funcao: Inicializa;
* Descricao: Inicializa a estrutura que contem as listas de cada tipo de dado;
* @remark Par�metros: Nenhum
* @remark Interface Expl�cita: retorno Listas* sts
* @remark Interface Impl�cita: Nenhuma
* @remark Assertivas de Entrada: 
*			Nenhuma
* @remark Assertivas de Sa�da:
*			Listas criadas:
*			Listas->p_cidade = NULL;
*			Listas->p_gerador = NULL;
*			Listas->p_interc = NULL;
*			Listas->p_adapter = NULL;
*			Listas->p_record = NULL;
*************************************************************************************/
Listas *Inicializa(void);

/*********************************************************************//**
* @brief Nome da funcao: Le_Arquivo;
* Descricao: Le o arquivo de entrada e insere os tipos de informac�es nas respectivas listas.
* @remark Par�metros: FILE *fp
* @remark Interface Expl�cita: retorno Listas* sts;
* @remark Interface Impl�cita: Arquivo fp;
* @remark Assertivas de Entrada: 
*			FILE *fp != NULL (ponteiro para arquivo de entrada)
* @remark Assertivas de Sa�da:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
*************************************************************************************************************************************/
Listas *Le_Arquivo(FILE*);

/*********************************************************************//**
* @brief Nome da funcao: Insere_Lista;
* Descricao: Insere o tipo de informacao lida, a partir da funcao 'Le_arquivo', para o tipo correspondente das Listas.
* @remark Assertivas de Entrada: 
* @remark Par�metros: char tipo_elemento, Listas *top, void *elemento.
* @remark Interface Expl�cita: par�metros char tipo_elemento, Listas *top, void *elemento.
* @remark Interface Impl�cita: Nenhuma.
*			char tipo_elemento;
*			Listas (previamente alocada, podendo ou nao estarem vazias)
*			void *elemento (ponteiro para o elemento a ser inserido)
* @remark Assertivas de Sa�da:
*			nenhuma
*****************************************************************************************************************************/
void Insere_Lista(char, Listas*, void*);

/*********************************************************************//**
* @brief Nome da funcao: Imprime;
* Descricao: Imprime a estrutura que armazena cada tipo de lista, ou seja, vai imprimir cada uma das listas de cidades, geradores,
	     adaptadores e interconex�es.
* @remark Par�metros: Listas *inicio
* @remark Interface Expl�cita: par�metro Listas *inicio
* @remark Interface Impl�cita: Nenhuma.
* @remark Assertivas de Entrada:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
* @remark Assertivas de Sa�da:
*			nenhuma
***********************************************************************************************************************************/
void Imprime(Listas*);

/*********************************************************************//**
* @brief Nome da funcao: Destroi;
* @remark Descricao: Desaloca a posicao de mem�ria ocupada pelas listas.
* @remark Par�metros: Listas *inicio
* @remark Interface Expl�cita: par�metro Listas *inicio
* @remark Interface Impl�cita: Nenhuma.
* @remark Assertivas de Entrada:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
* @remark Assertivas de Sa�da:
*			Listas = NULL;
***********************************************************************************************************/
Listas *Destroi(Listas*);

