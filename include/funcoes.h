//Arquivo de header para funcoes principais

#include "leitura.h"

Record *Inicializa_Record(void);

void Localiza_Paths(Listas *inicio);

Interc *Insere_Irmao(Interc *novo_elem, Interc *top);

int Calcula_Cap_Total(Interc *inicio);

int Calcula_Rel_Flow(Interc *inicio, int total);

int Calcula_Fluxo(void *inicio, char id);

void Gerencia_Sobra(void *inicio, char id);

void Fluxo_Adapt(Interc *inicio);

void Fluxo_City(Interc *inicio, Record *rec);

void Verifica_Falhas(Interc *inicio);

void Maneja_Falhas(Interc *inicio);

void Zera_Fluxo(Listas *inicio);

void Distribui_Recursos(Listas *inicio);

float Tamanho_Interc(Interc *inicio);

void Relatorio(Listas *inicio, int tempo);

void Interface_Grafica(Listas* inicio);

void ReunirDados(Listas *inicio);
