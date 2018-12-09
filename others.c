#include "functions.h"

/* ----------// Telas //---------- */
/* Tela da parte inicial do jogo */
void inicio(Estado *estado_atual){
    int flag = 0;

    clrscr();

    desenhaInterface();
    desenhaInicio();

    do{
        // Guarda o nome digitado pelo jogador
        fflush(stdin);
        gets(estado_atual->jogador.nome);

        // Verifica se o nome é grande ou pequeno demais
        if(strlen(estado_atual->jogador.nome) > NOME_MAX || strlen(estado_atual->jogador.nome) < 1){
            desenhaInterface();

            desenhaRetangulo();

            // Caso o nome seja muito grande
            if(strlen(estado_atual->jogador.nome) > NOME_MAX){
                gotoxy(18, 14);
                printf("Uau, mas que nome bonito, pena que %c", 130);
                gotoxy(18,15);
                printf("grande demais...");
                gotoxy(18, 17);
                printf("Que tal um apelido?");

                flag = 1;
            } else {
            // Caso o nome seja muito pequeno
                if(flag == 0){
                    gotoxy(18,14);
                    printf("N%co precisa se preocupar, n%co vamos", 198, 198);
                    gotoxy(18, 15);
                    printf("rir do seu nome");
                    gotoxy(18,17);
                    printf("Que tal tentarmos de novo?");

                    flag = 2;
                } else {
                    // Caso anteriormente o jogador tenha digitado um nome grande demais
                    gotoxy(18,14);
                    printf("Bom, agora %c um pouco pequeno", 130);
                    gotoxy(18, 15);
                    printf("demais...");
                    gotoxy(18,17);
                    printf("Vamos tentar mais uma vez, ok?");
                }
            }

            getch();

            fflush(stdin);
            desenhaInicio();
        }
    } while(strlen(estado_atual->jogador.nome) > NOME_MAX || strlen(estado_atual->jogador.nome) < 1);
    
    // Caso o primeiro nome digitado tenha sido pequeno demais
    if(flag == 2){
        gotoxy(18,14);
        printf("Rah, que nome fe... Quer dizer,");
        gotoxy(18, 15);
        printf("que nome lindo, nossa...");
        gotoxy(15,18);
        printf("   Erhnn... Que tal irmos pro jogo?");
        gotoxy(18,18);

        getch();
    }
}

/* Tela dos slots de save */
int selecionaSlot(SYSTEMTIME actual_time){
    Estado game_data;

    int option = 1;
    int flag = 0;
    char tecla;

    clrscr();
    desenhaInterface();

    desenhaSlots(game_data);
    desenhaSetas(option, game_data);

    do {
        tecla = getch();

        switch(tecla){
            // Cima
            case 72:
                apagaSetas(option, game_data);

                if(option == 1){
                    option = 3;
                } else {
                    option --;
                }

                desenhaSetas(option, game_data);

                break;
            // Baixo
            case 80:
                apagaSetas(option, game_data);

                if(option == 3){
                    option = 1;
                } else {
                    option ++;
                }

                desenhaSetas(option, game_data);
                break;
            // Enter
            case 13:
                flag = 1;
                break;
        }
    } while(flag == 0);

    return option;
}


/* ----------// Obtencao de coordenadas //---------- */
void localizaPosicoes(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual) {
    int i, j, k = 0, l = 0;

    for (j = 0; j < COLUNAS_MAPA; j++) {
        for (i = 0; i < LINHAS_MAPA; i++) {
            // Verifica qual o caractere contido na posição (i, j) da matriz
            switch(mapa[i][j]){
                // Rato
                case 'M':
                    estado_atual->jogador.pos_inicial.x = j;
                    estado_atual->jogador.pos_inicial.y = i;

                    estado_atual->jogador.pos_atual.x = j;
                    estado_atual->jogador.pos_atual.y = i;

                    break;
                // Gato
                case 'G':
                    estado_atual->gato[k].pos_inicial.x = j;
                    estado_atual->gato[k].pos_inicial.y = i;

                    estado_atual->gato[k].pos_atual.x = j;
                    estado_atual->gato[k].pos_atual.y = i;

                    k++;

                    break;
                // Queijo
                case 'Q':
                    estado_atual->jogador.qtd_queijos++;

                    break;
                // Porta
                case 'T':
                    estado_atual->porta[l].pos_porta.x = j;
                    estado_atual->porta[l].pos_porta.y = i;

                    l++;

                    break;
            }
        }
    }
}


/* ----------// Outras funcoes //---------- */
/* Remove o cursor da tela */
void removeCursor(){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
   
    info.dwSize = 100;
    info.bVisible = FALSE;
   
    SetConsoleCursorInfo(consoleHandle, &info);
}


/* Gera um numero aleatorio de 0 a 3 */
int geraNumero(){
    srand(time(NULL));
    int num;

    num = (rand() % 4);

    return num;
}


/* Verifica se a pontuacao obtida esta entre as 10 melhores e salva em caso positivo */
int atualizaVetor(Save ranking[MAX_SAVES], Jogador last_win){
    int flag = 0;

    if(last_win.pontuacao >= ranking[MAX_SAVES - 1].score){
        strcpy(ranking[MAX_SAVES - 1].nome, last_win.nome);
        ranking[MAX_SAVES - 1].score = last_win.pontuacao;

        flag = 1;
    }

    return flag;
}


/* Ordena um vetor em ordem crescente */
void ordenaVetor(Save vetor[MAX_SAVES]){
    Save auxiliar;
    int i = 0;

    do{
        if(vetor[MAX_SAVES - 1].score >= vetor[i].score){
            strcpy(auxiliar.nome, vetor[i].nome);
            auxiliar.score = vetor[i].score;

            strcpy(vetor[i].nome, vetor[MAX_SAVES - 1].nome);
            vetor[i].score = vetor[MAX_SAVES - 1].score;

            strcpy(vetor[MAX_SAVES - 1].nome, auxiliar.nome);
            vetor[MAX_SAVES - 1].score = auxiliar.score;
        }

        i++;
    } while(i < MAX_SAVES - 1);
}
