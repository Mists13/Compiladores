#include <stdio.h>
#include "queue.h"

//GRR20182592 VINICIUS OLIVEIRA DOS SANTOS 


//-------------------------------------------------------------------------------------------------------
/*

    FUNCOES COMPLEMENTARES

*/
//-------------------------------------------------------------------------------------------------------

int busca(queue_t **queue, queue_t *elem){
    int achou = 0;
    queue_t *head = *queue;
    
    if(*queue == elem){
        achou = 1; //ja eh o primeiro
    }
    *queue = (*queue)->next; //proximo

    //percorro a fila ate chegar a cabeca novamente
    while (*queue != head){
        if(*queue == elem){
            achou = 1;
        }
        *queue = (*queue)->next;
    }
    *queue = head; //retorno ao inicio

    return achou;
}

int vazia(queue_t *queue){
    if(queue == NULL){
        return 1; //vazia
    }
    
    return 0; //nao vazia
}

//-------------------------------------------------------------------------------------------------------

int queue_size (queue_t *queue){
    
    //se vazio, tamanho eh 0
    if(vazia(queue)){

        return 0;
    }
   
    int size = 1;
    queue_t *head = queue;
    queue = queue->next;

    //percorro a fila ate chegar a cabeca novamente
    while (queue != head){
        size++;
        queue = queue->next;
    }
    return size;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*) ) {
    
    //se vazia imprime nada
    if(vazia(queue)){
        return;
    }
    
    queue_t *head = queue;
    print_elem(queue);
    queue = queue->next;

    //imprimo ate ate retornar a cabeca
    while(queue != head){
        print_elem(queue);
        queue = queue->next;
    }
    return;
}

int queue_append(queue_t **queue, queue_t *elem){ 
	
    //confere se existe fila e elemento
    if(!queue || !elem){
        fprintf(stderr, "Fila ou elemento não existem");
        return -1;
    }

    //confere se elemento nao pertence a outra fila
    if ( elem->next != NULL || elem->prev != NULL ){
		return -1;
    }

    //inserçao em fila vazia
    if(vazia(*queue)){
        elem->prev = elem;
        elem->next = elem->prev; //aponta pra si mesmo
        *queue = elem; //ponho na fila
    }
    else {
        queue_t* head = *queue; //reservo cabeca da fila
        elem->prev = (*queue)->prev; //agora anterior elem eh o anterior da cabeca da fila (antigo rabo)
        elem->next = *queue; //agora prox elem de elem eh cabeca da fila
        
        *queue = (*queue)->prev;
        (*queue)->next = elem; //agora proximo do antigo rabo eh elem (novo rabo)
        *queue = head;
        (*queue)->prev = elem; //agora anterior da cabeca eh elem (novo rabo)
    }
    return 0;
}

int queue_remove (queue_t **queue, queue_t *elem){
     
    //confere se existe fila ou elemento
    if(!queue || !elem){
        fprintf(stderr, "Fila ou elemento não existem");
        return -1;
    }
    //confere se fila esta vazia
    if(vazia(*queue)){
        return -1;
    }
    
    //confere se elemento pertence a essa fila
    if(!busca(queue, elem)){
        return -1;
    }

    //remocao
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;

   //remocao na cabeca
    if(*queue == elem){
        //se so tem cabeca nula tudo
        if(elem->prev == elem && elem->next == elem){
            *queue = NULL;
        }
        else{
            *queue = elem->next;
        }
    }

    elem->next = NULL;
    elem->prev = NULL;  

    return 0;

}

// diferentemente de SO essa fila vai ter que se comportar como uma pilha, entao precisamos de uma funcao para desempilhar
// acho que eh assim mas n tenho certeza
int queue_desempilha (queue_t **queue) {
   
    //confere se existe fila ou elemento
    if(!queue || !elem){
        fprintf(stderr, "Fila ou elemento não existem");
        return -1;
    }
    
    //confere se fila esta vazia
    if(vazia(*queue)){
        return -1;
    }

    //confere se elemento pertence a essa fila
    if(!busca(queue, elem)){
        return -1;
    }

    //remocao
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;

    //remocao na cabeca
    if(*queue == elem){
        //se so tem cabeca nula tudo
        if(elem->prev == elem && elem->next == elem){
            *queue = NULL;
        }
        else{
            *queue = elem->next;
        }
    }

    elem->next = NULL;
    elem->prev = NULL; 

    return elem; 
}
