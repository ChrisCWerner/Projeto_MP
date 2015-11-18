//Arquivo de funcoes para leitura de dados

#include "leitura.h"
#include <assert.h>

/***********************************************************************************
* Nome da função: Inicializa;
* Descrição: Inicializa a estrutura que contem as listas de cada tipo de dado;
* Assertivas de Entrada: 
*			nenhum
* Assertivas de Saída:
*			Listas criadas:
*			Listas->p_cidade = NULL;
*			Listas->p_gerador = NULL;
*			Listas->p_interc = NULL;
*			Listas->p_adapter = NULL;
*************************************************************************************/
Listas *Inicializa(void){
	Listas *sts = (Listas *) malloc(sizeof(Listas));
	sts->p_cidade = NULL;
	sts->p_gerador = NULL;
	sts->p_interc = NULL;
	sts->p_adapter = NULL;
	
	return sts;
}
/**********************************************************************************************************************************
* Nome da função: Le_Arquivo;
* Descrição: Le o arquivo de entrada e insere os tipos de informações nas respectivas listas.
* Assertivas de Entrada: 
*			FILE *fp != NULL (ponteiro para arquivo de entrada)
* Assertivas de Saída:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
*************************************************************************************************************************************/
Listas *Le_Arquivo(FILE *fp){
	
	assert(fp != NULL);
	
	Listas *sts = NULL;
	Cidade *cidade = NULL;
	Gerador *gerador = NULL;
	Interc *interc = NULL;
	Adapter *adapter = NULL;
	char c;
	
	
	sts = Inicializa();
	
	
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
/**************************************************************************************************************************
* Nome da função: Insere_Lista;
* Descrição: Insere o tipo de informação lida, a partir da função 'Le_arquivo', para o tipo correspondente das Listas.
* Assertivas de Entrada: 
*			char tipo_elemento;
*			Listas (previamente alocada, podendo ou não estarem vazias)
*			void *elemento (ponteiro para o elemento a ser inserido)
* Assertivas de Saída:
*			nenhuma
*****************************************************************************************************************************/
void Insere_Lista(char tipo_elemento, Listas *top, void *elemento){
	
	assert(top != NULL);
	assert(elemento != NULL);
	assert((tipo_elemento == 'C') || (tipo_elemento == 'G') || \
		   (tipo_elemento == 'I') || (tipo_elemento == 'A'));
	
	
	if(tipo_elemento == 'C'){
		
		Cidade *novo_elem1 = (Cidade *) elemento;
		novo_elem1->prox = top->p_cidade;
		top->p_cidade = novo_elem1;
		
		novo_elem1->fluxo = 0;
	}
	else if(tipo_elemento == 'G'){
		
		Gerador *novo_elem2 = (Gerador *) elemento;
		novo_elem2->prox = top->p_gerador;
		top->p_gerador = novo_elem2;
		
		novo_elem2->saida = 0;
		novo_elem2->total = 0;
		novo_elem2->sobra = 0;
		novo_elem2->works = 0;
		novo_elem2->cheio = 0;
		novo_elem2->prim = NULL;
	}
	else if(tipo_elemento == 'I'){
		
		Interc *novo_elem3 = (Interc *) elemento;
		novo_elem3->prox = top->p_interc;
		top->p_interc = novo_elem3;
		
		novo_elem3->fluxo = 0;
		novo_elem3->rel_flow = 1;
		novo_elem3->funciona = 1;
		novo_elem3->irmao = NULL;
	}
	else if(tipo_elemento == 'A'){
		
		Adapter *novo_elem4 = (Adapter *) elemento;
		novo_elem4->prox = top->p_adapter;
		top->p_adapter = novo_elem4;
		
		novo_elem4->fluxo = 0;
		novo_elem4->saida = 0;
		novo_elem4->total = 0;
		novo_elem4->sobra = 0;
		novo_elem4->works = 0;
		novo_elem4->cheio = 0;
		novo_elem4->prim = NULL;
	}
}
/*********************************************************************************************************************************
* Nome da função: Imprime;
* Descrição: Imprime a estrutura que armazena cada tipo de lista, ou seja, vai imprimir cada uma das listas de cidades, geradores,
	     adaptadores e interconexões.
* Assertivas de Entrada:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
* Assertivas de Saída:
*			nenhuma
***********************************************************************************************************************************/
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
		
		printf("\t Recursos recebidos: %d\n\n", aux1->fluxo);
		aux1 = aux1->prox;
	}
	
	getchar();
	printf("\nGeradores: \n");
	
	aux2 = inicio->p_gerador;
	while(aux2 != NULL){
		printf("  %s: \n", aux2->nome_gerador);
		printf("\t Posicao: (%d, %d)\n", aux2->pos_x, aux2->pos_y);
		printf("\t Recurso produzido: %d\n", aux2->recurso_produzido);
		printf("\t Custo do gerador: %d\n\n", aux2->custo_gerador);
		
		printf("\t Quantidade de caminhos de saida: %d\n", aux2->saida);
		printf("\t Recursos desperdicados: %d\n", aux2->sobra);
		printf("\t Capacidade total de transporte: %d\n", aux2->total);
		printf("\t Total de saidas funcionando: %d\n", aux2->works);
		printf("\t Total de saidas lotadas: %d\n\n", aux2->cheio);
		aux2 = aux2->prox;
	}
	
	getchar();
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
		
		printf("\t Fluxo de recursos: %d\n", aux3->fluxo);
		printf("\t Fluxo relativo de recursos: %.2f\n\n", aux3->rel_flow);
		
		
		if(aux3->vemc == 'G'){
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
		else if(aux3->vaic == 'A'){
			v_adapter = (Adapter *) aux3->vai;
			printf("\t  Vai para: \t%s\n\n", v_adapter->nome_adapter);
		}
		
		aux3 = aux3->prox;
	}
	
	getchar();
	printf("\nAdaptadores: \n");
	
	aux4 = inicio->p_adapter;
	while(aux4 != NULL){
		printf("  %s: \n", aux4->nome_adapter);
		printf("\t Posicao: (%d, %d)\n\n", aux4->pos_x, aux4->pos_y);
		
		printf("\t Fluxo de recursos: %d\n", aux4->fluxo);
		printf("\t Quantidade de caminhos de saida: %d\n", aux4->saida);
		printf("\t Capacidade total de transporte: %d\n", aux4->total);
		printf("\t Recursos desperdicados: %d\n", aux4->sobra);
		printf("\t Total de saidas funcionando: %d\n", aux4->works);
		printf("\t Total de saidas lotadas: %d\n\n", aux4->cheio);
		aux4 = aux4->prox;
	}
	
	printf("\n\n");
}
/**********************************************************************************************************
* Nome da função: Destroi;
* Descrição: Desaloca a posição de memória ocupada pelas listas.
* Assertivas de Entrada:
*			Listas criadas:
*			Listas->p_cidade != NULL;
*			Listas->p_gerador != NULL;
*			Listas->p_interc != NULL;
*			Listas->p_adapter != NULL;
* Assertivas de Saída:
*			Listas = NULL;
***********************************************************************************************************/
Listas *Destroi(Listas *inicio){
	
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

