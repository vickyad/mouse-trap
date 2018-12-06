// Victoria de Avelar Duarte e Henrique Werner Delazeri

/* O programa é um jogo inspirado no jogo de Atari Mouse Trap*/


#include "functions.h"

// Main
int main() {
    // Declaração de variáveis
    Estado estado_atual = {{"", {0, 0}, {0, 0}, 0, NUM_VIDAS, 0, NUM_OSSOS, 0},
                          {{0,0}, {0,0}, 0, 1, 0, 0, {0,0}, {0,0}, 0, 1, 0, 0, {0,0}, {0,0}, 0, 1, 0, 0, {0,0}, {0,0}, 0, 1, 0, 0},
                          {{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}},
                          1, 0};

    char mapa[LINHAS_MAPA][COLUNAS_MAPA];

    int status_pause = 0;
    int status_passou_nivel = 1;
    int novo_jogo = 1;

    char char_nivel[NOME_ARQUIVO];

    char tecla_press;
    char resp, resp_aux;
    int i, j, k;

    clock_t tempo_inicial, tempo_decorrido;


    // Deixa a janela de um tamanho especifico
    system("mode 105,30");

    // Remove o cursor da janela
    removeCursor();

    //Loop do jogo
    do {
        // Menu inicial do jogo
        if(novo_jogo == 1){
            inicio(&estado_atual);
            desenhaInstrucoes();

            novo_jogo = 0;
        }

        // Avalia e seta status do jogador
        if(status_passou_nivel == 1 || resp == 'S'){
            if(resp == 'S'){
                estado_atual.nivel = 1;
                estado_atual.jogador.pontuacao = 0;

                resp = ' ';
            }

            // Reseta variáveis necessárias
            estado_atual.jogador.vidas = NUM_VIDAS;
            estado_atual.jogador.ossos_restantes = NUM_OSSOS;
            estado_atual.jogador.status_cachorro = 0;

            estado_atual.status_portas = 0;


            // Abre o mapa de acordo com o nivel e localiza o rato, os gatos e as portas na matriz
            pegaMapa(mapa, estado_atual.nivel);

            localizaPosicoes(mapa, &estado_atual);


            // Desenha a interface principal do jogo
            clrscr();
            desenhaInterface();
            desenhaMapa(mapa, estado_atual);
            desenhaInfo(estado_atual);

            status_passou_nivel = 0;
        }

        // Teste se já chegou ao fim do jogo
        if(estado_atual.nivel == 4){
            desenhaVitoria();

            atualizaRanking(estado_atual.jogador);

            return 0;
        }

        if(status_pause == 0){
            // Garante que os gatos só se movam caso o jogo não esteja pausado
            mexeGato(mapa, &estado_atual);
            desenhaMapa(mapa, estado_atual); // desenha o mapa após cada movimento dos gatos
        }

        // Controla o tempo que o rato fica no modo cachorro
        if(estado_atual.jogador.status_cachorro == 1){
            tempo_decorrido = (double)(clock() - tempo_inicial)/CLOCKS_PER_SEC*1000;

            if(tempo_decorrido >= TEMPO_MC){
                estado_atual.jogador.status_cachorro = 0;
                desenhaInfo(estado_atual);
            }
        }

        if (kbhit()) {
            // Movimentacaoo do jogador
            tecla_press = toupper(getch()); // Pega a tecla pressionada pelo jogador

            switch (tecla_press) {
                // Direita
                case 68:
                    if(status_pause == 0){
                        mexeRato(mapa, 1, 0, &tempo_inicial, &estado_atual);
                        desenhaMapa(mapa, estado_atual);
                        desenhaInfo(estado_atual);
                    }
                    break;
                // Esquerda
                case 65:
                    if(status_pause == 0){
                        mexeRato(mapa, -1, 0, &tempo_inicial, &estado_atual);
                        desenhaMapa(mapa, estado_atual);
                        desenhaInfo(estado_atual);
                    }
                    break;
                // Cima
                case 87:
                    if(status_pause == 0){
                        mexeRato(mapa, 0, -1, &tempo_inicial, &estado_atual);
                        desenhaMapa(mapa, estado_atual);
                        desenhaInfo(estado_atual);
                    }
                    break;
                // Baixo
                case 83:
                    if(status_pause == 0){
                        mexeRato(mapa, 0, 1, &tempo_inicial,  &estado_atual);
                        desenhaMapa(mapa, estado_atual);
                        desenhaInfo(estado_atual);
                    }
                    break;
                // Movimenta as portas
                case 66:
                    // Garante que as portas so se movimentem se o jogo não estiver pausado
                    if(status_pause == 0){
                        mexePorta(mapa, &estado_atual, &estado_atual.status_portas);
                        desenhaMapa(mapa, estado_atual);
                        desenhaInfo(estado_atual);
                    }
                    break;
                //Pausa o jogo
                case 9:
                    if(status_pause == 0){
                        clrscr();
                        desenhaInterface();
                        desenhaInfo(estado_atual);
                        desenhaPause();

                        Beep(600,150);

                        status_pause = 1;
                    } else {
                        desenhaMapa(mapa, estado_atual);
                        desenhaInfo(estado_atual);

                        Beep(600,150);

                        status_pause = 0;
                    }
                    break;

                //Novo jogo
                case 78:
                    desenhaRetangulo();

                    // Confere se o jogador realmente quer iniciar um novo jogo
                    do{
                        gotoxy(18,15);
                        printf("Deseja iniciar um novo jogo?");
                        gotoxy(18,17);
                        printf("(S) - Sim   (N) - N%co", 198);
                        gotoxy(18,18);
                        resp = toupper(getch());

                        if(resp != 'S' && resp != 'N'){
                            printf("Resposta inv%clida", 160);
                        }
                    } while(resp != 'S' && resp != 'N');

                    if(resp == 'S'){
                        novo_jogo = 1;
                    } else {
                        desenhaMapa(mapa, estado_atual);
                    }

                    break;
                //Salva jogo
                case 75:
                    salvaJogo(mapa, estado_atual);

                    // Verifica se o jogador deseja continuar no jogo atual
                    do{
                        //desenhaRetangulo();
                        gotoxy(18,15);
                        printf("Deseja voltar ao jogo?              ");
                        gotoxy(18,17);
                        printf("(S) - Sim   (N) - N%co", 198);
                        gotoxy(18,18);
                        resp_aux = toupper(getch());

                        if(resp_aux != 'S' && resp_aux != 'N'){
                            gotoxy(18,18);
                            printf("Resposta inv%clida", 160);
                        }
                    } while(resp_aux != 'S' && resp_aux != 'N');

                    if(resp_aux == 'N'){
                        resp = 'S';
                        novo_jogo = 1;
                    } else {
                        desenhaMapa(mapa, estado_atual);
                    }
                    break;
                // Carrega jogo
                case 76:
                    carregaJogo(mapa, &estado_atual);

                    status_pause = 0;
                    estado_atual.jogador.status_cachorro = 0;

                    localizaPosicoes(mapa, &estado_atual);
                    clrscr();
                    desenhaInterface();
                    desenhaMapa(mapa, estado_atual);
                    desenhaInfo(estado_atual);
                    break;
            }
        }

        // Verifica condição de vitoria do jogo (quantidade de queijos = 0)
        if(estado_atual.jogador.qtd_queijos == 0){
            status_passou_nivel = 1;
            estado_atual.nivel++;

            desenhaPassaNivel();

            Sleep(2000);
        }

        // Verifica condição de derrota do jogador (vidas = 0)
        if(estado_atual.jogador.vidas == 0){
            estado_atual.jogador.vidas = NUM_VIDAS;

            desenhaDerrota();

            desenhaRetangulo();

            // Verifica se o jogador deseja iniciar um novo jogo ou não
            do{
                gotoxy(18,15);
                printf("Deseja tentar novamente?");
                gotoxy(18,17);
                printf("(S) - Sim   (N) - N%co", 198);
                gotoxy(18,17);
                resp = toupper(getch());

                if(resp != 'S' && resp != 'N'){
                    gotoxy(18,18);
                    printf("Resposta inv%clida", 160);
                }
            } while(resp != 'S' && resp != 'N');

            if(resp == 'S'){
                novo_jogo = 1;
            } else {
                return 0;
            }
        }
    } while (tecla_press != 27); // Fim do loop do jogo

    return 0;
}
