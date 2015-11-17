//Arquivo de funcoes para funcoes principais

#include "funcoes.h"
#include <assert.h>



void Localiza_Paths(Listas *inicio){
	
	assert(inicio != NULL);
	
	
	Cidade *aux1;
	Gerador *aux2;
	Interc *aux3;
	Adapter *aux4;
	int i;
	
	
	aux2 = inicio->p_gerador;
	while(aux2 != NULL){
		
		i = 0;
		aux3 = inicio->p_interc;
		while(aux3 != NULL){
			
			if((aux3->pos_inic_x == aux2->pos_x) && (aux3->pos_inic_y == aux2->pos_y)){
				aux3->vem = aux2;
				aux3->vemc = 'G';
				i++;
				aux2->prim = Insere_Irmao(aux3, aux2->prim);
			}
			
			aux3 = aux3->prox;
		}
		aux2->saida = i;
		
		aux2 = aux2->prox;
	}
	
	aux4 = inicio->p_adapter;
	while(aux4 != NULL){
		
		i = 0;
		aux3 = inicio->p_interc;
		while(aux3 != NULL){
			
			if((aux3->pos_inic_x == aux4->pos_x) && (aux3->pos_inic_y == aux4->pos_y)){
				aux3->vem = aux4;
				aux3->vemc = 'A';
				i++;
				aux4->prim = Insere_Irmao(aux3, aux4->prim);
			}
			else if((aux3->pos_final_x == aux4->pos_x) && (aux3->pos_final_y == aux4->pos_y)){
				aux3->vai = aux4;
				aux3->vaic = 'A';
			}
			
			aux3 = aux3->prox;
		}
		aux4->saida = i;
		
		aux4 = aux4->prox;
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

Interc *Insere_Irmao(Interc *novo_elem, Interc *top){
	
	assert(novo_elem != NULL);
	
	novo_elem->irmao = top;
	top = novo_elem;
	return top;
}

void Atualiza_Paths(Interc *inicio){
	
	
	
	
	
}

void Distribui_Recursos0(Listas *inicio){
	
	assert(inicio != NULL);
	assert(inicio->p_gerador->prim != NULL);
	
	
	Interc *path = NULL, *aux = NULL;
	Cidade *city = NULL;
	Gerador *gerad = NULL;
	Adapter *adapt = NULL;
	
	
	gerad = inicio->p_gerador;
	
	while(gerad != NULL){
		
		if(gerad->saida > 1){
			
			aux = gerad->prim;
			while(aux != NULL){
				gerad->total += aux->capacidade_max;
				aux = aux->irmao;
			}
			
			aux = gerad->prim;
			while(aux != NULL){
				aux->fluxo = (int) (gerad->recurso_produzido)*((float) (aux->capacidade_max))/((float) (gerad->total));
				if(aux->fluxo > aux->capacidade_max)	aux->fluxo = aux->capacidade_max;
				aux = aux->irmao;
			}
			
		}
		else {
			
			aux = gerad->prim;
			printf("\n %d\n", aux->capacidade_max);
			
			aux->fluxo = gerad->recurso_produzido;
			if(aux->fluxo > aux->capacidade_max)	aux->fluxo = aux->capacidade_max;
		}
		
		gerad = gerad->prox;
	}
	
	/*
			Fazer para adaptadores...
	*/
	
	
}








