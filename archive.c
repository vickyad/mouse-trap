#include "functions.h"

/* Abre o arquivo que contem o mapa e preenche a matriz de acordo */
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


/* Salva o jogo em dois arquivos */
void salvaJogo(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado estado_atual, int option){
    FILE *arq1;
    FILE *arq2;

    char nome_arquivo[NOME_ARQUIVO];

    int i, j, flag;

    // Gera o nome do arquivo correto a se abrir (varia de acordo com o nivel)
    snprintf(nome_arquivo, NOME_ARQUIVO, "%s%d%s", "saves/Mousetrap_save", option, ".txt");

    // Arquivo txt (onde fica contido o mapa)
    arq1 = fopen(nome_arquivo, "w");

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


    // Gera o nome do arquivo correto a se abrir (varia de acordo com o nivel)
    snprintf(nome_arquivo, NOME_ARQUIVO, "%s%d%s", "saves/Mousetrap_estado_atual", option, ".bin");

    // Arquivo bin (onde ficam contidos os status e informacoes importantes do jogo)
    arq2 = fopen(nome_arquivo, "w+b");

    if(!fwrite(&estado_atual, sizeof(Estado), 1, arq2)){
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

    getch();
}


/* Carrega arquivos do jogo */
void carregaJogo(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual, int option){
    FILE *arq1;
    FILE *arq2;

    char nome_arquivo[NOME_ARQUIVO];

    int c, i, j;

    // Arquivo txt (onde fica contido o mapa)
    // Gera o nome do arquivo correto a se abrir (varia de acordo com o nivel)
    snprintf(nome_arquivo, NOME_ARQUIVO, "%s%d%s", "saves/Mousetrap_save", option, ".txt");

    arq1 = fopen(nome_arquivo, "r");

    for(i=0; i<LINHAS_MAPA; i++){
        for(j=0; j<COLUNAS_MAPA; j++){
            c = fgetc(arq1);
            mapa[i][j] = c;
        }
        c = fgetc(arq1);
    }

    fclose(arq1);


    // Arquivo bin (onde ficam contidos os status e informacoes importantes do jogo)
    // Gera o nome do arquivo correto a se abrir (varia de acordo com o nivel)
    snprintf(nome_arquivo, NOME_ARQUIVO, "%s%d%s", "saves/Mousetrap_estado_atual", option, ".bin");

    arq2 = fopen(nome_arquivo, "r+b");
    fread(&estado_atual, sizeof(Estado), 1, arq2);
    fclose(arq2);
}


/* Abre o arquivo do ranking e salva em um vetor */
void leRanking(FILE *arq, Save ranking[MAX_SAVES]){
    int i = 0;

    while (!feof(arq) && i < MAX_SAVES){
        fread(&ranking[i], sizeof(Save), 1, arq);

        i++;
    }
}


/* Salva o vetor contendo o ranking em um arquivo */
void salvaRanking(FILE *arq, Save ranking[MAX_SAVES]){
    int i = 0;

    while(i < MAX_SAVES){
        fwrite(&ranking[i], sizeof(Save), 1, arq);

        i++;
    }
}


/* Atualiza o ranking, caso necessario, ao final de um jogo */
void atualizaRanking(Jogador last_win){
    FILE *arq;
    Save ranking[MAX_SAVES] = {{"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}};
    int flag;

    if(!(arq = fopen("ranking.bin", "rb"))){
        printf("Erro na leitura do arquivo");
        getch();
    } else {
        leRanking(arq, ranking);

        fclose(arq);

        flag = atualizaVetor(ranking, last_win);

        // Caso o vetor tenha sido alterado, e feita a reordenacao e o novo ranking e salvo
        if(flag){
            ordenaVetor(ranking);

            if(!(arq = fopen("ranking.bin", "wb"))){
                printf("Erro na escrita do arquivo");
                getch();
            } else {
                salvaRanking(arq, ranking);

                fclose(arq);
            }
        }
    }

    desenhaInterface();

    desenha_ranking(ranking);

    getch();
}
