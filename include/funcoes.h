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

void Verifica_Falhas(Interc *inicio);

void Contabiliza_Falhas(Interc *inicio, Record *rec);

void Maneja_Falhas(Interc *inicio);

void Distribui_Recursos(Listas *inicio);
