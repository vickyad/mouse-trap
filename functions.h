#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/* ----------// Bibliotecas //---------- */
#include <stdio.h>
#include <strings.h>
#include <conio2.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <windows.h>

/* ----------// Definicoes //---------- */
/* Definicoes relacionadas a interfaces */
#define LINHAS_MAPA 11
#define COLUNAS_MAPA 27
#define LINHAS_TERMINAL 30
#define COLUNAS_TERMINAL 105
#define LINHAS_INTERFACE_RETANG 9
#define COLUNAS_INTERFACE_RETANG 44
#define LINHAS_RANKING 17
#define COLUNAS_RANKING 34
#define LINHAS_SLOTS 21
#define COLUNAS_SLOTS 40

/* Definições relacionadas a tamanhos maximos de vetores */
#define MAX_SAVES 10
#define NOME_MAX 20
#define NOME_ARQUIVO 30
#define FRASE_MAX 34

/* Definicoes gerais */
#define NUM_VIDAS 3
#define NUM_GATOS 4
#define NUM_OSSOS 4
#define NUM_PORTAS 7
#define NIVEL_MAX 4
#define TEMPO_MC 5000
#define TEMPO_MG 300


/* ----------// Estruturas //---------- */
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
    int flag;
} Porta;

typedef struct{
    Jogador jogador;
    Gato gato[NUM_GATOS];
    Porta porta[NUM_PORTAS];
    SYSTEMTIME actual_time;

    int nivel;
    int status_portas;
} Estado;

typedef struct {
    char nome[NOME_MAX];
    int score;
} Save;


/* ----------// Funcoes //---------- */
/* Funcoes de desenho */
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
void desenhaSlots(Estado game_data);
void desenhaSetas(int option, Estado game_data);
void apagaSetas(int option, Estado game_data);
void desenha_ranking(Save ranking[MAX_SAVES]);
void desenhaVitoria();
void desenhaDerrota();

/* Telas */
void inicio(Estado *Estado_atual);
int selecionaSlot(SYSTEMTIME actual_time);
char aviso(char str[FRASE_MAX]);

/* Obtencao de coordenadas */
void localizaPosicoes(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual);

/* Movimentacao */
void mexeRato(char mapa[LINHAS_MAPA][COLUNAS_MAPA], int x, int y, clock_t *tempo_inicial, Estado *estado_atual);
void mexeGato(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual);
void mexePorta(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual, int *status_portas);

/* Manipulacao de arquivos */
void pegaMapa(char mapa[LINHAS_MAPA][COLUNAS_MAPA], int nivel);
void salvaJogo(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado estado_atual, int option);
void carregaJogo(char mapa[LINHAS_MAPA][COLUNAS_MAPA], Estado *estado_atual, int option);
void leRanking(FILE *arq, Save ranking[MAX_SAVES]);
void salvaRanking(FILE *arq, Save ranking[MAX_SAVES]);
void atualizaRanking(Jogador last_win);

/* Outras funcoes */
void removeCursor();
int geraNumero();
int atualizaVetor(Save ranking[MAX_SAVES], Jogador last_win);
void ordenaVetor(Save vetor[MAX_SAVES]);

/* Teste */
int disPontos(int x1, int y1, int x2, int y2);
#endif // FUNCTIONS_H_INCLUDED
