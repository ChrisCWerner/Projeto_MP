//Arquivo de header para funcoes principais
/**
 * @author Roberta Renally, Rennê Ruan, Christian Werner
 * @date 8 dez 2015
 * @brief *
 *
 * Biblioteca principal para as funcões da rede de distribuicao de energia
 */

/** @file */

#include "leitura.h"
#include <SDL/SDL.h>
/*********************************************************************//**
* @brief Nome da funcao: Inicializa_Record;
* Inicializa a estrutura que irá armazenar os dados dos relatórios.
* @remark Parâmetros: Nenhum
* @remark Interface Explícita: retorno Record *rec
* @remark Interface Implícita: Nenhuma.
* @remark Assertivas de Entrada: nenhuma
* @remark Assertivas de Saída: 
*			Record *Registro != NULL (registro alocado na memória)
*************************************************************************/
Record *Inicializa_Record(void);

/*********************************************************************//**
* @brief Nome da funcao: Localiza_Paths;
* Descricao: Faz as ligacões entre os Geradores e adapatadores e entre adapatadores e cidades,
*	através das interconexões.
* @remark Parâmetros: Listas *inicio
* @remark Interface Explícita: parâmetro Listas *inicio
* @remark Interface Implícita: Nenhuma.
* @remark Assertivas de entrada: 
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
* @remark Assertivas de saída:
*			nenhum
*************************************************************************/
void Localiza_Paths(Listas *inicio);

/*********************************************************************//**
* @brief Nome da funcao: Insere_Irmao;
* Descricao: Insere na lista de interconexao as outras interconexões que saem do mesmo adaptador.
* @remark Parâmetros: Interc *novo_elem, Interc *top
* @remark Interface Explícita: parâmetros Interc *novo_elem, Interc *top, retorno top.
* @remark Interface Implícita: Nenhuma.
* @remark Assertivas de entrada:
*			Interc *novo_elem != NULL
*			Inetrc *top != NULL
* @remark Assertivas de saída:
*			Interc *saida != NULL && Interc *saida = top;
*************************************************************************/
Interc *Insere_Irmao(Interc *novo_elem, Interc *top);

/*********************************************************************//**
* @brief Nome da funcao: Calcula_Cap_Total;
* Descricao: Calcula a capacidade total que todas as interconexões podem transportar;
* @remark Parâmetros: Interc *inicio
* @remark Interface Explícita: parâmetros Interc *inicio
* @remark Interface Implícita: Nenhuma.
* @remark Assertivas de Entrada:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
* @remark Assertivas de Saída:
*			int capacidade_total != 0;
*************************************************************************/
int Calcula_Cap_Total(Interc *inicio);

/*********************************************************************//**
* @brief Nome da funcao: Calcula_Rel_Flow;
* Descricao: Calcula o fluxo de energia nas interconexões;
* @remark Parâmetros: Interc *inicio, int total
* @remark Interface Explícita: parâmetros Interc *inicio, int total, retorno int i.
* @remark Interface Implícita: Nenhuma.
* @remark Assertivas de Entrada:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
*			int total = Capacidade_total;
* Assertivas de Saída:
*			int capacidade_total != 0;
*************************************************************************/
int Calcula_Rel_Flow(Interc *inicio, int total);

/*********************************************************************//**
* @brief Nome da funcao: Calcula_Fluxo;
* Descricao: Calcula a sobre de recurso nos adapatadores;
* @remark Parâmetros: void *inicio, char id
* @remark Interface Explícita: parâmetros void *inicio, char id, retorno sombra.
* @remark Interface Implícita: Nenhuma.
* @remark Assertivas de entrada: 
*			void *inicio != NULL;
*			caracter identificador;
* @remark Assertivas de saida:
*			int sobra;
*************************************************************************/
int Calcula_Fluxo(void *inicio, char id);

/*********************************************************************//**
* @brief Nome da funcao: Gerencia_Sobra;
* Descricao: Faz um gerenciamento da sobre de recursos tanto de adpatadores e geradores, para as interconexões
*		que saem dele;
* @remark Parâmetros: void *inicio, char id
* @remark Interface Explícita: parâmetros void *inicio, char id, retorno sombra.
* @remark Interface Implícita: Nenhuma.
* @remark Assertivas de entrada: 
*			void *inicio != NULL;
*			caracter identificador;
* Assertivas de saida:
*			nenhuma
*************************************************************************/
void Gerencia_Sobra(void *inicio, char id);

/*********************************************************************//**
* @brief Nome da funcao:Fluxo_Adpat;
* Descricao: calcula o fluxo de energia que chega ao adpatador;
* Parâmetros: Interc *inicio
* Interface Explícita: parâmetros Interc *inicio 
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			void *inicio != NULL;
* Assertivas de saida:
*			nenhum
*************************************************************************/
void Fluxo_Adapt(Interc *inicio);

/*********************************************************************//**
* @brief Nome da funcao: Fluxo_City;
* Descricao: Calcula o fluxo de recurso que chega nas cidades;
* Parâmetros: Interc *inicio, Record *rec
* Interface Explícita: parâmetros Interc *inicio, Record *rec
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Interc *inicio != NULL;
*			Record *Registro != NULL (Registro alocado)
* Assertivas de saida:
*			nenhuma
*************************************************************************/
void Fluxo_City(Interc *inicio, Record *rec);

/*********************************************************************//**
* @brief Nome da funcao: Verifica_Falhas
* Descricao: Verifica se houve falhas nas interconexões
* Parâmetros: Interc *inicio
* Interface Explícita: parâmetros Interc *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Interc *inicio != NULL;
*			Record *Registro != NULL;
* Assertivas de saida:
*			nehuma;
*************************************************************************/
void Verifica_Falhas(Interc *inicio, Record *rec);

/*********************************************************************//**
* @brief Nome da funcao: Maneja_Falhas
* Descricao: faz o gerenciamento das falhas nos geradores e adpatadores, modificando a variável booleana,
*		para indicar falha;
* Parâmetros: Interc *inicio
* Interface Explícita: parâmetros Interc *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Interc *inicio != NULL;
*			incio->funciona = 1 (Se falhou);
* Assertivas de saida:
*			nehuma;
*************************************************************************/
void Maneja_Falhas(Interc *inicio);

/*********************************************************************//**
* @brief Nome da funcao: Zera_Fluxo
* Descricao: Zera o fluxo das interconexões
* Parâmetros: Listas *inicio
* Interface Explícita: parâmetros Listas *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*************************************************************************/
void Zera_Fluxo(Listas *inicio);

/*********************************************************************//**
* @brief Nome da funcao: Distribui_Recursos;
* Descricao: Faz a distribuicao dos recursos dos geradores para os adaptadores, cidades através das interconexões.
* Parâmetros: Listas *inicio
* Interface Explícita: parâmetros Listas *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*************************************************************************/
void Distribui_Recursos(Listas *inicio);

/*********************************************************************//**
* @brief Nome da funcao: Examina_Cidades
* Descricao: Calcula o tempo em que a cidade está sem recurso;
* Parâmetros: Listas *inicio
* Interface Explícita: parâmetros Listas *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*************************************************************************/
void Examina_Cidades(Listas *inicio);

/*********************************************************************//**
* Nome da funcao: Total_Elementos
* Descricao: Calcula o total de cidades e geradores
* Parâmetros: Interc *inicio
* Interface Explícita: parâmetros Interc *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*************************************************************************/
void Total_Elementos(Listas *inicio);

/*********************************************************************//**
* Nome da funcao: Tamanho_Interc
* Descricao: Calcula o tamanho de todas as interconexões juntas
* Parâmetros: Interc *inicio
* Interface Explícita: parâmetros Interc *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*************************************************************************/
float Tamanho_Interc(Interc *inicio);

/*********************************************************************//**
* Nome da funcao: Relatorio
* Descricao: Grava no arquivo .txt o relatório final com todos so dados solicitados pelo pdf do trabalho
* Parâmetros: Listas *inicio
* Interface Explícita: parâmetros Listas *inicio
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			Listas *inicio != NULL;
* Assertivas de saida:
*			nehuma;
*************************************************************************/
void Relatorio(Listas *inicio);

/*********************************************************************//**
* Nome da funcao: Interface_Grafica;
* Descricao: Responsável por criar a janela da interface gráfica da simulacao;
* Parâmetros: Listas *inicio
* Interface Explícita: parâmetros Listas *inicio
* Interface Implícita: Nenhuma.
* Assertivas de Entrada:
*			Listas *inicio != NULL;
* Assertivas de saída: Nenhuma;
*************************************************************************/
void Interface_Grafica(Listas* inicio);

/*********************************************************************//**
* Nome da funcao: put_pixel;
* Descricao: Desenha um pixel na tela;
* Parâmetros: SDL_Surface*, int, int, Uint8, Uint8, Uint8
* Interface Explícita: parâmetros SDL_Surface*, int, int, Uint8, Uint8, Uint8
* Interface Implícita: Nenhuma.
* Assertivas de entrada:
*			SDL_Surface* surface != NULL;
*			int x; int y; (posicao a ser desenhado o pixel na tela;
*			Uint8 r, Uint8 g, Uint8 b; (parâmetros das cores em rgb);
* Assertivas de saída: nenhuma;
*************************************************************************/
void putpixel(SDL_Surface*, int, int, Uint8, Uint8, Uint8);

/*********************************************************************//**
* Nome da funcao: cria_linha_horizontal;
* Descricao: cria uma linha horizontal ligando dois componentes da malha.
* Parâmetros: int, int, int,SDL_Surface*, int
* Interface Explícita: parâmetros int, int, int,SDL_Surface*, int
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			SDL_Surface*tela; ponteiro para a tela
*			int xi; int xf; posicões x incial e final e 
*			int yc; posicao y constante;
*			int condicao variável boolana (se a interconexao funciona ou nao);
* Assertivas de saida: nenhuma;
*************************************************************************/
void cria_linha_horizontal(int, int, int,SDL_Surface*, int);

/*********************************************************************//**
* Nome da funcao: cria_linha_vertical;
* Descricao: cria uma linha vertical ligando dois componentes da malha.
* Parâmetros: int, int, int,SDL_Surface*, int
* Interface Explícita: parâmetros int, int, int,SDL_Surface*, int
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			SDL_Surface*tela; ponteiro para a tela
*			int xi; int xf; posicões x incial e final e 
*			int yc; posicao y constante;
*			int condicao variável boolana (se a interconexao funciona ou nao);
* Assertivas de saida: nenhuma;
*************************************************************************/
void cria_linha_vertical(int, int, int, SDL_Surface*, int);

/*********************************************************************//**
* Nome da funcao: cria_linha_diagonal;
* Descricao: cria uma linha diagonal ligando dois componentes da malha.
* Parâmetros: int, int, int,SDL_Surface*, int
* Interface Explícita: parâmetros int, int, int,SDL_Surface*, int
* Interface Implícita: Nenhuma.
* Assertivas de entrada: 
*			SDL_Surface*tela; ponteiro para a tela
*			int xi; int xf; posicões x incial e final e 
*			int yi; int yf; posicao y inicial e final;
*			int condicao variável boolana (se a interconexao funciona ou nao);
* Assertivas de saida: nenhuma;
*************************************************************************/ 
void cria_linha_diagonal(int, int, int, int,SDL_Surface*, int);

