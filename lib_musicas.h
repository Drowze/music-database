#ifndef LIB_MUSICAS_H_INCLUDED
#define LIB_MUSICAS_H_INCLUDED

struct s_musica{
    char artista[32];
    char titulo[32];
    char genero[32];
    int ano;
    char nome_arquivo[32];
    struct tm data_cria;
    struct tm data_mod;
};
typedef struct s_musica s_musica;

struct no_musica{
    struct s_musica cadastro;
    struct no_musica *prox;
    struct no_musica *ant;
};
typedef struct no_musica no_musica;


int escreve_no_arquivo(no_musica *Lista);
int le_arquivo(no_musica **Lista);


no_musica *struct_para_no(s_musica musica);
no_musica *cria_musica();
void exibe_musica(s_musica musica);
int altera_musica(no_musica **lista, no_musica *no_alterado);
void imprime_string_sem_n(char string[]);


int adicionar_musica(no_musica **lista, no_musica *novo_no);
int remove_musica(no_musica **lista, no_musica **lista_removidos, no_musica *no_removido);
int hard_delete(no_musica **lista, no_musica *no_removido);
no_musica *busca_musica(no_musica *lista, char titulo[], char artista[]);
int exibe_lista(no_musica *lista, char artista[]);


int debugger_exibe_lista(no_musica *Lista);

#endif
