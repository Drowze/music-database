#include <stdio_ext.h> //consigo usar __fpurge(stdin) sem warnings (warning acusado usando gcc -wall)
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib_musicas.h"

void imprime_string_sem_n(char string[]){
    int i;
    for(i=0; string[i] != '\n'; i++)
        printf("%c", string[i]);
}

int escreve_no_arquivo(no_musica *Lista){
    if(Lista == NULL)
        return 1;
    
    FILE *arquivo = NULL;
    arquivo = fopen("lista_musicas.bin", "wb");
    if(arquivo == NULL)
        return 1;
    
    while(Lista != NULL){
        fwrite(&(Lista->cadastro), sizeof(s_musica), 1, arquivo);
        Lista = Lista->prox;
    }

    fclose(arquivo);
    return 0;    
}

int le_arquivo(no_musica **Lista){
    s_musica musica;
    if(Lista == NULL)
        return 1;

    FILE *arquivo = NULL;
    arquivo = fopen("lista_musicas.bin", "rb");
    if(arquivo == NULL)
        return 1;

    no_musica *novo_no;
    
    while(fread(&musica, sizeof(s_musica), 1, arquivo) == 1){
        novo_no = struct_para_no(musica);
        adicionar_musica(Lista, novo_no);
    }

    fclose(arquivo);
    return 0;
}

/* FUNÇÕES QUE MEXEM COM A STRUCT CADASTRO */

no_musica *cria_musica(){
    s_musica nova_musica;

    printf("Digite o nome do artista: ");
    __fpurge(stdin); fgets(nova_musica.artista, 32, stdin);
    printf("Digite o titulo da faixa: ");
    __fpurge(stdin); fgets(nova_musica.titulo, 32, stdin);
    printf("Digite o genero da faixa: ");
    __fpurge(stdin); fgets(nova_musica.genero, 32, stdin);
    printf("Digite o ano da faixa: ");
    scanf("%d", &nova_musica.ano);
    printf("Para finalizar, digite o nome do arquivo: ");
    __fpurge(stdin); fgets(nova_musica.nome_arquivo, 32, stdin);

    time_t t = time(NULL);
    nova_musica.data_cria = *(localtime ( &t ) );
    nova_musica.data_mod = nova_musica.data_cria;

    no_musica *novo_no;
    novo_no = struct_para_no(nova_musica);
    return novo_no;
}

no_musica *struct_para_no(s_musica musica){
    no_musica *novo_no = (no_musica *)malloc(sizeof(no_musica));
    novo_no->prox = NULL;
    novo_no->ant = NULL;
    novo_no->cadastro = musica;

    return novo_no;
}

void exibe_musica(s_musica musica){
    int i;
    printf("╔═════════════════════════════════════════╗\n");
    printf("║ Titulo.............: "); imprime_string_sem_n(musica.titulo); for(i=0; i<20-strlen(musica.titulo); i++) printf(" "); printf("║\n");
    printf("║ Artista............: "); imprime_string_sem_n(musica.artista); for(i=0; i<20-strlen(musica.artista); i++) printf(" "); printf("║\n");
    printf("║ Genero.............: "); imprime_string_sem_n(musica.genero); for(i=0; i<20-strlen(musica.genero); i++) printf(" "); printf("║\n");
    printf("║ Ano................: %d               ║\n", musica.ano);
    printf("║ Arquivo............: "); imprime_string_sem_n(musica.titulo); for(i=0; i<20-strlen(musica.nome_arquivo); i++) printf(" "); printf("║\n");
    printf("║ Data de criacao....: %d/%d/%d %d:%d:%d ║\n", musica.data_cria.tm_mday, musica.data_cria.tm_mon+1, musica.data_cria.tm_year+1900, musica.data_cria.tm_hour, musica.data_cria.tm_min, musica.data_cria.tm_sec);
    printf("║ Data de modificacao: %d/%d/%d %d:%d:%d ║\n", musica.data_mod.tm_mday, musica.data_mod.tm_mon+1, musica.data_mod.tm_year+1900, musica.data_mod.tm_hour, musica.data_mod.tm_min, musica.data_mod.tm_sec);
    printf("╚═════════════════════════════════════════╝\n");
}

int altera_musica(no_musica **lista, no_musica *no_alterado){
    //Ideia:
    //1) copiar no_alterado -> copia
    //2) alterações no copia
    //3) remover no_alterado da lista
    //4) adicionar copia na lista
    int op;
    time_t t; //usada mais tarde para manipular a hora de modificação

    no_musica *copia = (no_musica *)malloc(sizeof(no_musica));
    copia->prox = NULL; copia->ant = NULL; copia->cadastro = no_alterado->cadastro;

    do{
        printf("\n Qual campo deseja alterar?\n");
        printf("1- Artista \t\t| atual: %s", copia->cadastro.artista);
        printf("2- Titulo \t\t| atual: %s", copia->cadastro.titulo);
        printf("3- Genero \t\t| atual: %s", copia->cadastro.genero);
        printf("4- Ano \t\t\t| atual: %d\n", copia->cadastro.ano);
        printf("5- Nome do arquivo \t| atual: %s", copia->cadastro.nome_arquivo);
        printf("\n 0: Salvar e terminar alteracoes\n");
        printf("-1: Abandonar alteracoes\n");
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("Digite o novo nome de artista: ");
                __fpurge(stdin); fgets(copia->cadastro.artista, 32, stdin);
                break;
            case 2:
                printf("Digite o novo titulo: ");
                __fpurge(stdin); fgets(copia->cadastro.titulo, 32, stdin);
                break;
            case 3:
                printf("Digite o novo genero: ");
                __fpurge(stdin); fgets(copia->cadastro.genero, 32, stdin);
                break;
            case 4:
                printf("Digite o novo ano: ");
                scanf("%d", &(copia->cadastro.ano));
                break;
            case 5:
                printf("Digite o novo nome do arquivo: ");
                __fpurge(stdin); fgets(copia->cadastro.nome_arquivo, 32, stdin);
                break;
            case 0:
                t = time(NULL);
                copia->cadastro.data_mod = *(localtime ( &t ) );
                if(hard_delete(lista, no_alterado) != 0)
                    return 1;
                if(adicionar_musica(lista, copia) != 0)
                    return 1;
                return 0;
            case -1:
                return 0;
        }
    }while(op != 0);
    return 1;
}

//----------------------------------------//

/* FUNÇÕES QUE MEXEM COM OS NÓS */
int adicionar_musica(no_musica **lista, no_musica *novo_no){ //deve armazenar de forma alfabética
    /*
        considerei eliminar o *anterior, mas isso me seria um problema
        na hora de adicionar um elemento ao final da lista, já que aux
        apontaria para NULL e eu não poderia fazer aux->ant->prox = novo_no,
        como seria desejado.
        Para resolver esse problema, o ideal seria implementar uma lista
        circular, possivelmente com nó cabeça.
    */

    no_musica *aux = *lista;
    no_musica *anterior = NULL;
    novo_no->prox = NULL;
    novo_no->ant = NULL;

    if(novo_no == NULL)
        return 1;

    if(aux == NULL){ //Anteriormente, lista vazia
        *lista = novo_no;
        novo_no->prox = NULL;
        novo_no->ant = NULL;
        return 0;
    }
    else{
        while(aux != NULL && (strcmp(aux->cadastro.titulo, novo_no->cadastro.titulo) < 0 ) ) { //eqnt aux->titulo for anterior a no->titulo, ande; http://i.imgur.com/4Q7oKLG.png
            anterior = aux;
            aux = aux->prox;
        }
        if(aux == NULL){ //Insere no final
            anterior->prox = novo_no;
            novo_no->ant = anterior;
            novo_no->prox = NULL;
        }
        else{
            if(anterior == NULL){ //se ele cai aqui, insere antes do primeiro
                *lista = novo_no;
                novo_no->ant = NULL; //ou igual anterior
                novo_no->prox = aux;
                aux->ant = novo_no;
            }
            else{ //se ele cai aqui, pode ser em qualquer outro espaço
                anterior->prox = novo_no;
                novo_no->ant = anterior;
                novo_no->prox = aux;
                aux->ant = novo_no;
            }
        }
        return 0;
    }
    return 1; //Erro: não foi possível adicionar na lista
}

int hard_delete(no_musica **lista, no_musica *no_removido){

    if(no_removido == NULL) //é inesperado cair nesse erro
        return 1;

    if(no_removido == *lista){ //Checa se é o primeiro da lista
        *lista = no_removido->prox; //lista aponta pro seguinte ao removido
        if(no_removido->prox != NULL) //Checo se não é o único elemento na lista
            no_removido->prox->ant = NULL; // (*ant) do seguinte ao removido aponta pra NULL (ele agora é o primeiro elemento)
        free(no_removido);
        return 0;
    }

    else 
        if(no_removido->ant != NULL && no_removido->prox != NULL){ //Checo se tá no meio (não é primeiro nem último)
            no_removido->ant->prox = no_removido->prox; // (*prox) do anterior ao removido aponta para o seguinte ao removido
            no_removido->prox->ant = no_removido->ant; // (*ant) do seguinte ao removido aponta para o anterior ao removido
            free(no_removido);
            return 0;
        }
        else
            if(no_removido->prox == NULL){ //Checo se é o último
                no_removido->ant->prox = NULL; //(*prox) do anterior ao removido aponta pra NULL (ele agora é o último elemento)
                free(no_removido);
                return 0;
            }

    return 1; //é inesperado chegar aqui
}


int remove_musica(no_musica **lista, no_musica **lista_removidos, no_musica *no_removido){

    if(no_removido == NULL) //é inesperado cair nesse erro
        return 1;

    if(no_removido == *lista){ //Checa se é o primeiro da lista
        *lista = no_removido->prox; //lista aponta pro seguinte ao removido
        if(no_removido->prox != NULL) //Checo se não é o único elemento na lista
            no_removido->prox->ant = NULL; // (*ant) do seguinte ao removido aponta pra NULL (ele agora é o primeiro elemento)
        //free(no_removido);
        no_removido->prox = NULL;
        no_removido->ant = NULL;
        adicionar_musica(lista_removidos, no_removido);
        return 0;
    }

    else 
        if(no_removido->ant != NULL && no_removido->prox != NULL){ //Checo se tá no meio (não é primeiro nem último)
            no_removido->ant->prox = no_removido->prox; // (*prox) do anterior ao removido aponta para o seguinte ao removido
            no_removido->prox->ant = no_removido->ant; // (*ant) do seguinte ao removido aponta para o anterior ao removido
            //free(no_removido);
            no_removido->prox = NULL;
            no_removido->ant = NULL;
            adicionar_musica(lista_removidos, no_removido);
            return 0;
        }
        else
            if(no_removido->prox == NULL){ //Checo se é o último
                no_removido->ant->prox = NULL; //(*prox) do anterior ao removido aponta pra NULL (ele agora é o último elemento)
                //free(no_removido);
                no_removido->prox = NULL;
                no_removido->ant = NULL;
                adicionar_musica(lista_removidos, no_removido);
                return 0;
            }

    return 1; //é inesperado chegar aqui
}

//Sobre a procura: se titulo = NULL, remoção por artista, caso contrário artista = NULL
no_musica *busca_musica(no_musica *lista, char titulo[], char artista[]){
    no_musica *aux = lista;
    if(aux == NULL)
        return NULL;

    if(titulo != NULL && artista != NULL){ //busca uma musica de um artista especifico
        while(aux != NULL && ((strcmp(aux->cadastro.titulo, titulo) < 0) || (strcmp(aux->cadastro.artista, artista) != 0)) )
            aux = aux->prox;

        if(aux == NULL || strcmp(aux->cadastro.artista, artista) != 0 || strcmp(aux->cadastro.titulo, titulo) != 0)
            return NULL;
        else
            return aux;
    }
    
    else if(titulo != NULL){ //busca musica pelo titulo
        while(aux != NULL && strcmp(aux->cadastro.titulo, titulo) < 0)
            aux = aux->prox;

        if(aux == NULL || strcmp(aux->cadastro.titulo, titulo) != 0)
            return NULL;
        else
            return aux;
    }

    //busca musica pelo artista. Vai retornar o primeiro nó do artista correspondente
    //útil para checar se existe pelo menos uma ocorrência
    else{ 
        while( (aux != NULL) && (strcmp(aux->cadastro.artista, artista) != 0) )
            aux = aux->prox;

        if(aux == NULL || strcmp(aux->cadastro.artista, artista) != 0)
            return NULL;
        else
            return aux;
    }

    return NULL;
}

int exibe_lista(no_musica *Lista, char artista[]){
    if(Lista == NULL)
        return 1;

    int i = 0;

    if(artista == NULL){
        while(Lista != NULL){
            exibe_musica(Lista->cadastro);
            if(Lista->prox != NULL) 
                printf("\t --- \n");
            Lista = Lista->prox;
        }
    }
    else{ //exibir músicas de um artista específico
        while(Lista != NULL){
            if(strcmp(Lista->cadastro.artista, artista) == 0){
                exibe_musica(Lista->cadastro);
                i++;
                if(Lista->prox != NULL) 
                    printf("\t --- \n");
            }
            Lista = Lista->prox;
        }
        return i;
    }
    return 0;
}

//função sem uso para o usuário final
int debugger_exibe_lista(no_musica *Lista){
    if(Lista == NULL)
        return 1;

    int i = 0;
    while(Lista != NULL){
        printf("Indice: %d\n", i);
        printf("Endereco: %p\n", (void *) Lista);
        printf("Endereco (struct): %p\n", (void *) &(Lista->cadastro));
        printf("Nome da musica: %s", Lista->cadastro.titulo);
        printf("Endereco->ant: %p\n", (void *) (Lista->ant));
        printf("Endereco->prox: %p\n\n", (void *) (Lista->prox));
        Lista = Lista->prox;
        i++;
    }
    __fpurge(stdin); getchar();

    return 0;
}
