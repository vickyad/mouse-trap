#include "functions.h"

/* Desenham elementos individualmente */
// Rato
void desenhaRato(int x, int y) {
    textcolor(WHITE);
    textbackground(DARKGRAY);

    gotoxy(x, y);
    cprintf("%c%c", 64, 64);
    gotoxy(x, y + 1);
    cprintf("uu");
}

// Cachorro
void desenhaCachorro(int x, int y){
    textcolor(WHITE);
    textbackground(RED);

    gotoxy(x, y);
    cprintf("U ");
    gotoxy(x, y + 1);
    cprintf("uu");
}

// Gato
void desenhaGato(int x, int y) {
    textbackground(WHITE);
    textcolor(BLACK);

    gotoxy(x, y);
    cprintf("^^");
    gotoxy(x, y + 1);
    cprintf("uu");
}

// Queijo
void desenhaQueijo(int x, int y) {
    textbackground(BLACK);
    textcolor(YELLOW);

    gotoxy(x, y);
    cprintf("  ");
    gotoxy(x, y + 1);
    cprintf(" .");
}

// Osso
void desenhaOsso(int x, int y) {
    textbackground(BLACK);
    textcolor(YELLOW);

    gotoxy(x, y);
    cprintf("\\/");
    gotoxy(x, y + 1);
    cprintf("/\\");
}

// Porta
void desenhaPorta(int x, int y) {
    textbackground(LIGHTGREEN);

    gotoxy(x, y);
    cprintf("  ");
    gotoxy(x, y + 1);
    cprintf("  ");
}

// Parede
void desenhaParede(int x, int y) {
    textbackground(GREEN);

    gotoxy(x, y);
    cprintf("  ");
    gotoxy(x, y + 1);
    cprintf("  ");
}


/* Desenha o mapa a partir da matriz */
void desenhaMapa(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado estado_atual) {
    int x = 7;
    int y = 7;

    int l, c;
    for (l = 0; l < LINHAS_MAPA; l++) {
        x = 7;

        for (c = 0; c < COLUNAS_MAPA; c++) {
            // Verifica qual o char encontrado para imprimi-lo na cor correspondente
            switch (mapa[l][c]) {
                // Rato
                case 'M':
                    // Verifica se o status cachorro está ativado
                    if(estado_atual.jogador.status_cachorro == 1){
                        desenhaCachorro(x, y);
                    } else {
                        desenhaRato(x, y);
                    }
                    break;
                // Gato
                case 'G':
                    desenhaGato(x, y);
                    break;
                // Queijo
                case 'Q':
                    desenhaQueijo(x, y);
                    break;
                // Osso
                case 'O':
                    desenhaOsso(x, y);
                    break;
                // Porta
                case 'T':
                    desenhaPorta(x, y);
                    break;
                // Parede
                case 'X':
                    desenhaParede(x, y);
                    break;
                default:
                    textbackground(BLACK);
                    textcolor(WHITE);
                    gotoxy(x, y);
                    printf("  ");
                    gotoxy(x, y + 1);
                    printf("  ");
            }

            x += 2;
        }

        y += 2;
    }

    // Retorna as cores default
    textbackground(BLACK);
    textcolor(WHITE);
}


/* Desenha retangulo que contem mensagens ao jogador */
void desenhaRetangulo(){
    int i, j;
    int x = 14, y = 11;

    textbackground(YELLOW);

    for(j = 0; j <= LINHAS_INTERFACE_RETANG; j++){
        if(j == 0 || j == LINHAS_INTERFACE_RETANG){
            for(i = 0; i <= COLUNAS_INTERFACE_RETANG; i++){
                gotoxy(i + 14, j + 11);
                printf(" ");
            }
        } else {
            gotoxy(14, j + 11);
            printf(" ");

            gotoxy(COLUNAS_INTERFACE_RETANG + 14, j + 11);
            printf(" ");
        }
    }

    // Retorna as cores default
    textbackground(BLACK);
    textcolor(WHITE);
}


/* Desenha esqueleto da interface principal */
void desenhaInterface() {
    int i, j;

    // Desenho da borda
    gotoxy(0, 0);

    for (i = 0; i < COLUNAS_TERMINAL; i++) {
        textbackground(LIGHTBLUE);
        cprintf(" ");
    }

    printf("\n");

    for (j = 0; j < 3; j++) {
        for (i = 0; i < COLUNAS_TERMINAL; i++) {
            if (i % 21 == 0 || i == COLUNAS_TERMINAL - 1) {
                textbackground(LIGHTBLUE);
                cprintf(" ");
            } else {
                textbackground(BLACK);
                cprintf(" ");
            }
        }

        printf("\n");
    }

    for (i = 0; i < COLUNAS_TERMINAL; i++) {
        gotoxy(0, 0);
        textbackground(LIGHTBLUE);
        cprintf(" ");
    }

    printf("\n");

    for (i = 0; i < LINHAS_TERMINAL - 6; i++) {
        for (j = 0; j < COLUNAS_TERMINAL; j++) {
            if (j == 0 || j == 69 || j == 104) {
                textbackground(LIGHTBLUE);
            } else {
                textbackground(BLACK);
            }

            cprintf(" ");
        }

        printf("\n");
    }

    for (i = 0; i < COLUNAS_TERMINAL; i++) {
        textbackground(LIGHTBLUE);
        cprintf(" ");
    }

    // Desenho das opcoes do menu
    textbackground(BLACK);
    gotoxy(5, 3);
    printf("[N] Novo Jogo");

    gotoxy(24, 3);
    printf("[L] Carregar Jogo");

    gotoxy(46, 3);
    printf("[K] Salvar Jogo");

    gotoxy(69, 3);
    printf("[TAB] Pausar");

    gotoxy(90, 3);
    printf("[ESC] Sair");
}


/* Desenha as informações do jogador */
void desenhaInfo(Estado estado_atual){
    gotoxy(72, 10);
    printf("Jogador: %s", estado_atual.jogador.nome);

    gotoxy(72, 13);
    printf("Pontua%c%co: %d", 135, 198, estado_atual.jogador.pontuacao);

    gotoxy(72, 16);
    printf("N%cvel: %d", 161, estado_atual.nivel);

    gotoxy(72, 19);
    printf("%d vidas restantes", estado_atual.jogador.vidas);

    gotoxy(72, 22);
    printf("%d ossos restantes", estado_atual.jogador.ossos_restantes);

    gotoxy(72, 24);
    // Caso o jogador esteja no modo cachorro, uma mensagem e printada na tela
    if(estado_atual.jogador.status_cachorro == 1){
        textcolor(LIGHTRED);
        printf("Au! Au!");
        textcolor(WHITE);
    } else {
        printf("                        ");
    }
}


/* Desenha a mensagem inicial do jogo */
void desenhaInicio() {
    desenhaRetangulo();

    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(25, 14);
    printf("BEM-VINDO AO");
    textcolor(LIGHTRED);
    gotoxy(38,14);
    printf("MOUSE TRAP");
    textcolor(WHITE);

    gotoxy(16, 18);
    printf("Insira o seu nome: ");
}


/* Desenha a interface de instruções */
void desenhaInstrucoes(){
    clrscr();
    desenhaInterface();

    // Mensagens
    gotoxy(32,7);
    printf("Instru%c%ces:", 135, 228);

    gotoxy(14,9);
    printf("Para se mover:");

    gotoxy(36,9);
    printf("Para mover as portas:");

    gotoxy(20,19);
    printf("Cuidado com os gatos!");

    gotoxy(25,24);
    printf("Boa sorte!");

    //Teclas
    gotoxy(19,10);
    printf("___");
    gotoxy(18,11);
    printf("| W |");
    gotoxy(15,12);
    printf("___|___|___");
    gotoxy(14,13);
    printf("| A | S | D |");
    gotoxy(14,14);
    printf("|___|___|___|");

    gotoxy(46,10);
    printf("___");
    gotoxy(45,11);
    printf("| B |");
    gotoxy(45,12);
    printf("|___|");

    // Rato
    gotoxy(6,18);
    printf("_   _");
    gotoxy(5,19);
    printf("(q\\_/p)");
    gotoxy(6,20);
    printf("/. .\\");
    gotoxy(5,21);
    printf("=\\_t_/=   _");
    gotoxy(6,22);
    printf("/   \\   (");
    gotoxy(5,23);
    printf("((   ))   )");
    gotoxy(5,24);
    printf("/\\) (/\\  /");
    gotoxy(5,25);
    printf("\\  Y  /-'");
    gotoxy(6,26);
    printf("nn%cnn", 94);

    // Gato
    gotoxy(52,17);
    printf("|\\._./|");
    gotoxy(51,18);
    printf("/       \\");
    gotoxy(50,19);
    printf("/ {|} {|} \\  _");
    gotoxy(50,20);
    printf("\\ == Y == / ( \\");
    gotoxy(51,21);
    printf(";-.-^-.-;   ) )");
    gotoxy(50,22);
    printf("/   ___   \\ / /");
    gotoxy(50,23);
    printf("|  (   )  |/ /");
    gotoxy(49,24);
    printf("/|  |   |  |\\/");
    gotoxy(48,25);
    printf("| |  |   |  | |");
    gotoxy(49,26);
    printf("\\|__|___|__|/");

    getch();
}


/* Desenha a mensagem de pause */
void desenhaPause() {
    desenhaRetangulo();

    textbackground(BLACK);
    gotoxy(29, 15);
    printf("Jogo Pausado");

    gotoxy(23, 16);
    printf("Pressione (TAB) para voltar");
}


/* Desenha a interface de conclusão de nivel */
void desenhaPassaNivel(){
    desenhaRetangulo();

    textbackground(BLACK);
    textcolor(WHITE);

    gotoxy(18, 15);
    printf("Parab%cns, voc%c passou de n%cvel!", 130, 136, 161);

    // Efeito sonoro
    Beep(800,150);
    Beep(600,150);
    Beep(300,150);
    Beep(200,250);
}


/* Desenha a interface dos slots */
void desenhaSlots(Estado game_data){
    FILE *arq;
    int i = 0, j = 0;

    textbackground(YELLOW);

    // Desenhas o contorno
    for(j = 0; j <= LINHAS_SLOTS; j++){
        if(j == 0 || j == 7 || j == 14 || j == LINHAS_SLOTS){
            for(i = 0; i <= COLUNAS_SLOTS; i++){
                gotoxy(i + 15, j + 7);
                printf(" ");
            }
        } else {
            gotoxy(15, j + 7);
            printf(" ");

            gotoxy(COLUNAS_SLOTS + 15, j + 7);
            printf(" ");
        }
    }

    textbackground(BLACK);

    // Informacoes jogo 1
    if(!(arq = fopen("Mousetrap_estado_atual1.bin", "r+b"))){
        gotoxy(19, 9);
        printf("SLOT VAZIO");
    } else {
        fread(&game_data, sizeof(Estado), 1, arq);

        gotoxy(19, 9);
        puts(game_data.jogador.nome);

        gotoxy(19, 10);
        printf("Nivel %d", game_data.nivel);

        gotoxy(19, 12);
        printf("%d/%d/%d - %dh%d", game_data.actual_time.wDay, game_data.actual_time.wMonth, game_data.actual_time.wYear, game_data.actual_time.wHour, game_data.actual_time.wMinute);

        fclose(arq);
    }

    // Informacoes jogo 2
    if(!(arq = fopen("Mousetrap_estado_atual2.bin", "r+b"))){
        gotoxy(19, 16);
        printf("SLOT VAZIO");
    } else {
        fread(&game_data, sizeof(Estado), 1, arq);

        gotoxy(19, 16);
        puts(game_data.jogador.nome);

        gotoxy(19, 17);
        printf("Nivel %d", game_data.nivel);

        gotoxy(19, 19);
        printf("%d/%d/%d - %dh%d", game_data.actual_time.wDay, game_data.actual_time.wMonth, game_data.actual_time.wYear, game_data.actual_time.wHour, game_data.actual_time.wMinute);

        fclose(arq);
    }

    // Informacoes jogo 3
    if(!(arq = fopen("Mousetrap_estado_atual3.bin", "r+b"))){
        gotoxy(19, 23);
        printf("SLOT VAZIO");
    } else {
        fread(&game_data, sizeof(Estado), 1, arq);

        gotoxy(19, 23);
        puts(game_data.jogador.nome);

        gotoxy(19, 24);
        printf("Nivel %d", game_data.nivel);

        gotoxy(19, 26);
        printf("%d/%d/%d - %dh%d", game_data.actual_time.wDay, game_data.actual_time.wMonth, game_data.actual_time.wYear, game_data.actual_time.wHour, game_data.actual_time.wMinute);

        fclose(arq);
    }
}


/* Desenha as setas na opcao potencial */
void desenhaSetas(int option, Estado game_data){
    textcolor(RED);
    switch(option){
        case 1:
            gotoxy(17, 9);
            printf(">");

            gotoxy(49, 9);
            printf("<");

            break;
        case 2:
            gotoxy(17, 16);
            printf(">");

            gotoxy(49, 16);
            printf("<");

            break;
        case 3:
            gotoxy(17, 23);
            printf(">");

            gotoxy(49, 23);
            printf("<");

            break;
    }

    textcolor(WHITE);
}


/* Apaga as setas da opcao anterior */
void apagaSetas(int option, Estado game_data){
    textbackground(BLACK);
    switch(option){
        case 1:
            gotoxy(17, 9);
            printf(" ");

            gotoxy(49, 9);
            printf(" ");

            break;
        case 2:
            gotoxy(17, 16);
            printf(" ");

            gotoxy(49, 16);
            printf(" ");

            break;
        case 3:
            gotoxy(17, 23);
            printf(" ");

            gotoxy(49, 23);
            printf(" ");

            break;
    }
}


/* Desenha a interface do ranking */
void desenha_ranking(Save ranking[MAX_SAVES]){
    int i = 0, j = 0;

    // Desenha o contorno
    textbackground(YELLOW);

    for(j = 0; j <= LINHAS_RANKING; j++){
        if(j == 0 || j == 4 || j == LINHAS_RANKING){
            for(i = 0; i <= COLUNAS_RANKING; i++){
                gotoxy(i + 18, j + 9);
                printf(" ");
            }
        } else {
            gotoxy(18, j + 9);
            printf(" ");

            gotoxy(COLUNAS_RANKING + 18, j + 9);
            printf(" ");
        }
    }

    textbackground(BLACK);

    // Escreve o titulo
    textcolor(RED);
    gotoxy(32, 11);
    printf("RANKING");

    textcolor(WHITE);

    // Escreve o nome dos jogadores
    for(i = 0; i < MAX_SAVES; i++){
        gotoxy(20, i + 15);
        printf("%20s     %6d\n", ranking[i].nome, ranking[i].score);
    }
}


// Desenha a interface de vitoria
void desenhaVitoria(){
    clrscr();

    desenhaInterface();

    // Fogo 1
    textcolor(YELLOW);
    gotoxy(12,8);
    printf("*''*");
    gotoxy(11,9);
    printf("*_\\/_*");
    gotoxy(11,10);
    printf("* /\\ *");
    gotoxy(12,11);
    printf("*..*");

    // Fogo 2
    textcolor(LIGHTGREEN);
    gotoxy(61,9);
    printf(":");
    gotoxy(59,10);
    printf(".\\'/.");
    gotoxy(57,11);
    printf("--= o =--");
    gotoxy(58,12);
    printf(".'/.\\'.");
    gotoxy(61,13);
    printf(":");

    // Fogo 3
    textcolor(LIGHTMAGENTA);
    gotoxy(4,17);
    printf(".''.");
    gotoxy(3,18);
    printf(":_\\/_:");
    gotoxy(3,19);
    printf(": /\\ :");
    gotoxy(4,20);
    printf("'..'");

    // Fogo 3
    textcolor(CYAN);
    gotoxy(14,22);
    printf(":");
    gotoxy(12,23);
    printf(".\\'/.");
    gotoxy(10,24);
    printf("--= o =--");
    gotoxy(11,25);
    printf(".'/.\\'.");
    gotoxy(14,26);
    printf(":");

    // Fogo 4
    textcolor(LIGHTRED);
    gotoxy(52,21);
    printf("*''*");
    gotoxy(51,22);
    printf("*_\\/_*");
    gotoxy(51,23);
    printf("* /\\ *");
    gotoxy(52,24);
    printf("*..*");

    // Mensagem
    textcolor(WHITE);
    gotoxy(21,15);
    printf("Parab%cns, voc%c concluiu o jogo!", 130, 136);
    gotoxy(26,18);
    printf("Obrigado por jogar");

    getch();
}


// Desenha a interface de derrota
void desenhaDerrota(){
    clrscr();
    desenhaInterface();

    textbackground(LIGHTRED);

    //G
    gotoxy(15,16);
    printf(" ");
    gotoxy(15,17);
    printf(" ");
    gotoxy(15,18);
    printf(" ");
    gotoxy(15,19);
    printf(" ");
    gotoxy(15,20);
    printf(" ");
    gotoxy(16,16);
    printf(" ");
    gotoxy(16,20);
    printf(" ");
    gotoxy(17,16);
    printf(" ");
    gotoxy(17,18);
    printf(" ");
    gotoxy(17,20);
    printf(" ");
    gotoxy(18,16);
    printf(" ");
    gotoxy(18,18);
    printf(" ");
    gotoxy(18,19);
    printf(" ");
    gotoxy(18,20);
    printf(" ");

    //A
    gotoxy(20, 16);
    printf(" ");
    gotoxy(20, 17);
    printf(" ");
    gotoxy(20, 18);
    printf(" ");
    gotoxy(20, 19);
    printf(" ");
    gotoxy(20, 20);
    printf(" ");
    gotoxy(21, 16);
    printf(" ");
    gotoxy(21, 18);
    printf(" ");
    gotoxy(22, 16);
    printf(" ");
    gotoxy(22, 17);
    printf(" ");
    gotoxy(22, 18);
    printf(" ");
    gotoxy(22, 19);
    printf(" ");
    gotoxy(22, 20);
    printf(" ");

    //M
    gotoxy(24, 16);
    printf(" ");
    gotoxy(24, 17);
    printf(" ");
    gotoxy(24, 18);
    printf(" ");
    gotoxy(24, 19);
    printf(" ");
    gotoxy(24, 20);
    printf(" ");
    gotoxy(25, 17);
    printf(" ");
    gotoxy(26, 18);
    printf(" ");
    gotoxy(27, 17);
    printf(" ");
    gotoxy(28, 16);
    printf(" ");
    gotoxy(28, 17);
    printf(" ");
    gotoxy(28, 18);
    printf(" ");
    gotoxy(28, 19);
    printf(" ");
    gotoxy(28, 20);
    printf(" ");

    //E
    gotoxy(30, 16);
    printf(" ");
    gotoxy(30, 17);
    printf(" ");
    gotoxy(30, 18);
    printf(" ");
    gotoxy(30, 19);
    printf(" ");
    gotoxy(30, 20);
    printf(" ");
    gotoxy(31, 16);
    printf(" ");
    gotoxy(31, 18);
    printf(" ");
    gotoxy(31, 20);
    printf(" ");
    gotoxy(32, 16);
    printf(" ");
    gotoxy(32, 20);
    printf(" ");

    //O
    gotoxy(37, 16);
    printf(" ");
    gotoxy(37, 17);
    printf(" ");
    gotoxy(37, 18);
    printf(" ");
    gotoxy(37, 19);
    printf(" ");
    gotoxy(37, 20);
    printf(" ");
    gotoxy(38, 16);
    printf(" ");
    gotoxy(38, 20);
    printf(" ");
    gotoxy(39, 16);
    printf(" ");
    gotoxy(39, 17);
    printf(" ");
    gotoxy(39, 18);
    printf(" ");
    gotoxy(39, 19);
    printf(" ");
    gotoxy(39, 20);
    printf(" ");

    //V
    gotoxy(41, 16);
    printf(" ");
    gotoxy(41, 17);
    printf(" ");
    gotoxy(41, 18);
    printf(" ");
    gotoxy(42, 19);
    printf(" ");
    gotoxy(43, 20);
    printf(" ");
    gotoxy(44, 19);
    printf(" ");
    gotoxy(45, 16);
    printf(" ");
    gotoxy(45, 17);
    printf(" ");
    gotoxy(45, 18);
    printf(" ");

    //E
    gotoxy(47, 16);
    printf(" ");
    gotoxy(47, 17);
    printf(" ");
    gotoxy(47, 18);
    printf(" ");
    gotoxy(47, 19);
    printf(" ");
    gotoxy(47, 20);
    printf(" ");
    gotoxy(48, 16);
    printf(" ");
    gotoxy(48, 18);
    printf(" ");
    gotoxy(48, 20);
    printf(" ");
    gotoxy(49, 16);
    printf(" ");
    gotoxy(49, 20);
    printf(" ");

    //R
    gotoxy(51, 16);
    printf(" ");
    gotoxy(51, 17);
    printf(" ");
    gotoxy(51, 18);
    printf(" ");
    gotoxy(51, 19);
    printf(" ");
    gotoxy(51, 20);
    printf(" ");
    gotoxy(52, 16);
    printf(" ");
    gotoxy(52, 18);
    printf(" ");
    gotoxy(53, 16);
    printf(" ");
    gotoxy(53, 17);
    printf(" ");
    gotoxy(53, 19);
    printf(" ");
    gotoxy(53, 20);
    printf(" ");

    // Retorna as cores default
    textbackground(BLACK);
    textcolor(WHITE);

    // Efeito sonoro
    Beep(200, 300);
    Beep(400, 300);
    Beep(200, 600);

    getch();
}