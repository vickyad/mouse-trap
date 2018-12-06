#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <strings.h>
#include <conio2.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <windows.h>


#define LINHAS_MAPA 11
#define COLUNAS_MAPA 27
#define LINHAS_TERMINAL 30
#define COLUNAS_TERMINAL 105
#define LINHAS_INTERFACE_RETANG 11
#define COLUNAS_INTERFACE_RETANG 44
#define LINHAS_RANKING 17
#define COLUNAS_RANKING 34
#define MAX_SAVES 10
#define NOME_MAX 20
#define NOME_ARQUIVO 18
#define NUM_VIDAS 3
#define NUM_GATOS 4
#define NUM_OSSOS 4
#define NUM_PORTAS 7
#define TEMPO_MC 5000
#define TEMPO_MG 100


/* Estruturas */
typedef struct {
    int x;
    int y;
} Coord;

typedef struct {
    char nome[NOME_MAX];
    Coord pos_inicial;
    Coord pos_atual;
    int pontuacao;
    int vidas;
    int qtd_queijos;
    int ossos_restantes;
    int status_cachorro;
} Jogador;

typedef struct{
    Coord pos_inicial;
    Coord pos_atual;
    int direcao;
    int flag;
    clock_t last_time;
    int comeu_queijo;
} Gato;

typedef struct{
    Coord pos_porta;
} Porta;

typedef struct{
    Jogador jogador;
    Gato gato[NUM_GATOS];
    Porta porta[NUM_PORTAS];

    int nivel;
    int status_portas;
} Estado;

typedef struct {
    char nome[NOME_MAX];
    int score;
} SAVE;

/* Funcoes */
// Funcoes de desenho
void desenhaRato(int x, int y);
void desenhaQueijo(int x, int y);
void desenhaParede(int x, int y);
void desenhaOsso(int x, int y);
void desenhaPorta(int x, int y);
void desenhaGato(int x, int y);
void desenhaCachorro(int x, int y);
void desenhaRetangulo();
void desenhaInterface();
void desenhaInfo(Estado estado_atual);
void desenhaMapa(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado estado_atual);
void desenhaInicio();
void desenhaInstrucoes();
void desenhaPause();
void desenhaPassaNivel();
void desenhaVitoria();
void desenhaDerrota();

// Telas
void inicio(Estado *Estado_atual);

// Obtencao de coordenadas
void localizaPosicoes(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual);

// Movimentacao
void mexeRato(char mapa[LINHAS_MAPA][COLUNAS_MAPA], int x, int y, clock_t *tempo_inicial, Estado *estado_atual);
void mexeGato(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual);
void mexePorta(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual, int *status_portas);

// Manipulacao de arquivos
void pegaMapa(char mapa[LINHAS_MAPA][COLUNAS_MAPA], int nivel);
void salvaJogo(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado estado_atual);
void carregaJogo(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual);

// Outras funcoes
int geraNumero();
void removeCursor();

// Teste
void leRanking(FILE *arq, SAVE ranking[MAX_SAVES]);
void salvaRanking(FILE *arq, SAVE ranking[MAX_SAVES]);
int atualizaVetor(SAVE ranking[MAX_SAVES], Jogador last_win);
void ordenaVetor(SAVE vetor[MAX_SAVES]);
void atualizaRanking(Jogador last_win);
void desenha_ranking(SAVE ranking[MAX_SAVES]);

#endif // FUNCTIONS_H_INCLUDED
