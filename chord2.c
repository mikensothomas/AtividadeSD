#include <stdio.h>
#include <stdlib.h>
#define TAM 12

typedef struct NO {
    int valor;
    char recurso[18];
    struct NO* proximo;
    int ativo;
    struct NO* proximo_ativo;
    struct NO* responsavel;
} NO;

typedef struct Lista {
    NO* inicio;
    NO* fim;
} Lista;

void inicializa_lista(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

int funcaoHash(int chave){
    return chave % TAM;
}

void inserir_recurso(Lista* lista, char recurso[18]){
    
}

void inserir_no_fim(Lista* lista, int valor) {
    NO* novo_no = (NO *)malloc(sizeof(NO));
    if (novo_no == NULL) {
        printf("Erro: Não foi possível alocar memória para o NOvo nó.\n");
        return;
    }

    novo_no->valor = valor;

    if (lista->inicio == NULL) {
        lista->inicio = novo_no;
    } else {
        lista->fim->proximo = novo_no;
    }

    lista->fim = novo_no;

    lista->fim->proximo = lista->inicio;
}

void ativar_no(Lista* lista, int numero){
    if (lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    NO* atual = lista->inicio;

    do {
        //printf("%d ", atual->valor);
        if(atual->valor == numero){
            atual->ativo = 1;
            printf("%d foi ativado\n", atual->valor);
        }
        atual = atual->proximo;
    } while (atual != lista->inicio);

}

void desativar_no(Lista* lista, int numero){
    if (lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    NO* atual = lista->inicio;

    do {
        //printf("%d ", atual->valor);
        if(atual->valor == numero){
            atual->ativo = 0;
            printf("%d foi desativado\n", atual->valor);
        }
        atual = atual->proximo;
    } while (atual != lista->inicio);

}

void ligar_no_ativado(Lista* lista){
    if (lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    NO* atual = lista->inicio;
    NO* salvar_ativo;
    int achar_prinmeiro = 0;
    NO* primeiro_ativo;

    do {
        
        if(atual->ativo == 1 && achar_prinmeiro == 0){
            salvar_ativo = atual;
            primeiro_ativo = atual;
            achar_prinmeiro = 1;
        } else if (atual->ativo == 1 && achar_prinmeiro == 1) {
            salvar_ativo->proximo_ativo = atual;
            atual->proximo_ativo = primeiro_ativo;
            salvar_ativo = atual;
        }
        

        atual = atual->proximo;
    } while (atual != lista->inicio);

}

void conectar_responsaveis(Lista* lista){
    if (lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    NO* atual = lista->inicio;
    NO* salvar_ativo;
    int achar_prinmeiro = 0;
    NO* primeiro_ativo;
    NO* responsavel;

    do {
        
        if(atual->ativo == 1 && achar_prinmeiro == 0){
            salvar_ativo = atual;
            responsavel = atual->proximo;
            primeiro_ativo = atual;
            achar_prinmeiro = 1;
        } else if (atual->ativo == 1 && achar_prinmeiro == 1) {
            //salvar_ativo->proximo_ativo = atual;
            //atual->proximo_ativo = primeiro_ativo;
            //salvar_ativo = atual;
            atual->responsavel = responsavel;
            responsavel = atual->proximo;
            salvar_ativo = atual;
        }

        primeiro_ativo->responsavel = responsavel;
        

        atual = atual->proximo;
    } while (atual != lista->inicio);

}

void imprimir_responsaveis(Lista* lista){
    if (lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    NO* atual = lista->inicio;
    NO* primeiro_ativo;
    do {
        if(atual->ativo == 1){
            primeiro_ativo = atual;
            break;
        }
        atual = atual->proximo;
    } while (atual != lista->inicio);
    
    NO* auxiliar;

    do {    
        for(auxiliar = atual->responsavel; auxiliar != atual->proximo; auxiliar = auxiliar->proximo ){
            printf(" -> ");
            printf("%d responsavel: %d \n", atual->valor, auxiliar->valor);
            
        }
        //printf("%d responsavel: %d\n", atual->valor, atual->responsavel->valor);
        //printf(" -> ");
        atual = atual->proximo_ativo;
    } while (atual != primeiro_ativo);

    printf("\n");
}

void imprimir_ativos_ligados(Lista* lista){
    if (lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    NO* atual = lista->inicio;
    NO* primeiro_ativo;
    do {
        if(atual->ativo == 1){
            primeiro_ativo = atual;
            break;
        }
        atual = atual->proximo;
    } while (atual != lista->inicio);
    

    do {    
        printf("%d ", atual->valor);
        printf(" -> ");
        atual = atual->proximo_ativo;
    } while (atual != primeiro_ativo);

    printf("\n");
}

void imprimir_lista(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    NO* atual = lista->inicio;

    do {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    } while (atual != lista->inicio);

    printf("\n");
}


int main() {
    Lista lista;
    inicializa_lista(&lista);

    inserir_no_fim(&lista, 0);
    inserir_no_fim(&lista, 1);
    inserir_no_fim(&lista, 2);
    inserir_no_fim(&lista, 3);
    inserir_no_fim(&lista, 4);
    inserir_no_fim(&lista, 5);
    inserir_no_fim(&lista, 6);
    inserir_no_fim(&lista, 7);
    inserir_no_fim(&lista, 8);
    inserir_no_fim(&lista, 9);
    inserir_no_fim(&lista, 10);
    inserir_no_fim(&lista, 11);
    inserir_no_fim(&lista, 12);
    inserir_no_fim(&lista, 13);
    inserir_no_fim(&lista, 14);
    inserir_no_fim(&lista, 15);

    printf("Lista: ");
    imprimir_lista(&lista);

    ativar_no(&lista, 0);
    ativar_no(&lista, 5);
    ativar_no(&lista, 9);
    ativar_no(&lista, 13);
    //desativar_no(&lista, 6);

    ligar_no_ativado(&lista);
    imprimir_ativos_ligados(&lista);

    conectar_responsaveis(&lista);
    imprimir_responsaveis(&lista);

    /*desativar_no(&lista, 32);
    ligar_no_ativado(&lista);
    conectar_responsaveis(&lista);

    imprimir_ativos_ligados(&lista);
    imprimir_responsaveis(&lista);*/



    return 0;
}