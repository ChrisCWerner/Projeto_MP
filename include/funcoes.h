//Arquivo de header para funcoes principais

#include "leitura.h"


void Localiza_Paths(Listas *inicio);

Interc *Insere_Irmao(Interc *novo_elem, Interc *top);

int Calcula_Cap_Total(Interc *inicio);

void Calcula_Rel_Flow(Interc *inicio, int total);

int Calcula_Fluxo(void *inicio, char id);

void Gerencia_Sobra(Gerador *gerad);

void Fluxo_Adapt(Interc *inicio);

void Distribui_Recursos0(Listas *inicio);

void Atualiza_Paths(Interc *inicio);
