//Arquivo de header para funcoes principais

#include "leitura.h"
#include <SDL/SDL.h>
/************************************************************************************************************
* Nome da função: Inicializa_Record;
* Descrição: Inicializa a estrutura que irá armazenar os dados dos relatórios.
* Parâmetros: Nenhum
* Interface Explícita: retorno Record *rec
* Interface Implícita: Nenhuma.
* Assertivas de Entrada: nenhuma
* Assertivas de Saída: 
*			Record *Registro != NULL (registro alocado na memória)
*************************************************************************************************************/
Record *Inicializa_Record(void);

/**********************************************************************************************************
* Nome da função: Localiza_Paths;
* Descrição: Faz as ligações entre os Geradores e adapatadores e entre adapatadores e cidades,
*	através das interconexões.
* Parâmetros: Listas *inicio
* Interface Explícita: parâmetro Listas *inicio
* Interface Implícita: Nenhuma.
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
* Parâmetros: Interc *novo_elem, Interc *top
* Interface Explícita: parâmetros Interc *novo_elem, Interc *top, retorno top.
* Interface Implícita: Nenhuma.
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
* Parâmetros: Interc *inicio
* Interface Explícita: parâmetros Interc *inicio
* Interface Implícita: Nenhuma.
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
* Nome da função: Calcula_Rel_Flow;
* Descrição: Calcula o fluxo de energia nas interconexões;
* Parâmetros: Interc *inicio, int total
* Interface Explícita: parâmetros Interc *inicio, int total, retorno int i.
* Interface Implícita: Nenhuma.
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
* Parâmetros: void *inicio, char id
* Interface Explícita: parâmetros void *inicio, char id, retorno sombra.
* Interface Implícita: Nenhuma.
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
* Parâmetros: void *inicio, char id
* Interface Explícita: parâmetros void *inicio, char id, retorno sombra.
* Interface Implícita: Nenhuma.
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
* Parâmetros: Interc *inicio
* Interface Explícita: parâmetros Interc *inicio 
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			void *inicio != NULL;
* Assertivas de saida:
*			nenhum
*******************************************************************************************************************/
void Fluxo_Adapt(Interc *inicio);

/**************************************************************************************************************
* Nome da função: Fluxo_City;
* Descrição: Calcula o fluxo de recurso que chega nas cidades;
* Parâmetros: Interc *inicio, Record *rec
* Interface Explícita: parâmetros Interc *inicio, Record *rec
* Interface Implícita: Nenhuma.
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
* Parâmetros: Interc *inicio
* Interface Explícita: parâmetros Interc *inicio
* Interface Implícita: Nenhuma.
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
* Parâmetros: Interc *inicio
* Interface Explícita: parâmetros Interc *inicio
* Interface Implícita: Nenhuma.
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
* Parâmetros: Listas *inicio
* Interface Explícita: parâmetros Listas *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Zera_Fluxo(Listas *inicio);

/**************************************************************************************************************
* Nome da função: Distribui_Recursos;
* Descrição: Faz a distribuição dos recursos dos geradores para os adaptadores, cidades através das interconexões.
* Parâmetros: Listas *inicio
* Interface Explícita: parâmetros Listas *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Distribui_Recursos(Listas *inicio);

/**************************************************************************************************************
* Nome da função: Examina_Cidades
* Descrição: Calcula o tempo em que a cidade está sem recurso;
* Parâmetros: Listas *inicio
* Interface Explícita: parâmetros Listas *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Examina_Cidades(Listas *inicio);

/**************************************************************************************************************
* Nome da função: Total_Elementos
* Descrição: Calcula o total de cidades e geradores
* Parâmetros: Interc *inicio
* Interface Explícita: parâmetros Interc *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Total_Elementos(Listas *inicio);

/**************************************************************************************************************
* Nome da função: Tamanho_Interc
* Descrição: Calcula o tamanho de todas as interconexões juntas
* Parâmetros: Interc *inicio
* Interface Explícita: parâmetros Interc *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
float Tamanho_Interc(Interc *inicio);

/**************************************************************************************************************
* Nome da função: Relatorio
* Descrição: Grava no arquivo .txt o relatório final com todos so dados solicitados pelo podf do trabalho
* Parâmetros: Listas *inicio
* Interface Explícita: parâmetros Listas *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*******************************************************************************************************************/
void Relatorio(Listas *inicio);

/*******************************************************************************************************************************
* Nome da função: Interface_Grafica;
* Descrição: Responsável por criar a janela da interface gráfica da simulação;
* Parâmetros: Listas *inicio
* Interface Explícita: parâmetros Listas *inicio
* Interface Implícita: Nenhuma.
* Assertivas de Entrada:
*			Listas *inicio != NULL;
* Assertivas de saída: Nenhuma;
*********************************************************************************************************************************/
void Interface_Grafica(Listas* inicio);

/***************************************************************************************************************************
* Nome da função: put_pixel;
* Descrição: Desenha um pixel na tela;
* Parâmetros: SDL_Surface*, int, int, Uint8, Uint8, Uint8
* Interface Explícita: parâmetros SDL_Surface*, int, int, Uint8, Uint8, Uint8
* Interface Implícita: Nenhuma.
* Assertivas de entrada:
*			SDL_Surface* surface != NULL;
*			int x; int y; (posição a ser desenhado o pixel na tela;
*			Uint8 r, Uint8 g, Uint8 b; (parâmetros das cores em rgb);
* Assertivas de saída: nenhuma;
*****************************************************************************************************************************/
void putpixel(SDL_Surface*, int, int, Uint8, Uint8, Uint8);

/****************************************************************************************************************************
* Nome da função: cria_linha_horizontal;
* Descrição: cria uma linha horizontal ligando dois componentes da malha.
* Parâmetros: int, int, int,SDL_Surface*, int
* Interface Explícita: parâmetros int, int, int,SDL_Surface*, int
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			SDL_Surface*tela; ponteiro para a tela
*			int xi; int xf; posições x incial e final e 
*			int yc; posição y constante;
*			int condicao variável boolana (se a interconexão funciona ou não);
* Assertivas de saida: nenhuma;
******************************************************************************************************************************/ 
void cria_linha_horizontal(int, int, int,SDL_Surface*, int);

/****************************************************************************************************************************
* Nome da função: cria_linha_vertical;
* Descrição: cria uma linha vertical ligando dois componentes da malha.
* Parâmetros: int, int, int,SDL_Surface*, int
* Interface Explícita: parâmetros int, int, int,SDL_Surface*, int
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			SDL_Surface*tela; ponteiro para a tela
*			int xi; int xf; posições x incial e final e 
*			int yc; posição y constante;
*			int condicao variável boolana (se a interconexão funciona ou não);
* Assertivas de saida: nenhuma;
******************************************************************************************************************************/ 
void cria_linha_vertical(int, int, int, SDL_Surface*, int);

/****************************************************************************************************************************
* Nome da função: cria_linha_diagonal;
* Descrição: cria uma linha diagonal ligando dois componentes da malha.
* Parâmetros: int, int, int,SDL_Surface*, int
* Interface Explícita: parâmetros int, int, int,SDL_Surface*, int
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			SDL_Surface*tela; ponteiro para a tela
*			int xi; int xf; posições x incial e final e 
*			int yi; int yf; posição y inicial e final;
*			int condicao variável boolana (se a interconexão funciona ou não);
* Assertivas de saida: nenhuma;
******************************************************************************************************************************/ 
void cria_linha_diagonal(int, int, int, int,SDL_Surface*, int);

