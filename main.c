#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node * prev;
    struct node * next;
} Node;

void add(Node ** head, Node ** tail, int data){
    if(*head == NULL){
        *head = (Node*)malloc(sizeof(Node));
        (*head)->data = data;
        (*head)->prev = NULL;
        (*head)->next = NULL;
        *tail = *head;
        return;
    }
    (*tail)->next = (Node*)malloc(sizeof(Node));
    (*tail)->next->data = data;
    (*tail)->next->prev = (*tail);
    (*tail)->next->next = NULL;
    (*tail) = (*tail)->next;
}

void show(Node * head){
    Node * i;
    for(i = head;i != NULL;i = i->next)
        printf("%d ",i->data);
    printf("\n");
}

int main() {
    int i, j;
    FILE * file = fopen("Sayilar.txt", "r");

    Node * head0 = NULL,
    * tail0 = NULL,
    * head1 = NULL,
    * tail1 = NULL,
    * i0    = NULL,
    * i1    = NULL,
    * temp  = NULL,
    * rev   = NULL;
    char text[3];
    int which = 0;
    int counter = 0;
    int number;
    while(1){
        if(fscanf(file, "%c", &text[0]) == -1) break;
        if(text[0] == '#'){
            which = 1;
            continue;
        }

        fscanf(file, "%c", &text[1]);
        fscanf(file, "%c", &text[2]);

        sscanf(text, "%d", &number);
        if(which == 0)
            add(&head0, &tail0, number);
        else
            add(&head1, &tail1, number);
        counter++;
    }

    for(i = 0;i<counter/2;i++){
        i0 = head0;
        i1 = head1;
        for(j = 0;j<i;j++){
            i0 = i0->next;
            i1 = i1->next;
        }

        if(i0->data > i1->data){
            rev = head0;
            while(rev != NULL){
                temp = rev->prev;
                rev->prev = rev->next;
                rev->next = temp;
                rev = rev->prev;
            }
            temp = head0;
            head0 = tail0;
            tail0 = temp;
        }else if(i0->data < i1->data){
            temp = i1->prev;
            i1->prev = i0->prev;
            if(temp)
                temp->next = i0;

            i0->prev = temp;
            if(i1->prev)
                i1->prev->next = i1;

            temp = i1->next;
            i1->next = i0->next;
            if(temp)
                temp->prev = i0;

            i0->next = temp;
            if(i1->next)
                i1->next->prev = i1;
        }else{
            rev = head1;
            while(rev != NULL){
                temp = rev->prev;
                rev->prev = rev->next;
                rev->next = temp;
                rev = rev->prev;
            }
            temp = head1;
            head1 = tail1;
            tail1 = temp;
        }
    }

    show(head0);
    show(head1);

    return 0;
}