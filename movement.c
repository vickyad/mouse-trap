#include "functions.h"

/* Movimenta o rato */
void mexeRato(char mapa[LINHAS_MAPA][COLUNAS_MAPA], int x, int y, clock_t *tempo_inicial, Estado *estado_atual) {
    int k;

    // Verifica se nao havera sobreposicao com a parede ou a porta
    if (mapa[estado_atual->jogador.pos_atual.y + y][estado_atual->jogador.pos_atual.x + x] != 'X' && mapa[estado_atual->jogador.pos_atual.y + y][estado_atual->jogador.pos_atual.x + x] != 'T') {
        // Casos possiveis de sobreposicao
        switch(mapa[estado_atual->jogador.pos_atual.y + y][estado_atual->jogador.pos_atual.x + x]){
            // Queijo
            case 'Q':
                (estado_atual->jogador.pontuacao) += 10;
                estado_atual->jogador.qtd_queijos--;
                break;
            // Osso
            case 'O':
                (estado_atual->jogador.ossos_restantes)--;

                // Ativa o modo cachorro
                *tempo_inicial = clock();
                estado_atual->jogador.status_cachorro = 1;

                // Efeito sonoro
                Beep(750, 300);

                break;
            // Gato
            case 'G':
                if(estado_atual->jogador.status_cachorro == 1){
                    estado_atual->jogador.pontuacao += 50;

                    // Efeito sonoro
                    Beep(200, 300);
                } else {
                    // Efeito sonoro
                    Beep(650, 150);
                    Beep(400, 200);
                }
        }

        // Salva um caractere vazio na matriz na posicao atual do rato
        mapa[estado_atual->jogador.pos_atual.y][estado_atual->jogador.pos_atual.x] = ' ';

        if(mapa[estado_atual->jogador.pos_atual.y + y][estado_atual->jogador.pos_atual.x + x] == 'G'){
            // Verifica se o modo cachorro esta ativado
            if (estado_atual->jogador.status_cachorro == 0) {
                // Verifica qual gato colidiu com o rato
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
                // Verifica qual gato colidiu com o rato
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


/* Movimenta os gatos */ 
void mexeGato(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual){
    int x = 0, y = 0, k;
    int dis_menor;

   for(k = 0; k < NUM_GATOS; k++){
        dis_menor = disPontos(estado_atual->jogador.pos_atual.x, estado_atual->jogador.pos_atual.y, estado_atual->gato[k].pos_atual.x, estado_atual->gato[k].pos_atual.y);

        if(disPontos(estado_atual->jogador.pos_atual.x, estado_atual->jogador.pos_atual.y, (estado_atual->gato[k].pos_atual.x + 1), estado_atual->gato[k].pos_atual.y) < dis_menor){
            x = 1;
            y = 0;
        } else {
            if(disPontos(estado_atual->jogador.pos_atual.x, estado_atual->jogador.pos_atual.y, (estado_atual->gato[k].pos_atual.x - 1), estado_atual->gato[k].pos_atual.y) < dis_menor){
                x = -1;
                y = 0;
            } else {
                if(disPontos(estado_atual->jogador.pos_atual.x, estado_atual->jogador.pos_atual.y, estado_atual->gato[k].pos_atual.x, (estado_atual->gato[k].pos_atual.y + 1)) < dis_menor){
                    x = 0;
                    y = 1;
                } else {
                    if(disPontos(estado_atual->jogador.pos_atual.x, estado_atual->jogador.pos_atual.y, estado_atual->gato[k].pos_atual.x, (estado_atual->gato[k].pos_atual.y - 1)) < dis_menor){
                        x = 0;
                        y = -1;
                    } else {
                        if(pow((estado_atual->jogador.pos_atual.x - (estado_atual->gato[k].pos_atual.x + 1)),2) < pow((estado_atual->jogador.pos_atual.x - estado_atual->gato[k].pos_atual.x),2)){
                            x = 1;
                            y = 0;
                        } else {
                            if(pow((estado_atual->jogador.pos_atual.x - (estado_atual->gato[k].pos_atual.x - 1)),2) < pow((estado_atual->jogador.pos_atual.x - estado_atual->gato[k].pos_atual.x),2)){
                                x = -1;
                                y = 0;
                            } else {
                                if(pow((estado_atual->jogador.pos_atual.y - (estado_atual->gato[k].pos_atual.y + 1)),2) < pow((estado_atual->jogador.pos_atual.y - estado_atual->gato[k].pos_atual.y),2)){
                                    x = 0;
                                    y = 1;
                                } else {
                                    if(pow((estado_atual->jogador.pos_atual.y - (estado_atual->gato[k].pos_atual.y - 1)),2) < pow((estado_atual->jogador.pos_atual.y - estado_atual->gato[k].pos_atual.y),2)){
                                        x = 0;
                                        y = -1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //Checa se o tempo para mover o gato ja foi atingido
        if(((double)(clock() - estado_atual->gato[k].last_time)/CLOCKS_PER_SEC*1000) >= TEMPO_MG){
            // Verifica se o gato colidiu com uma parede, porta ou outro gato
            if(mapa[estado_atual->gato[k].pos_atual.y + y][estado_atual->gato[k].pos_atual.x + x] != 'X' && mapa[estado_atual->gato[k].pos_atual.y + y][estado_atual->gato[k].pos_atual.x + x] != 'T' && mapa[estado_atual->gato[k].pos_atual.y + y][estado_atual->gato[k].pos_atual.x + x] != 'G'){
                // Verifica flag de sobreposicao do gato
                switch(estado_atual->gato[k].comeu_queijo){
                    // Verifica se o gato havia se sobreposto a um queijo
                    case 1:
                        estado_atual->gato[k].comeu_queijo = 0;
                        mapa[estado_atual->gato[k].pos_atual.y][estado_atual->gato[k].pos_atual.x] = 'Q';
                        break;
                    // Verifica se o gato havia se sobreposto a um osso
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
                        // Verifica se o modo cachorro esta ativado
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

/* Movimenta as portas */
void mexePorta(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual, int *status_portas) {
    int k;

    // Verifica se as postas se encontram no estado abertas ou fechadas
    if (estado_atual->status_portas == 0) {
        for(k = NUM_PORTAS - 1; k >= 0; k--){
            if(mapa[estado_atual->porta[k].pos_porta.y + 1][estado_atual->porta[k].pos_porta.x + 1] != 'G' && mapa[estado_atual->porta[k].pos_porta.y + 1][estado_atual->porta[k].pos_porta.x + 1] != 'M' && estado_atual->porta[k].flag == 0){
                mapa[estado_atual->porta[k].pos_porta.y][estado_atual->porta[k].pos_porta.x] = ' ';

                estado_atual->porta[k].pos_porta.x++;
                estado_atual->porta[k].pos_porta.y++;

                mapa[estado_atual->porta[k].pos_porta.y][estado_atual->porta[k].pos_porta.x] = 'T';
            } else{
                if(estado_atual->porta[k].flag == 0){
                    estado_atual->porta[k].flag = 1;
                } else {
                   estado_atual->porta[k].flag = 0;
                }
            }
        }

        // Atualiza o novo estado da porta
        estado_atual->status_portas = 1;
    } else {
        for(k = 0; k < NUM_PORTAS; k++){
            if(mapa[estado_atual->porta[k].pos_porta.y - 1][estado_atual->porta[k].pos_porta.x - 1] != 'G' && mapa[estado_atual->porta[k].pos_porta.y - 1][estado_atual->porta[k].pos_porta.x - 1] != 'M' && estado_atual->porta[k].flag == 0){
              mapa[estado_atual->porta[k].pos_porta.y][estado_atual->porta[k].pos_porta.x] = ' ';

                estado_atual->porta[k].pos_porta.x--;
                estado_atual->porta[k].pos_porta.y--;

                mapa[estado_atual->porta[k].pos_porta.y][estado_atual->porta[k].pos_porta.x] = 'T';
            } else {
                if(estado_atual->porta[k].flag == 0){
                    estado_atual->porta[k].flag = 1;
                } else {
                   estado_atual->porta[k].flag = 0;
                }
            }
        }

        // Atualiza o novo estado da porta
        estado_atual->status_portas = 0;
    }
}
