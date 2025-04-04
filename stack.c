#include "stack.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define INIT_CAPACITY 2
#define FCT_CAPACITY 2

struct _Stack
{
    void **item;
    int top;
    int capacity;
};

Stack *stack_init(){
    Stack *s=NULL;

    s=(Stack*)malloc(sizeof(Stack));
    if(!s) return NULL;

    s->capacity=INIT_CAPACITY;
    s->top=-1;
    s->item=(void**)malloc(s->capacity * sizeof(void*));

    return s;
}

void stack_free (Stack *s){
    free(s->item);
    free(s);
}

Status stack_push (Stack *s, const void *ele){
    void **temp=NULL;

    if(!s||!ele){
        return ERROR;
    }

    if(s->top==s->capacity - 1){
        s->capacity*=FCT_CAPACITY;
        temp = (void**)realloc(s->item, s->capacity*sizeof(void*));
        s->item=temp;
    }

    s->top++;
    s->item[s->top]=(void*)ele;
    return OK;
}

void * stack_pop (Stack *s){
    void *e=NULL;

    if(!s||stack_isEmpty(s)==TRUE){
        return NULL;
    }

    e=s->item[s->top];
    s->item[s->top]=NULL;
    s->top--;
    return e;
}

void * stack_top (const Stack *s){
    if(!s||stack_isEmpty(s)==TRUE){
        return NULL;
    }

    return s->item[s->top];
}

Bool stack_isEmpty (const Stack *s){
    if(!s||s->top==-1){
        return TRUE;
    }

    return FALSE;
}

size_t stack_size (const Stack *s){
    if(!s) return -1;

    return s->top;
}

int stack_print(FILE* fp, const Stack *s,  P_stack_ele_print f){
    int i, count;

    if(!fp||!s||!f) return -1;

    for (i=0; i<s->top; i++){
        count+=f(fp, s->item[i]);
        fprintf(stdout, "\n");
    }

    return count;
}
