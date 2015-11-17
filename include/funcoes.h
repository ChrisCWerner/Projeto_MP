//Arquivo de header para funcoes principais

#include "leitura.h"


void Localiza_Paths(Listas *inicio);

Interc *Insere_Irmao(Interc *novo_elem, Interc *top);

int Calcula_Cap_Total(Interc *inicio);

void Calcula_Rel_Flow(Gerador *gerad);

int Calcula_Fluxo(Gerador *gerad);

void Gerencia_Sobra(Gerador *gerad);

void Distribui_Recursos0(Listas *inicio);

void Atualiza_Paths(Interc *inicio);
