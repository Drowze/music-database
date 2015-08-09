/*
Integrante 1 - Nome: Rafael Gibim               RA: 14081673
Integrante 2 - Nome: Rodrigo Groot              RA: 14129027
Integrante 3 - Nome: Leonardo Saito             RA: 14035265
Integrante 4 - Nome: Vinicius Nunes             RA: 14035265
Resultados obtidos:
Projeto básico: 100 % concluído
(X) Opcional 1 
(X) Opcional 2 
(X) Opcional 3 - Obs: Não há opção de cor
(X) Opcional 4 - Obs: Comportamento inesperado em alguns momentos
( ) Opcional 5 - Obs: 
(X) Opcional 6
*/

 //consigo usar __fpurge(stdin) sem warnings (warning acusado usando gcc -wall)
#include <time.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "lib_musicas.h"



int main(void){
    int op;
    char titulo[32], artista[32];

    no_musica *Lista = NULL; //Ponteiro para lista de músicas inicialmente vazia
    no_musica *ListaRemovidos = NULL; //ponteiro para "lixeira"
    no_musica *no = NULL;
    no_musica *no2 = NULL;

    le_arquivo(&Lista);

    do{
        system("clear");
        printf("\n╔═════════════════════════════════════════════════╗\n");
        printf("║            Digite a opcao desejada:             ║\n");
        printf("╠═════════════════════════════════════════════════╣\n");
        printf("║ 1- Inserir musica                               ║\n");
        printf("║ 2- Remover musica                               ║\n");
        printf("║ 3- Alterar musica                               ║\n");
        printf("║ 4- Buscar musica pelo titulo                    ║\n");
        printf("║ 5- Buscar musicas pelo artista                  ║\n");
        printf("║ 6- Recuperar músicas apagadas                   ║\n");
        printf("║ 7- Exibir dados de todas as musicas cadastradas ║\n");
        printf("║                                                 ║\n");
        printf("║ 0- Sair                                         ║\n");
        printf("╚═════════════════════════════════════════════════╝\n");
        //puts("-1 Debugger: Exibir Lista");
        scanf("%d", &op);

        switch(op){
            case 1:
                if(adicionar_musica(&Lista, cria_musica()) != 0){
                    printf("╔═════════════════════════════════════╗\n");
                    printf("║ Erro: impossivel adicionar a musica ║\n");
                    printf("╚═════════════════════════════════════╝\n");
                    __fpurge(stdin); getchar();
                }
                else{
                    printf("╔═══════════════════════════════╗\n");
                    printf("║ Musica adicionada com sucesso ║\n");
                    printf("╚═══════════════════════════════╝\n");
                    __fpurge(stdin); getchar();
                }
                break;

            case 2:
                do{
                    printf("╔════════════════════════╗\n");
                    printf("║          Opcao         ║\n");
                    printf("╠════════════════════════╣\n");
                    printf("║ 1- Remover por titulo  ║\n");
                    printf("║ 2- Remover por artista ║\n");
                    printf("╚════════════════════════╝\n");
                    scanf("%d", &op);
                    if(op != 1 && op != 2){
                        printf("╔══════════════════════╗\n");
                        printf("║ Erro: opcao invalida ║\n");
                        printf("╚══════════════════════╝\n");
                    }
                }while(op != 1 && op != 2);
                
                if(op == 1){
                    printf("Digite o nome da musica a ser removida: ");
                    __fpurge(stdin); fgets(titulo, 32, stdin);
                    no = busca_musica(Lista, titulo, NULL);
                    if(no == NULL){
                        printf("╔══════════════════════════════════╗\n");
                        printf("║ Erro: nenhum elemento encontrado ║\n");
                        printf("╚══════════════════════════════════╝\n");
                        __fpurge(stdin); getchar();
                    }
                    else
                        if(remove_musica(&Lista, &ListaRemovidos, no) != 0){
                            printf("╔═════════════════╗\n");
                            printf("║ Erro inesperado ║\n");
                            printf("╚═════════════════╝\n");
                        }
                        else{
                            printf("╔══════════════════════╗\n");
                            printf("║ Removido com sucesso ║\n");
                            printf("╚══════════════════════╝\n");
                        }
                        __fpurge(stdin); getchar();
                }

                else{
                    printf("Digite o nome do artista da musica a ser removida: ");
                    __fpurge(stdin); fgets(artista, 32, stdin);
                    no = busca_musica(Lista, NULL, artista);

                    if(no == NULL){
                        printf("╔════════════════════════════╗\n");
                        printf("║ Nenhum elemento encontrado ║\n");
                        printf("╚════════════════════════════╝\n");
                        __fpurge(stdin); getchar();
                    }
                    else{
                        printf("\nResultados: %d \n", exibe_lista(Lista, artista));

                        printf("Digite o titulo da musica do(a) \""); imprime_string_sem_n(artista); printf("\" a ser removida: ");
                        fgets(titulo, 32, stdin);
                        no = busca_musica(Lista, titulo, artista);

                        if(no == NULL){
                            printf("╔════════════════════════════╗\n");
                            printf("║ Nenhum elemento encontrado ║\n");
                            printf("╚════════════════════════════╝\n");
                        }
                        else
                            if(remove_musica(&Lista, &ListaRemovidos, no) != 0){
                                printf("╔═════════════════╗\n");
                                printf("║ Erro inesperado ║\n");
                                printf("╚═════════════════╝\n");
                            }
                            else{
                                printf("╔══════════════════════╗\n");
                                printf("║ Removido com sucesso ║\n");
                                printf("╚══════════════════════╝\n");
                            }
                        __fpurge(stdin); getchar();
                    }
                }
                break;

            case 3:
                printf("Digite o nome da musica a alterada: ");
                __fpurge(stdin); fgets(titulo, 32, stdin);
                no = busca_musica(Lista, titulo, NULL);
                if(no == NULL){
                    printf("╔═══════════════════════════════╗\n");
                    printf("║ Erro: elemento nao encontrado ║\n");
                    printf("╚═══════════════════════════════╝\n");
                    __fpurge(stdin); getchar();
                }
                else
                    if(altera_musica(&Lista, no) != 0){
                        printf("╔═════════════════╗\n");
                        printf("║ Erro inesperado ║\n");
                        printf("╚═════════════════╝\n");
                        __fpurge(stdin); getchar();
                    }
                break;

            case 4:
                printf("Digite o nome da musica a ser buscada: ");
                __fpurge(stdin); fgets(titulo, 32, stdin);
                no = busca_musica(Lista, titulo, NULL);
                if(no == NULL){
                    printf("╔═══════════════════════════════╗\n");
                    printf("║ ERRO: elemento nao encontrado ║\n");
                    printf("╚═══════════════════════════════╝\n");
                    __fpurge(stdin); getchar();
                }
                else{
                    printf("╔═════════════════════╗\n");
                    printf("║ Exibindo resultados ║\n");
                    printf("╚═════════════════════╝\n");
                    exibe_musica(no->cadastro);
                    __fpurge(stdin); getchar();
                }
                break;

            case 5:
                printf("Digite o nome do artista: ");
                __fpurge(stdin); fgets(artista, 32, stdin);
                no = busca_musica(Lista, NULL, artista);
                if(no == NULL){
                    printf("╔══════════════════════════════════════════╗\n");
                    printf("║ ERRO: nao foi encontrado nenhum elemento ║\n");
                    printf("╚══════════════════════════════════════════╝\n");
                    __fpurge(stdin); getchar();
                }
                else{
                    printf("\nResultados: %d \n", exibe_lista(Lista, artista));
                    __fpurge(stdin); getchar();
                }
                break;

            case 6:
                printf("╔══════════════════════════════╗\n");
                printf("║ Musicas previamente apagadas ║\n");
                printf("╚══════════════════════════════╝\n");
                if(exibe_lista(ListaRemovidos, NULL) != 0){
                    printf("╔══════════════════════════════════╗\n");
                    printf("║ ERRO: nenhuma musica foi apagada ║\n");
                    printf("╚══════════════════════════════════╝\n");
                    __fpurge(stdin); getchar();                    
                }
                else{
                    printf("Digite o titulo da musica que deseja recuperar: ");
                    __fpurge(stdin); fgets(titulo, 32, stdin);
                    no = busca_musica(ListaRemovidos, titulo, NULL);
                    if(no == NULL){
                    printf("╔═════════════════════════════╗\n");
                    printf("║ ERRO: musica nao encontrada ║\n");
                    printf("╚═════════════════════════════╝\n");
                    }
                    else{
                        adicionar_musica(&Lista, no);

                        if(ListaRemovidos != NULL)
                            hard_delete(&ListaRemovidos, busca_musica(ListaRemovidos, titulo, NULL));
                        else
                            printf("Erro inesperado");
                    }
                    
                }
                break;

            case 7:
                printf("\n╔═════════════════════╗\n");
                printf("║ Exibindo resultados ║\n");
                printf("╚═════════════════════╝\n");
                if(exibe_lista(Lista, NULL) != 0){
                    printf("╔═════════════════════╗\n");
                    printf("║  ERRO: Lista vazia  ║\n");
                    printf("╚═════════════════════╝\n");
                }
                __fpurge(stdin); getchar();        
                break;
            // case -1:
            //     debugger_exibe_lista(ListaRemovidos);
        }

    }while(op != 0);
    if(escreve_no_arquivo(Lista) != 0)
        printf("Erro: impossivel salvar registros");
}
