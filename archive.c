#include "functions.h"

// Abre o arquivo que contem o mapa e preenche a matriz de acordo
void pegaMapa(char mapa[LINHAS_MAPA][COLUNAS_MAPA], int nivel){
    FILE *arquivo;
    int c, i, j;
    char nome_arquivo[NOME_ARQUIVO];

    // Gera o nome do arquivo correto a se abrir (varia de acordo com o nivel)
    snprintf(nome_arquivo, NOME_ARQUIVO, "%s%d%s", "levels/nivel", nivel, ".txt");

    arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL){

    } else {
        for(i=0; i<LINHAS_MAPA; i++){
            for(j=0; j<COLUNAS_MAPA; j++){
                c = fgetc(arquivo);
                mapa[i][j] = c;
            }
            c = fgetc(arquivo);
        }
    }

    fclose(arquivo);
}

// Salva o jogo em dois arquivos
void salvaJogo(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado estado_atual){
    FILE *arq1;
    FILE *arq2;

    int i, j, flag;

    // Arquivo txt (onde fica contido o mapa)
    arq1 = fopen("Mousetrap_save.txt", "w");

    for(i=0; i<LINHAS_MAPA; i++){
        for (j = 0; j < COLUNAS_MAPA; j++){
            fwrite(&mapa[i][j], 1, 1, arq1);
        }
        fwrite("\n", 1, 1, arq1);
    }

    if(fwrite(&mapa[LINHAS_MAPA - 1][COLUNAS_MAPA - 1], 1, 1, arq1) == 1 ){
        flag = 1;
    }

    fclose(arq1);


    // Arquivo bin (onde ficam contidos os status e informacoes importantes do jogo)
    arq2 = fopen("Mousetrap_estado_atual.bin", "w+b");

    if(!fwrite(&estado_atual, sizeof(Estado), 1, arq2) == 1){
        flag = 0;
    }

    fclose(arq2);


    // Mensagem sobre o final do processo
    desenhaRetangulo();

    if(flag == 1){
        gotoxy(25,15);
        printf("Jogo salvo com sucesso");
    } else {
        gotoxy(25,15);
        printf("Erro ao salvar o arquivo");
    }

    Sleep(1500);
}

// Carrega arquivos do jogo
void carregaJogo(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual){
    FILE *arq1;
    FILE *arq2;

    //Estado estado_atual;

    int c, i, j, k;

    // Arquivo txt (onde fica contido o mapa)
    arq1 = fopen("Mousetrap_save.txt", "r");

    for(i=0; i<LINHAS_MAPA; i++){
        for(j=0; j<COLUNAS_MAPA; j++){
            c = fgetc(arq1);
            mapa[i][j] = c;
        }
        c = fgetc(arq1);
    }

    fclose(arq1);


    // Arquivo bin (onde ficam contidos os status e informacoes importantes do jogo)
    arq2 = fopen("Mousetrap_estado_atual.bin", "r+b");
    fread(&estado_atual, sizeof(Estado), 1, arq2);
    fclose(arq2);
}

