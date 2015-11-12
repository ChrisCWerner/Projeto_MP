//Arquivo de funcoes para leitura de dados

#include "leitura.h"
#include <assert.h>

listas *Le_Arquivo(FILE *fp){
	
	listas *sts;
	char c;
	
	assert(fp);
	
	sts = (listas *) malloc(sizeof(listas));
	sts->p_cidade = (cidade *) malloc(sizeof(cidade));
	sts->p_gerador = (gerador *) malloc(sizeof(gerador));
	sts->p_interc = (interc *) malloc(sizeof(interc));
	sts->p_adaptador = (adaptador *) malloc(sizeof(adaptador));
	
	
	while((c = getc(fp)) != EOF){
		
		if(c == 'C'){
			fscanf(fp, "%[^\0]s", sts->p_cidade->nome_cidade);
			fscanf(fp, "%d", sts->p_cidade->pos_x);
			fscanf(fp, "%d", sts->p_cidade->pos_y);
			fscanf(fp, "%d", sts->p_cidade->recurso_necessario);
			
			
			/* TODO (Chris#1#): Terminar... */
		}
		else if(c == 'G'){
			fscanf(fp, "%[^\0]s", sts->p_gerador->nome_gerador);
			fscanf(fp, "%d", sts->p_gerador->pos_x);
			fscanf(fp, "%d", sts->p_gerador->pos_y);
			fscanf(fp, "%d", sts->p_gerador->recurso_produzido);
			fscanf(fp, "%d", sts->p_gerador->custo_gerador);
			
			
			/* TODO (Chris#1#): Terminar... */
		}
		else if(c == 'I'){
			fscanf(fp, "%[^\0]s", sts->p_interc->nome_interc);
			fscanf(fp, "%d", sts->p_interc->pos_inic_x);
			fscanf(fp, "%d", sts->p_interc->pos_inic_y);
			fscanf(fp, "%d", sts->p_interc->pos_final_x);
			fscanf(fp, "%d", sts->p_interc->pos_final_y);
			fscanf(fp, "%d", sts->p_interc->capacidade_max);
			fscanf(fp, "%f", sts->p_interc->chance_falha);
			fscanf(fp, "%d", sts->p_interc->tempo_conserto);
			fscanf(fp, "%d", sts->p_interc->custo_conserto);
			
			
			/* TODO (Chris#1#): Terminar... */
		}
		else if(c == 'A'){
			fscanf(fp, "%[^\0]s", sts->p_adaptador->nome_adaptador);
			fscanf(fp, "%d", sts->p_adaptador->pos_x);
			fscanf(fp, "%d", sts->p_adaptador->pos_y);
			
			
			/* TODO (Chris#1#): Terminar... */
		}
		
		
		
		
		
		
		
		/* TODO (Chris#1#): Terminar... */
	}
	
	
	
	
	return sts;
}
