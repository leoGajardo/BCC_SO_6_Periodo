#include<stdio.h>
#include<stdint.h>

typedef struct pontero{
    uint8_t* p;
    int tamanho;
    struct pontero* anterior;
    struct pontero* proximo;
} aloc;

uint8_t memory[4096];
aloc* mapa = NULL;

void* aloca(unsigned int bytes){
    if(mapa == NULL){
        if(bytes < sizeof(memory)){
            aloc v = { .tamanho = bytes, .p = &memory[0] , .proximo = NULL };
            mapa = &v;
            return mapa->p;
        }
        else{
            return NULL;
        }
    }
    else{
        int achou = 0;
        aloc* posicao = mapa;

        while(achou != 0){
            if(posicao->proximo == NULL){
                if(bytes <= (sizeof(memory) - (posicao->tamanho + (posicao->p - &memory[0])))){
                    aloc v = { .tamanho = bytes, .p = &memory[(posicao->tamanho + (posicao->p - &memory[0]) + 1)] , .proximo = NULL, .anterior = posicao };
                    posicao->proximo = &v;

                    return posicao->proximo->p;
                }
                else{
                    return NULL;
                }
            }
            else{
                if((posicao->proximo->p - posicao->p + posicao->tamanho) >= bytes){
                    aloc v = { .tamanho = bytes, .p = &memory[(posicao->tamanho + (posicao->p - &memory[0]) + 1)] , .proximo = posicao->proximo, .anterior = posicao };
                    posicao->proximo->anterior = &v;
                    posicao->proximo = &v;

                    return posicao->proximo->p;
                }
                else{
                    posicao = posicao->proximo;
                }
            }
        }
    }
}

void libera(void* ponteiro){

}


int main(void){

    int* b = (int*)aloca(sizeof(int)*2);
    *(b) = 4;
    *(b+sizeof(int)) = 6;

    printf("%d\n", (*b));
    printf("%d\n", (*b+sizeof(int)));

}
