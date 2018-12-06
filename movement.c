#include "functions.h"

// Movimenta o rato
void mexeRato(char mapa[LINHAS_MAPA][COLUNAS_MAPA], int x, int y, clock_t *tempo_inicial, Estado *estado_atual) {
    int k;

    // Verifica se nao havera sobreposicao com a parede ou a porta
    if (mapa[estado_atual->jogador.pos_atual.y + y][estado_atual->jogador.pos_atual.x + x] != 'X' && mapa[estado_atual->jogador.pos_atual.y + y][estado_atual->jogador.pos_atual.x + x] != 'T') {
        // Casos possiveis de sobreposição
        switch(mapa[estado_atual->jogador.pos_atual.y + y][estado_atual->jogador.pos_atual.x + x]){
            // Queijo
            case 'Q':
                (estado_atual->jogador.pontuacao) += 10;
                estado_atual->jogador.qtd_queijos--;
                break;
            // Osso
            case 'O':
                (estado_atual->jogador.ossos_restantes)--;
                *tempo_inicial = clock();
                estado_atual->jogador.status_cachorro = 1;

                Beep(750, 300);

                break;
            // Gato
            case 'G':
                if(estado_atual->jogador.status_cachorro == 1){
                    estado_atual->jogador.pontuacao += 50;

                    Beep(200, 300);
                } else {
                    Beep(650, 150);
                    Beep(400, 200);
                }
        }

        // Salva um caractere vazio na matriz na posicao atual do rato
        mapa[estado_atual->jogador.pos_atual.y][estado_atual->jogador.pos_atual.x] = ' ';

        if(mapa[estado_atual->jogador.pos_atual.y + y][estado_atual->jogador.pos_atual.x + x] == 'G'){
            // Verifica se o modo cachorro esta ativado
            if (estado_atual->jogador.status_cachorro == 0) {

                mapa[estado_atual->jogador.pos_atual.y][estado_atual->jogador.pos_atual.x] = ' ';

                for(k = 0; k < NUM_GATOS; k++){
                    if(estado_atual->gato[k].pos_atual.x == (estado_atual->jogador.pos_atual.x + x) && estado_atual->gato[k].pos_atual.y == (estado_atual->jogador.pos_atual.y + y)){
                        mapa[estado_atual->gato[k].pos_atual.y][estado_atual->gato[k].pos_atual.x] = ' ';

                        estado_atual->gato[k].pos_atual.x = estado_atual->gato[k].pos_inicial.x;
                        estado_atual->gato[k].pos_atual.y = estado_atual->gato[k].pos_inicial.y;

                        mapa[estado_atual->gato[k].pos_atual.y][estado_atual->gato[k].pos_atual.x] = 'G';
                    }
                }

                estado_atual->jogador.pos_atual.x = estado_atual->jogador.pos_inicial.x;
                estado_atual->jogador.pos_atual.y = estado_atual->jogador.pos_inicial.y;

                mapa[estado_atual->jogador.pos_atual.y][estado_atual->jogador.pos_atual.x] = 'M';

            } else if (estado_atual->jogador.status_cachorro == 1) {
                for(k = 0; k < NUM_GATOS; k++){
                    if(estado_atual->gato[k].pos_atual.x == (estado_atual->jogador.pos_atual.x + x) && estado_atual->gato[k].pos_atual.y == (estado_atual->jogador.pos_atual.y + y)){
                        mapa[estado_atual->gato[k].pos_atual.y][estado_atual->gato[k].pos_atual.x] = ' ';

                        estado_atual->gato[k].pos_atual.x = estado_atual->gato[k].pos_inicial.x;
                        estado_atual->gato[k].pos_atual.y = estado_atual->gato[k].pos_inicial.y;

                        mapa[estado_atual->gato[k].pos_atual.y][estado_atual->gato[k].pos_atual.x] = 'G';
                    }
                }

                estado_atual->jogador.pos_atual.x += x;
                estado_atual->jogador.pos_atual.y += y;
            }
        } else {
            // Atualiza a nova posicao do rato
            estado_atual->jogador.pos_atual.x += x;
            estado_atual->jogador.pos_atual.y += y;
        }

        // Atualiza a matriz com o rato na nova posicao
        mapa[estado_atual->jogador.pos_atual.y][estado_atual->jogador.pos_atual.x] = 'M';
    }
}

// Movimenta os gatos
void mexeGato(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual){
    int x, y, k;

   for(k = 0; k < NUM_GATOS; k++){
        // Caso o gato tenha colidido com uma parede, porta ou outro gato
        if(estado_atual->gato[k].flag == 1){
                estado_atual->gato[k].direcao = geraNumero(); // Gera um numero aletaroio de 0 a 3
                estado_atual->gato[k].flag = 0;
        }

        // A partir do numero gerado, define-se uma direcao para o gato
        switch(estado_atual->gato[k].direcao){
                case 0:
                    x = 1;
                    y = 0;
                    break;
                case 1:
                    x = -1;
                    y =  0;
                    break;
                case 2:
                    x = 0;
                    y = 1;
                    break;
                case 3:
                    x =  0;
                    y = -1;
                    break;
            }

        //Checa se o tempo para mover o gato ja foi atingido
        if(((double)(clock() - estado_atual->gato[k].last_time)/CLOCKS_PER_SEC*1000) >= TEMPO_MG){
            // Verifica se o gato colidiu com uma parede, porta ou outro gato
            if(mapa[estado_atual->gato[k].pos_atual.y + y][estado_atual->gato[k].pos_atual.x + x] == 'X' || mapa[estado_atual->gato[k].pos_atual.y + y][estado_atual->gato[k].pos_atual.x + x] == 'T' || mapa[estado_atual->gato[k].pos_atual.y + y][estado_atual->gato[k].pos_atual.x + x] == 'G'){
                estado_atual->gato[k].flag = 1;
            } else {
                // Verifica flag de sobreposição do gato
                switch(estado_atual->gato[k].comeu_queijo){
                    // Verifica se o gato havia se sobreposto a um queijo
                    case 1:
                        estado_atual->gato[k].comeu_queijo = 0;
                        mapa[estado_atual->gato[k].pos_atual.y][estado_atual->gato[k].pos_atual.x] = 'Q';
                        break;
                    // Verifica se o gato havia se sobreposto a um qosso
                    case 2:
                        estado_atual->gato[k].comeu_queijo = 0;
                        mapa[estado_atual->gato[k].pos_atual.y][estado_atual->gato[k].pos_atual.x] = 'O';
                        break;
                    default:
                        mapa[estado_atual->gato[k].pos_atual.y][estado_atual->gato[k].pos_atual.x] = ' ';
                }

                // Verifica possiveis sobreposicoes
                switch(mapa[estado_atual->gato[k].pos_atual.y + y][estado_atual->gato[k].pos_atual.x + x]){
                    // Queijo
                    case 'Q':
                        estado_atual->gato[k].comeu_queijo = 1;
                        break;
                    // Osso
                    case 'O':
                        estado_atual->gato[k].comeu_queijo = 2;
                        break;
                    // Rato
                    case 'M':
                        // Verifica se o modo cachorro está ativado
                        if (estado_atual->jogador.status_cachorro == 0) {
                            mapa[estado_atual->gato[k].pos_atual.y][estado_atual->gato[k].pos_atual.x] = ' ';

                            estado_atual->gato[k].pos_atual.x = estado_atual->gato[k].pos_inicial.x;
                            estado_atual->gato[k].pos_atual.y = estado_atual->gato[k].pos_inicial.y;

                            estado_atual->jogador.vidas --;


                            mapa[estado_atual->jogador.pos_atual.y][estado_atual->jogador.pos_atual.x] = ' ';

                            estado_atual->jogador.pos_atual.x = estado_atual->jogador.pos_inicial.x;
                            estado_atual->jogador.pos_atual.y = estado_atual->jogador.pos_inicial.y;

                            mapa[estado_atual->jogador.pos_atual.y][estado_atual->jogador.pos_atual.x] = 'M';

                        } else if (estado_atual->jogador.status_cachorro == 1) {
                            mapa[estado_atual->gato[k].pos_atual.y][estado_atual->gato[k].pos_atual.x] = ' ';

                            estado_atual->gato[k].pos_atual.x = estado_atual->gato[k].pos_inicial.x;
                            estado_atual->gato[k].pos_atual.y = estado_atual->gato[k].pos_inicial.y;
                        }
                        break;
                }

                // Atualiza a nova posicao do gato
                estado_atual->gato[k].pos_atual.x += x;
                estado_atual->gato[k].pos_atual.y += y;

                // Atualiza a matriz com a nova posicao do gato
                mapa[estado_atual->gato[k].pos_atual.y][estado_atual->gato[k].pos_atual.x] = 'G';
            }

            // Atualiza o ultimo horario de movimentacao do gato
            estado_atual->gato[k].last_time = clock();
        }
    }
}

// Movimenta as portas
void mexePorta(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual, int *status_portas) {
    int l, c, k;

    // Verifica se as postas se encontram no estado abertas ou fechadas
    if (estado_atual->status_portas == 0) {
        for(k = NUM_PORTAS - 1; k >= 0; k--){
            if(mapa[estado_atual->porta[k].pos_porta.y + 1][estado_atual->porta[k].pos_porta.x + 1] != 'G' && mapa[estado_atual->porta[k].pos_porta.y + 1][estado_atual->porta[k].pos_porta.x + 1] != 'M'){
                mapa[estado_atual->porta[k].pos_porta.y][estado_atual->porta[k].pos_porta.x] = ' ';

                estado_atual->porta[k].pos_porta.x++;
                estado_atual->porta[k].pos_porta.y++;

                mapa[estado_atual->porta[k].pos_porta.y][estado_atual->porta[k].pos_porta.x] = 'T';
            }
        }

        // Atualiza o novo estado da porta
        estado_atual->status_portas = 1;
    } else {
        for(k = 0; k < NUM_PORTAS; k++){
            if(mapa[estado_atual->porta[k].pos_porta.y - 1][estado_atual->porta[k].pos_porta.x - 1] != 'G' && mapa[estado_atual->porta[k].pos_porta.y - 1][estado_atual->porta[k].pos_porta.x - 1] != 'M'){
              mapa[estado_atual->porta[k].pos_porta.y][estado_atual->porta[k].pos_porta.x] = ' ';

                estado_atual->porta[k].pos_porta.x--;
                estado_atual->porta[k].pos_porta.y--;

                mapa[estado_atual->porta[k].pos_porta.y][estado_atual->porta[k].pos_porta.x] = 'T';
            }
        }

        // Atualiza o novo estado da porta
        estado_atual->status_portas = 0;
    }
}
