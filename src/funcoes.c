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
		aux2->works = i;
		
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
		aux4->works = i;
		
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

int Calcula_Cap_Total(Interc *inicio){
	
	assert(inicio != NULL);
	
	int capacidade_total = 0;
	
	do {
		if(inicio->funciona)
			capacidade_total += inicio->capacidade_max;
		inicio = inicio->irmao;
	} while(inicio != NULL);
	return capacidade_total;
}

int Calcula_Fluxo(Gerador *gerad){
	
	assert(gerad->prim != NULL);
	
	Interc *path = NULL;
	int sobra = 0;
	
	path = gerad->prim;
	while(path != NULL){
		if(path->funciona){
			path->fluxo = (gerad->recurso_produzido)*(path->capacidade_max);
			path->fluxo = (float) (path->fluxo)/(gerad->total);
			
			if(path->fluxo > path->capacidade_max){
				sobra += path->fluxo - path->capacidade_max;
				path->fluxo = path->capacidade_max;
			}
		}
		path = path->irmao;
	}
	
	return sobra;
}

void Gerencia_Sobra(Gerador *gerad){
	
	assert(gerad->sobra != 0);
	
	Interc *path = NULL;
	
	if(gerad->saida == 1)
		return;
	else {
		
		path = gerad->prim;
		while(path != NULL){
			
			
			
			path = path->irmao;
		}
		
		
	}
	
	
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
		
		//Calcula gerad->total;
		gerad->total = Calcula_Cap_Total(gerad->prim);
		
		//Distribui recursos;
		gerad->sobra = Calcula_Fluxo(gerad);
		
		//Gerencia sobra (?)
		
//		if(gerad->sobra){
//			
//			
//			
//			path = gerad->prim;
//			while(path != NULL){
//				
//				if((path->fluxo < path->capacidade_max) && (path->funciona)){
////					path->fluxo += 
//				}
//				
//				path = path->irmao;
//			}
//		}
		
		
		gerad = gerad->prox;
	}
	
	/*
			Fazer para adaptadores...
	*/
	
	
}

void Atualiza_Paths(Interc *inicio){
	
	
	
	
	
}








