//Arquivo de header para funcoes principais

#include "leitura.h"

/************************************************************************************************************
* Nome da funcao: Inicializa_Record;
* Descricao: Inicializa a estrutura que ira armazenar os dados dos relatorios.
* Assertivas de Entrada:
*			nenhum
* Assertivas de Saida: 
*			Record *Registro != NULL (registro alocado na memoria)
*************************************************************************************************************/
Record *Inicializa_Record(void);

/**********************************************************************************************************
* Nome da funcao: Localiza_Paths;
* Descricao: Faz as ligacoes entre os Geradores e adapatadores e entre adapatadores e cidades,
*	atraves das interconexoes.
* Assertivas de entrada: 
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
* Assertivas de saida:
*			nenhum
************************************************************************************************************/
void Localiza_Paths(Listas *inicio);

/*******************************************************************************************************************
* Nome da funcao: Insere_Irmao;
* Descricao: Insere na lista de interconexao as outras interconexoes que saem do mesmo elemento.
* Assertivas de entrada:
*			Interc *novo_elem != NULL
*			Inetrc *top != NULL
* Assertivas de saida:
*			Interc *saida != NULL && Interc *saida = top;
********************************************************************************************************************/
Interc *Insere_Irmao(Interc *novo_elem, Interc *top);

/************************************************************************************************************************
* Nome da funcao: Calcula_Cap_Total;
* Descricao: Calcula a capacidade total que todas as interconexoes podem transportar;
* Assertivas de Entrada:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
* Assertivas de Saida:
*			int capacidade_total != 0;
*************************************************************************************************************************/
int Calcula_Cap_Total(Interc *inicio);

/************************************************************************************************************************
* Nome da funcao: Calcula_Cap_Total;
* Descricao: Calcula a capacidade relativa que cada interconexao pode transportar;
* Assertivas de Entrada:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
*			int total = Capacidade_total;
* Assertivas de Saida:
*			int capacidade_total != 0;
*************************************************************************************************************************/
int Calcula_Rel_Flow(Interc *inicio, int total);

/**************************************************************************************************************
* Nome da funcao: Calcula_Fluxo;
* Descricao: Calcula o fluxo de recursos nas interconexoes de um elemento e retorna a sobra total;
* Assertivas de entrada: 
*			void *inicio != NULL;
*			caracter identificador;
* Assertivas de saida:
*			int sobra;
*******************************************************************************************************************/
int Calcula_Fluxo(void *inicio, char id);

/**************************************************************************************************************
* Nome da funcao: Gerencia_Sobra;
* Descricao: Faz um gerenciamento da sobra de recursos tanto de adpatadores e geradores, para as interconexoes
*		que saem dele;
* Assertivas de entrada: 
*			void *inicio != NULL;
*			caracter identificador;
* Assertivas de saida:
*			nenhuma
*******************************************************************************************************************/
void Gerencia_Sobra(void *inicio, char id);

/**************************************************************************************************************
* Nome da funcao: Fluxo_Adpat;
* Descricao: calcula o fluxo de energia que chega ao adpatador;
* Assertivas de entrada: 
*			void *inicio != NULL;
* Assertivas de saida:
*			nenhum
*******************************************************************************************************************/
void Fluxo_Adapt(Interc *inicio);

/**************************************************************************************************************
* Nome da funcao: Fluxo_City;
* Descricao: Calcula o fluxo de recurso que chega nas cidades;
* Assertivas de entrada: 
*			Interc *inicio != NULL;
*			Record *Registro != NULL (Registro alocado)
* Assertivas de saida:
*			nenhuma
*******************************************************************************************************************/
void Fluxo_City(Interc *inicio, Record *rec);

/**************************************************************************************************************
* Nome da funcao: Verifica_Falhas
* Descricao: Verifica se houve falhas nas interconexoes
* Assertivas de entrada: 
*			Interc *inicio != NULL;
*			Record *Registro != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Verifica_Falhas(Interc *inicio, Record *rec);

/**************************************************************************************************************
* Nome da funcao: Maneja_Falhas
* Descricao: faz o gerenciamento das falhas nos geradores e adpatadores, modificando a variavel booleana,
*		para indicar falha;
* Assertivas de entrada: 
*			Interc *inicio != NULL;
*			incio->funciona = 1 (Se falhou);
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Maneja_Falhas(Interc *inicio);

/**************************************************************************************************************
* Nome da funcao: Zera_Fluxo
* Descricao: Zera o fluxo das interconexoes no inicio de cada ciclo (segundo);
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Zera_Fluxo(Listas *inicio);

/**************************************************************************************************************
* Nome da funcao: Distribui_Recursos;
* Descricao: Faz a distribuicao dos recursos dos geradores para os adaptadores, cidades atraves das interconexoes.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Distribui_Recursos(Listas *inicio);

/**************************************************************************************************************
* Nome da funcao: Examina_Cidades
* Descricao: Calcula o tempo em que a cidade esta sem recurso;
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Examina_Cidades(Listas *inicio);

/**************************************************************************************************************
* Nome da funcao: Total_Elementos
* Descricao: Calcula o total de cidades e geradores;
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Total_Elementos(Listas *inicio);

/**************************************************************************************************************
* Nome da funcao: Tamanho_Interc
* Descricao: Calcula o tamanho de todas as interconexoes juntas
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
float Tamanho_Interc(Interc *inicio);

/**************************************************************************************************************
* Nome da funcao: Relatorio
* Descricao: Grava no arquivo .txt o relatorio final com todos os dados solicitados pelo pdf do trabalho.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Relatorio(Listas *inicio);
