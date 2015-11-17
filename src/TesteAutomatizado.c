#include "funcoes.h"
#include "gtest/gtest.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

Listas *sts = NULL;
Listas *inicio = NULL;
Cidade *cidade = NULL;
Gerador *gerador = NULL;
Interc *interc = NULL;
Adapter *adaptador = NULL;

TEST(Alocando_as_Estruturas, Inicializa){

	sts = inicializa ();
	ASSERT_EQ(NULL, sts->p_cidade);
	ASSERT_EQ(NULL, sts->p_gerador);
	ASSERT_EQ(NULL, sts->p_interc);
	ASSERT_EQ(NULL, sts->p_adapter);
}

TEST(Inseri_na_Lista_Cidade, Cidade){
	cidade = (Cidade *) malloc(sizeof(Cidade));
	strcpy(cidade->nome_cidade, "A_City");
	cidade->pos_x = 20;
	cidade->pos_y = 15;
	cidade->recurso_necessario = 100;
	Insere_Lista('C', sts, cidade);
	EXPECT_STREQ("A_City", sts->p_cidade->nome_cidade);
	EXPECT_EQ(20, sts->p_cidade->pos_x);
	EXPECT_EQ(15,sts->p_cidade->pos_y);
}

TEST(Inseri_na_Lista_Gerador, Gerador){
	gerador = (Gerador *) malloc(sizeof(Gerador));
	strcpy(gerador->nome_gerador, "A_Gen");
	gerador->pos_x = 7;
	gerador->pos_y = 48;
	gerador->recurso_produzido = 110;
	gerador->custo_gerador = 1000;
	Insere_Lista('G', sts, gerador);
	EXPECT_STREQ("A_Gen", sts->p_gerador->nome_gerador);
	EXPECT_EQ(07, sts->p_gerador->pos_x);
	EXPECT_EQ(48, sts->p_gerador->pos_y);
	EXPECT_EQ(110, sts->p_gerador->recurso_produzido);
	EXPECT_EQ(1000, sts->p_gerador->custo_gerador);
}

TEST(Inseri_na_Lista_Interconexao, Interconexao){
	interc = (Interc *) malloc(sizeof(Interc));
	strcpy(interc->nome_interc, "A_Path");
	interc->pos_inic_x = 07;
	interc->pos_inic_y = 48;
	interc->pos_final_x = 21;
	interc->pos_final_y = 40;
	interc->capacidade_max = 140;
	interc->chance_falha = 0.1;
	interc->tempo_conserto = 14;
	interc->custo_conserto = 20;
	Insere_Lista('I', sts, interc);
	EXPECT_STREQ("A_Path", sts->p_interc->nome_interc);
	EXPECT_EQ(07,  sts->p_interc->pos_inic_x);
	EXPECT_EQ(48,  sts->p_interc->pos_inic_y);
	EXPECT_EQ(21,  sts->p_interc->pos_final_x);
	EXPECT_EQ(40, sts->p_interc->pos_final_y);
	EXPECT_EQ(140, sts->p_interc->capacidade_max);
	EXPECT_EQ(0.1*10, 10*sts->p_interc->chance_falha);
	EXPECT_EQ(14,  sts->p_interc->tempo_conserto);
	EXPECT_EQ(20,  sts->p_interc->custo_conserto);
	
}

TEST(Inseri_na_Lista_Adaptador, Adaptador){
	adaptador = (Adapter *) malloc(sizeof(Adapter));
	strcpy(adaptador->nome_adapter, "A_dapt");
	adaptador->pos_x = 21;
	adaptador->pos_y = 40;
	Insere_Lista('A', sts, adaptador);
	EXPECT_STREQ("A_dapt", sts->p_adapter->nome_adapter);
	EXPECT_EQ(21,  sts->p_adapter->pos_x);
	EXPECT_EQ(40,  sts->p_adapter->pos_y);
}

TEST(Localiza_caminhos, localizar){
	Localiza_Paths(sts);
	Gerador* aux1 = (Gerador*)sts->p_interc->vem;
	Adapter* aux2 = (Adapter*)sts->p_interc->vai;
	EXPECT_STREQ("A_Gen", aux1->nome_gerador);
	EXPECT_EQ('G',  sts->p_interc->vemc);
	EXPECT_STREQ("A_dapt", aux2->nome_adapter);
	EXPECT_EQ('A',  sts->p_interc->vaic);
}

TEST(Destroi_Listas, Destruir){
	sts = Destroi(sts);
	EXPECT_EQ(NULL, sts->p_cidade);
	EXPECT_EQ(NULL, sts->p_gerador);
	EXPECT_EQ(NULL, sts->p_interc);
	EXPECT_EQ(NULL, sts->p_adapter);
}

TEST(Leitura_do_arquivo_de_entrada, Leitura){
	FILE *fp = fopen("Arquivo.txt", "r");
	ASSERT_EQ(NULL, inicio);
	inicio = Le_Arquivo(fp);
	fclose(fp);
	Localiza_Paths(inicio);
	inicio = Destroi(inicio);
	EXPECT_EQ(NULL, inicio->p_cidade);
	EXPECT_EQ(NULL, inicio->p_gerador);
	EXPECT_EQ(NULL, inicio->p_interc);
	EXPECT_EQ(NULL, inicio->p_adapter);
}

int main(int argc, char **argv) {
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
