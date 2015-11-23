//Arquivo de header para funcoes principais

#include "leitura.h"

/************************************************************************************************************
* Nome da função: Inicializa_Record;
* Descrição: Inicializa a estrutura que irá armazenar os dados dos relatórios.
* Assertivas de Entrada: nenhuma
* Assertivas de Saída: 
*			Record *Registro != NULL (registro alocado na memória)
*************************************************************************************************************/
Record *Inicializa_Record(void);

/**********************************************************************************************************
* Nome da função: Localiza_Paths;
* Descrição: Faz as ligações entre os Geradores e adapatadores e entre adapatadores e cidades,
*	através das interconexões.
* Assertivas de entrada: 
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
* Assertivas de saída:
*			nenhum
************************************************************************************************************/
void Localiza_Paths(Listas *inicio);

/*******************************************************************************************************************
* Nome da função: Insere_Irmão;
* Descrição: Insere na lista de interconexão as outras interconexões que saem do mesmo adaptador.
* Assertivas de entrada:
*			Interc *novo_elem != NULL
*			Inetrc *top != NULL
* Assertivas de saída:
*			Interc *saida != NULL && Interc *saida = top;
********************************************************************************************************************/
Interc *Insere_Irmao(Interc *novo_elem, Interc *top);

/************************************************************************************************************************
* Nome da função: Calcula_Cap_Total;
* Descrição: Calcula a capacidade total que todas as interconexões podem transportar;
* Assertivas de Entrada:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
* Assertivas de Saída:
*			int capacidade_total != 0;
*************************************************************************************************************************/
int Calcula_Cap_Total(Interc *inicio);

/************************************************************************************************************************
* Nome da função: Calcula_Cap_Total;
* Descrição: Calcula a capacidade relativa que cada interconexão podem transportar;
* Assertivas de Entrada:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
*			int total = Capacidade_total;
* Assertivas de Saída:
*			int capacidade_total != 0;
*************************************************************************************************************************/
int Calcula_Rel_Flow(Interc *inicio, int total);

/**************************************************************************************************************
* Nome da função: Calcula_Fluxo;
* Descrição: Calcula a sobre de recurso nos adapatadores;
* Assertivas de entrada: 
*			void *inicio != NULL;
*			caracter identificador;
* Assertivas de saida:
*			int sobra;
*******************************************************************************************************************/
int Calcula_Fluxo(void *inicio, char id);

/**************************************************************************************************************
* Nome da função: Gerencia_Sobra;
* Descrição: Faz um gerenciamento da sobre de recursos tanto de adpatadores e geradores, para as interconexões
*		que saem dele;
* Assertivas de entrada: 
*			void *inicio != NULL;
*			caracter identificador;
* Assertivas de saida:
*			nenhuma
*******************************************************************************************************************/
void Gerencia_Sobra(void *inicio, char id);

/**************************************************************************************************************
* Nome da função:Fluxo_Adpat;
* Descrição: calcula o fluxo de energia que chega ao adpatador;
* Assertivas de entrada: 
*			void *inicio != NULL;
* Assertivas de saida:
*			nenhum
*******************************************************************************************************************/
void Fluxo_Adapt(Interc *inicio);

/**************************************************************************************************************
* Nome da função: Fluxo_City;
* Descrição: Calcula o fluxo de recurso que chega nas cidades;
* Assertivas de entrada: 
*			Interc *inicio != NULL;
*			Record *Registro != NULL (Registro alocado)
* Assertivas de saida:
*			nenhuma
*******************************************************************************************************************/
void Fluxo_City(Interc *inicio, Record *rec);

/**************************************************************************************************************
* Nome da função: Verifica_Falhas
* Descrição: Verifica se houve falhas nas interconexões
* Assertivas de entrada: 
*			Interc *inicio != NULL;
*			Record *Registro != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Verifica_Falhas(Interc *inicio, Record *rec);

/**************************************************************************************************************
* Nome da função: Maneja_Falhas
* Descrição: faz o gerenciamento das falhas nos geradores e adpatadores, modificando a variável booleana,
*		para indicar falha;
* Assertivas de entrada: 
*			Interc *inicio != NULL;
*			incio->funciona = 1 (Se falhou);
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Maneja_Falhas(Interc *inicio);

/**************************************************************************************************************
* Nome da função: Zera_Fluxo
* Descrição: Zera o fluxo das interconexões
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Zera_Fluxo(Listas *inicio);

/**************************************************************************************************************
* Nome da função: Distribui_Recursos;
* Descrição: Faz a distribuição dos recursos dos geradores para os adaptadores, cidades através das interconexões.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Distribui_Recursos(Listas *inicio);

/**************************************************************************************************************
* Nome da função: Examina_Cidades
* Descrição: Calcula o tempo em que a cidade está sem recurso;
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Examina_Cidades(Listas *inicio);

/**************************************************************************************************************
* Nome da função: Total_Elementos
* Descrição: Calcula o total de cidades e geradores
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Total_Elementos(Listas *inicio);

/**************************************************************************************************************
* Nome da função: Tamanho_Interc
* Descrição: Calcula o tamanho de todas as interconexões juntas
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
float Tamanho_Interc(Interc *inicio);

/**************************************************************************************************************
* Nome da função: Relatorio
* Descrição: Grava no arquivo .txt o relatório final com todos so dados solicitados pelo podf do trabalho
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Relatorio(Listas *inicio);

//void Interface_Grafica(Listas* inicio);
