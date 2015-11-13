//Arquivo de funcoes para funcoes principais

#include "funcoes.h"
#include <assert.h>



void Localiza_Paths(Listas *inicio){
	
	assert(inicio != NULL);
	
	
	Cidade *aux1;
	Gerador *aux2;
	Interc *aux3;
	Adapter *aux4;
	
	
	aux3 = inicio->p_interc;
	while(aux3 != NULL){
		
		aux2 = inicio->p_gerador;
		while(aux2 != NULL){
			
			if((aux3->pos_inic_x == aux2->pos_x) && (aux3->pos_inic_y == aux2->pos_y)){
				aux3->vem = aux2;
				aux3->vemc = 'G';
			}
			
			aux2 = aux2->prox;
		}
		aux3 = aux3->prox;
	}
	
	aux3 = inicio->p_interc;
	while(aux3 != NULL){
		
		aux4 = inicio->p_adapter;
		while(aux4 != NULL){
			
			if((aux3->pos_inic_x == aux4->pos_x) && (aux3->pos_inic_y == aux4->pos_y)){
				aux3->vem = aux4;
				aux3->vemc = 'A';
			}
			else if((aux3->pos_final_x == aux4->pos_x) && (aux3->pos_final_y == aux4->pos_y)){
				aux3->vai = aux4;
				aux3->vaic = 'A';
			}
			
			aux4 = aux4->prox;
		}
		aux3 = aux3->prox;
	}
	
	aux3 = inicio->p_interc;
	while(aux3 != NULL){
		
		aux1 = inicio->p_cidade;
		while(aux1 != NULL){
			
			if((aux3->pos_final_x == aux1->pos_x) && (aux3->pos_final_y == aux1->pos_y)){
				aux3->vai = aux1;
				aux3->vaic = 'C';
			}
			
			aux1 = aux1->prox;
		}
		aux3 = aux3->prox;
	}
}

void Distribui_G_A(Gerador *gerad, Adapter *adapt, Listas *inicio){
	
	/*
		?
	*/
	
}


