//Arquivo de funcoes para leitura de dados

#include "leitura.h"
#include <assert.h>

Listas* inicializa(void) {
	Listas* sts = (Listas *) malloc(sizeof(Listas));
	sts->p_cidade = NULL;
	sts->p_gerador = NULL;
	sts->p_interc = NULL;
	sts->p_adapter = NULL;
	return sts;
}

Listas *Le_Arquivo(FILE *fp){
	
	assert(fp != NULL);
	
	
	Listas *sts = NULL;
	Cidade *cidade = NULL;
	Gerador *gerador = NULL;
	Interc *interc = NULL;
	Adapter *adapter = NULL;
	char c;
	
	
	sts = inicializa();
	
	
	while((c = getc(fp)) != EOF){
		
		if(c == 'C'){
			cidade = (Cidade *) malloc(sizeof(Cidade));
			
			fscanf(fp, "%s", cidade->nome_cidade);
			fscanf(fp, "%d", &(cidade->pos_x));
			fscanf(fp, "%d", &(cidade->pos_y));
			fscanf(fp, "%d", &(cidade->recurso_necessario));
			
			Insere_Lista('C', sts, cidade);
		}
		else if(c == 'G'){
			gerador = (Gerador *) malloc(sizeof(Gerador));
			
			fscanf(fp, "%s", gerador->nome_gerador);
			fscanf(fp, "%d", &(gerador->pos_x));
			fscanf(fp, "%d", &(gerador->pos_y));
			fscanf(fp, "%d", &(gerador->recurso_produzido));
			fscanf(fp, "%d", &(gerador->custo_gerador));
			
			Insere_Lista('G', sts, gerador);
		}
		else if(c == 'I'){
			interc = (Interc *) malloc(sizeof(Interc));
			
			fscanf(fp, "%s", interc->nome_interc);
			fscanf(fp, "%d", &(interc->pos_inic_x));
			fscanf(fp, "%d", &(interc->pos_inic_y));
			fscanf(fp, "%d", &(interc->pos_final_x));
			fscanf(fp, "%d", &(interc->pos_final_y));
			fscanf(fp, "%d", &(interc->capacidade_max));
			fscanf(fp, "%f", &(interc->chance_falha));
			fscanf(fp, "%d", &(interc->tempo_conserto));
			fscanf(fp, "%d", &(interc->custo_conserto));
			
			Insere_Lista('I', sts, interc);
		}
		else if(c == 'A'){
			adapter = (Adapter *) malloc(sizeof(Adapter));
			
			fscanf(fp, "%s", adapter->nome_adapter);
			fscanf(fp, "%d", &(adapter->pos_x));
			fscanf(fp, "%d", &(adapter->pos_y));
			
			Insere_Lista('A', sts, adapter);
		}
	}
	
	return sts;
}

void Insere_Lista(char tipo_elemento, Listas *top, void *elemento){
	
	assert(top != NULL);
	assert(elemento != NULL);
	assert((tipo_elemento == 'C') || (tipo_elemento == 'G') || \
		   (tipo_elemento == 'I') || (tipo_elemento == 'A'));
	
	
	if(tipo_elemento == 'C'){
		
		Cidade *novo_elem1 = (Cidade *) elemento;
		novo_elem1->prox = top->p_cidade;
		top->p_cidade = novo_elem1;
	}
	else if(tipo_elemento == 'G'){
		
		Gerador *novo_elem2 = (Gerador *) elemento;
		novo_elem2->prox = top->p_gerador;
		top->p_gerador = novo_elem2;
	}
	else if(tipo_elemento == 'I'){
		
		Interc *novo_elem3 = (Interc *) elemento;
		novo_elem3->prox = top->p_interc;
		top->p_interc = novo_elem3;
	}
	else if(tipo_elemento == 'A'){
		
		Adapter *novo_elem4 = (Adapter *) elemento;
		novo_elem4->prox = top->p_adapter;
		top->p_adapter = novo_elem4;
	}
}

void Imprime(Listas *inicio){
	
	assert(inicio != NULL);
	assert(inicio->p_cidade != NULL);
	assert(inicio->p_gerador != NULL);
	assert(inicio->p_interc != NULL);
	assert(inicio->p_adapter != NULL);
	
	
	Cidade *aux1 = NULL, *v_cidade;
	Gerador *aux2 = NULL, *v_gerador;
	Interc *aux3 = NULL;
	Adapter *aux4 = NULL, *v_adapter;
	
	
	printf("\nCidades: \n");
	
	aux1 = inicio->p_cidade;
	while(aux1 != NULL){
		printf("  %s: \n", aux1->nome_cidade);
		printf("\t Posicao: (%d, %d)\n", aux1->pos_x, aux1->pos_y);
		printf("\t Recursos necessarios: %d\n\n", aux1->recurso_necessario);
		aux1 = aux1->prox;
	}
	
	printf("\nGeradores: \n");
	
	aux2 = inicio->p_gerador;
	while(aux2 != NULL){
		printf("  %s: \n", aux2->nome_gerador);
		printf("\t Posicao: (%d, %d)\n", aux2->pos_x, aux2->pos_y);
		printf("\t Recurso produzido: %d\n", aux2->recurso_produzido);
		printf("\t Custo do gerador: %d\n\n", aux2->custo_gerador);
		aux2 = aux2->prox;
	}
	
	printf("\nInterconexoes: \n");
	
	aux3 = inicio->p_interc;
	while(aux3 != NULL){
		printf("  %s: \n", aux3->nome_interc);
		printf("\t Posicao inicial: (%d, %d)\n", aux3->pos_inic_x, aux3->pos_inic_y);
		printf("\t Posicao final: (%d, %d)\n", aux3->pos_final_x, aux3->pos_final_y);
		printf("\t Capacidade maxima: %d \n", aux3->capacidade_max);
		printf("\t Chance de falha: %.2f\n", aux3->chance_falha);
		printf("\t Tempo de conserto: %d\n", aux3->tempo_conserto);
		printf("\t Custo do conserto: %d\n\n", aux3->custo_conserto);
		
		if(aux3->vemc == 'C'){
			v_cidade = (Cidade *) aux3->vem;
			printf("\t  Vem de: \t%s\n", v_cidade->nome_cidade);
		}
		else if(aux3->vemc == 'G'){
			v_gerador = (Gerador *) aux3->vem;
			printf("\t  Vem de: \t%s\n", v_gerador->nome_gerador);
		}
		else if(aux3->vemc == 'A'){
			v_adapter = (Adapter *) aux3->vem;
			printf("\t  Vem de: \t%s\n", v_adapter->nome_adapter);
		}
		
		if(aux3->vaic == 'C'){
			v_cidade = (Cidade *) aux3->vai;
			printf("\t  Vai para: \t%s\n\n", v_cidade->nome_cidade);
		}
		else if(aux3->vaic == 'G'){
			v_gerador = (Gerador *) aux3->vai;
			printf("\t  Vai para: \t%s\n\n", v_gerador->nome_gerador);
		}
		else if(aux3->vaic == 'A'){
			v_adapter = (Adapter *) aux3->vai;
			printf("\t  Vai para: \t%s\n\n", v_adapter->nome_adapter);
		}
		
		aux3 = aux3->prox;
	}
	
	printf("\nAdaptadores: \n");
	
	aux4 = inicio->p_adapter;
	while(aux4 != NULL){
		printf("  %s: \n", aux4->nome_adapter);
		printf("\t Posicao: (%d, %d)\n", aux4->pos_x, aux4->pos_y);
		aux4 = aux4->prox;
	}
	
	printf("\n\n");
}

Listas* Destroi(Listas *inicio){
	
	assert(inicio != NULL);
	assert(inicio->p_cidade != NULL);
	assert(inicio->p_gerador != NULL);
	assert(inicio->p_interc != NULL);
	assert(inicio->p_adapter != NULL);
	
	
	Cidade *aux1 = NULL;
	Gerador *aux2 = NULL;
	Interc *aux3 = NULL;
	Adapter *aux4 = NULL;
	
	
	while(inicio->p_cidade != NULL){
		aux1 = inicio->p_cidade;
		inicio->p_cidade = aux1->prox;
		free(aux1);
	}
	while(inicio->p_gerador != NULL){
		aux2 = inicio->p_gerador;
		inicio->p_gerador = aux2->prox;
		free(aux2);
	}
	while(inicio->p_interc != NULL){
		aux3 = inicio->p_interc;
		inicio->p_interc = aux3->prox;
		free(aux3);
	}
	while(inicio->p_adapter != NULL){
		aux4 = inicio->p_adapter;
		inicio->p_adapter = aux4->prox;
		free(aux4);
	}
	
	return inicio;
}

