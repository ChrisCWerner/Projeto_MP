//Arquivo de funcoes para funcoes principais

#include "funcoes.h"
#include "math.h"

Record *Inicializa_Record(void){
	Record *rec = (Record *) malloc(sizeof(Record));
	rec->custo_total = 0;
	rec->tempo_de_falha = 0;
	rec->total_geradores = 0;
	rec->total_cidades = 0;
	rec->energia_total_geradores = 0;
	rec->energia_gasta_cidades = 0;
	rec->tamanho_interc = 0;
	rec->numerofalhas = 0;

	return rec;
}

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

int Calcula_Rel_Flow(Interc *inicio, int total){
	
	Interc *aux = inicio;
	int i = 0;
	
	while(aux != NULL){
		if((aux->funciona) && (aux->fluxo < aux->capacidade_max) && (total != 0))
			aux->rel_flow = (float) (aux->capacidade_max) / (total);
		else {
			aux->rel_flow = 0;
			i++;
		}
		aux = aux->irmao;
	}
	return i;
}

int Calcula_Fluxo(void *inicio, char id){
	
	assert(inicio != NULL);
	
	Gerador *gerad = NULL;
	Interc *path = NULL;
	Adapter *adapt = NULL;
	int sobra = 0, rec_disp;
	
	if(id == 'G'){
		gerad = (Gerador *) inicio;
		rec_disp = gerad->recurso_produzido;
		gerad->cheio = 0;
		path = gerad->prim;
	}
	else if(id == 'A'){
		adapt = (Adapter *) inicio;
		rec_disp = adapt->fluxo;
		adapt->cheio = 0;
		path = adapt->prim;
	}
	
	while(path != NULL){
		if(path->funciona){
			path->fluxo = (path->rel_flow) * (rec_disp);
			
			if(path->fluxo > path->capacidade_max){
				sobra += path->fluxo - path->capacidade_max;
				path->fluxo = path->capacidade_max;
			}
			
		assert(path->fluxo <= path->capacidade_max);
		
			if(path->fluxo == path->capacidade_max){
				if(id == 'G')
					gerad->cheio++;
				if(id == 'A')
					adapt->cheio++;
			}
		}
		else	path->fluxo = 0;
		
		path = path->irmao;
	}
	
	return sobra;
}

void Gerencia_Sobra(void *inicio, char id){
	
	Gerador *gerad = NULL;
	Interc *path = NULL;
	Adapter *adapt = NULL;
	int sobra, sobra_saida, path_ncheio = 0, total;
	
	if(id == 'G'){
		gerad = (Gerador *) inicio;
		path_ncheio = gerad->works - gerad->cheio;
		sobra_saida = gerad->sobra;
	}
	else if(id == 'A'){
		adapt = (Adapter *) inicio;
		path_ncheio = adapt->works - adapt->cheio;
		sobra_saida = adapt->sobra;
	}
	
	if(path_ncheio == 0)
		return;
	
	while((path_ncheio != 0) && (total != 0)){
		
		if(id == 'G'){
			path = gerad->prim;
			path_ncheio = gerad->works - gerad->cheio;
		}
		else if(id == 'A'){
			path = adapt->prim;
			path_ncheio = adapt->works - adapt->cheio;
		}
		
		total = Calcula_Cap_Total(path);
		Calcula_Rel_Flow(path, total);
		
		sobra = 0;
		if(path_ncheio == 1){
			while(path != NULL){
				if((path->fluxo < path->capacidade_max) && (path->funciona))
					break;
				path = path->irmao;
			}
			
			path->fluxo += sobra_saida;
			
			if(path->fluxo > path->capacidade_max){
				sobra += path->fluxo - path->capacidade_max;
				path->fluxo = path->capacidade_max;
			}
			
			if(id == 'G')
				gerad->total = 0;
			else if(id == 'A')
				adapt->total = 0;
		}
		else {
			while(path != NULL){
				if((path->funciona) && (path->fluxo < path->capacidade_max))
					path->fluxo += (path->rel_flow) * (sobra_saida);
				
				if(path->fluxo > path->capacidade_max){
					sobra += path->fluxo - path->capacidade_max;
					path->fluxo = path->capacidade_max;
				}
				
				path = path->irmao;
			}
		}
		
		sobra_saida = sobra;
	}
	if(id == 'G')
		gerad->sobra = sobra_saida;
	else if(id == 'A')
		adapt->sobra = sobra_saida;
}

void Fluxo_Adapt(Interc *inicio){
	
	assert(inicio->vai != NULL);
	
	Interc *path = NULL;
	Adapter *adapt = NULL;
	
	path = inicio;
	while(path != NULL){
		
		if(path->vaic == 'A'){
			adapt = (Adapter *) path->vai;
			adapt->fluxo += path->fluxo;
		}
		
		path = path->prox;
	}
}

void Fluxo_City(Interc *inicio){
	
	assert(inicio->vai != NULL);
	
	Interc *path = NULL;
	Cidade *city = NULL;
	
	path = inicio;
	while(path != NULL){
		
		if(path->vaic == 'C'){
			city = (Cidade *) path->vai;
			city->fluxo += path->fluxo;
		}
		
		path = path->prox;
	}
}

void Verifica_Falhas(Interc *inicio){
	
	Interc *path = NULL;
	Gerador *gerad = NULL;
	Adapter *adapt = NULL;
	float num;
	
	path = inicio;
	while(path != NULL){
		
		num = ((float) rand() / RAND_MAX);
		
		if((path->chance_falha > 0) && (path->chance_falha > num) && (path->funciona)){
			path->funciona = 0;
			if(path->vemc == 'G'){
				gerad = (Gerador *) path->vem;
				gerad->works--;
			}
			else {
				adapt = (Adapter *) path->vem;
				adapt->works--;
			}
		}
		
		path = path->prox;
	}
}

void Contabiliza_Falhas(Interc *inicio, Record *rec){
	
	Interc *path = NULL;
	
	path = inicio;
	while(path != NULL){
		if(!path->funciona){
			rec->numerofalhas += 1;
			rec->custo_total += path->custo_conserto;
			rec->tempo_de_falha += path->tempo_conserto;
			path->time_wrk = path->tempo_conserto;
		}
		path = path->prox;
	}
}

void Maneja_Falhas(Interc *inicio){
	
}

void Distribui_Recursos(Listas *inicio){
	
	assert(inicio != NULL);
	assert(inicio->p_gerador->prim != NULL);
	
	
	Gerador *gerad = NULL;
	Adapter *adapt = NULL;
	
	Verifica_Falhas(inicio->p_interc);
	Contabiliza_Falhas(inicio->p_interc, inicio->p_record);
	
	gerad = inicio->p_gerador;
	while(gerad != NULL){
		
		gerad->total = Calcula_Cap_Total(gerad->prim);
		
		Calcula_Rel_Flow(gerad->prim, gerad->total);
		gerad->sobra = Calcula_Fluxo(gerad, 'G');
		
		if(gerad->sobra > 0)
			Gerencia_Sobra(gerad, 'G');
		
		gerad = gerad->prox;
	}
	
	Fluxo_Adapt(inicio->p_interc);
	
	adapt = inicio->p_adapter;
	while(adapt != NULL){
		
		adapt->total = Calcula_Cap_Total(adapt->prim);
		
		Calcula_Rel_Flow(adapt->prim, adapt->total);
		adapt->sobra = Calcula_Fluxo(adapt, 'A');
		
		if(adapt->sobra > 0)
			Gerencia_Sobra(adapt, 'A');
		
		adapt = adapt->prox;
	}
	
	Fluxo_City(inicio->p_interc);
}



void Relatorio(Listas *inicio, Record* rec,int tempo){
	int custoaux = 0, cidades_sem_recurso = 0;
	Cidade *aux1 = NULL;
	Gerador *aux2 = NULL;
	Interc *aux3 = NULL;
	Adapter *aux4 = NULL;

	aux1 = inicio->p_cidade;
	aux2 = inicio->p_gerador;
	aux3 = inicio->p_interc;

	FILE* arq;
	arq = fopen("Relatorio","w+");
	
	fprintf(arq, "Tempo total de simulação: %d\n", tempo);
	while(aux2 != NULL){
		rec->total_geradores += 1;
		rec->energia_total_geradores += aux2->recurso_produzido;
		custoaux += aux2->custo_gerador;
		rec->custo_total += (custoaux*tempo);
		aux2 = aux2->prox;
	}
	fprintf(arq, "Custo total da simulação: %d\n", rec->custo_total);
	fprintf(arq, "Total de geradores: %d\n", rec->total_geradores);
	fprintf(arq, "Energia total gerada: %d\n", rec->energia_total_geradores);

	while(aux1 != NULL){
		rec->total_cidades += 1;
		rec->energia_gasta_cidades += aux1->fluxo;
		aux1 = aux1->prox;
	
	}
	fprintf(arq, "Energia total gasta pelas cidades: %d\n", rec->energia_gasta_cidades);

	while(aux3 != NULL){
		rec->tamanho_interc += sqrt(pow(aux3->pos_final_x - aux3->pos_inic_x,2) 
					+ pow(aux3->pos_final_y - aux3->pos_inic_y,2));
		aux3 = aux3->prox;
	}
	fprintf(arq, "Tamanho total das interconexões: %d\n", rec->tamanho_interc);
	fprintf(arq, "Número de falhas nas interconexões: %d\n", rec->numerofalhas);
	fprintf(arq, "Tempo que ficaram sem recurso: %d\n", rec->tempo_de_falha);
	fprintf(arq, "Número de cidades que ficaram sem recurso necessário: \n");
	fprintf(arq, "Tempo que ficaram sem recurso: \n");


	fclose(arq);

}


