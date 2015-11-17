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
	
	Interc *aux = inicio;
	int capacidade_total = 0;
	
	while(aux != NULL){
		if((aux->funciona) && (aux->fluxo < aux->capacidade_max))
			capacidade_total += aux->capacidade_max;
		aux = aux->irmao;
	}
	return capacidade_total;
}

void Calcula_Rel_Flow(Gerador *gerad){
	
	assert(gerad->total != 0);
	
	Interc *aux = gerad->prim;
	
	while(aux != NULL){
		if((aux->funciona) && (aux->fluxo < aux->capacidade_max))
			aux->rel_flow = (float) (aux->capacidade_max) / (gerad->total);
		else	aux->rel_flow = 0;
		aux = aux->irmao;
	}
}

int Calcula_Fluxo(Gerador *gerad){
	
	assert(gerad->prim != NULL);
	
	Interc *path = NULL;
	int sobra = 0, rec_disp;
	
	rec_disp = gerad->recurso_produzido;
	gerad->cheio = 0;
	path = gerad->prim;
	while(path != NULL){
		if(path->funciona){
			path->fluxo = (path->rel_flow) * (rec_disp);
			
			
			if(path->fluxo > path->capacidade_max){
				sobra += path->fluxo - path->capacidade_max;
				path->fluxo = path->capacidade_max;
			}
			
		assert(path->fluxo <= path->capacidade_max);
		
			if(path->fluxo == path->capacidade_max)
				gerad->cheio++;
		}
		else	path->fluxo = 0;
		
		path = path->irmao;
	}
	
	return sobra;
}

void Gerencia_Sobra(Gerador *gerad){
	
	assert(gerad->sobra != 0);
	assert(gerad->works >= 0);
	assert(gerad->cheio >= 0);
	
	Interc *path = NULL;
	int sobra;
	
	
	if((gerad->works - gerad->cheio) == 0)
		return;
	else {
		while(((gerad->works - gerad->cheio) == 0) && (gerad->total != 0)){
			
			if(((gerad->works - gerad->cheio) == 1)){
				
				
				
			}
			
			
			sobra = 0;
			gerad->total = Calcula_Cap_Total(gerad->prim);
			Calcula_Rel_Flow(gerad);
			path = gerad->prim;
			while(path != NULL){
				
				if((path->funciona) && (path->fluxo < path->capacidade_max))
					path->fluxo += (path->rel_flow) * (gerad->sobra);
				
				if(path->fluxo > path->capacidade_max){
					sobra += path->fluxo - path->capacidade_max;
					path->fluxo = path->capacidade_max;
				}
				
				path = path->irmao;
			}
			
			gerad->sobra = sobra;
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
		Calcula_Rel_Flow(gerad);
		
		//Gerencia sobra (?)
		if(gerad->sobra > 0)
			Gerencia_Sobra(gerad);
		
		
		
		gerad = gerad->prox;
	}
	
	/*
			Fazer para adaptadores...
	*/
	
	
}

void Atualiza_Paths(Interc *inicio){
	
	
	
	
	
}








