#include <stdio.h>
#include <stdlib.h>

/*from Dietel c-programming */
#include<stdio.h>
#include<stdlib.h>

struct queueNode {
        char data;
        struct queueNode *nextPtr;
};

/* make queueNode alias */
typedef struct queueNode QueueNode;
/* QueueNode pointer alias */
typedef QueueNode* QueueNodePtr;

void enqueue (QueueNodePtr *headPtr,QueueNodePtr *tailPtr, char value);
char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr);
int isEmpty(QueueNodePtr headPtr);
void printQueue(QueueNodePtr currentPtr);
void instructions(void);

int main(){
        QueueNodePtr headPtr=NULL;
        QueueNodePtr tailPtr=NULL;
        int choice;
        char item;

        instructions();
        printf(" ?");
        scanf("%d",&choice);

        while (choice != 3) {
                switch( choice ) {
                case 1:
                        printf("enter a character: ");
                        scanf("\n%c", &item);
                        enqueue(&headPtr,&tailPtr,item);
                        printQueue( headPtr);
                        break;
                case 2:
                        if ( !isEmpty( headPtr ) ) {
                                item = dequeue(&headPtr,&tailPtr);
                                printf( "%c dequeued.\n",item);
                                printQueue( headPtr);
                        }
                        break;

                default:
                        printf("invalid choice\n");
                        instructions();
                        break;
                }
                instructions();
                printf("choice ?");
                scanf("%d", &choice);
        }
                
                

        printf( "end of program\n");
        return 0;
}

void instructions(void){
        printf("enter 1 (enqueue)\n  2(dequeue )\n 3(end)\n");
}

void enqueue(QueueNodePtr *headPtr,QueueNodePtr *tailPtr, char value){
        QueueNodePtr newPtr;
        newPtr = malloc( sizeof( QueueNode ) );
        if( newPtr != NULL ){
                newPtr->data = value;
                newPtr->nextPtr= NULL;
                
                if (isEmpty(*headPtr)){
                        *headPtr = newPtr;
                }else {
                        (*tailPtr)->nextPtr = newPtr;
                }
                *tailPtr=newPtr;

        } else {
                printf("%c not enqueueed \n NOt enough memory\n",value);
        }
}

char dequeue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr){
        QueueNodePtr  tempPtr=*headPtr;
        char value = (*headPtr)->data;
        *headPtr=(*headPtr)->nextPtr;
        if ( *headPtr ==NULL)
                *tailPtr=NULL;
        free(tempPtr);
        return value;
}

int isEmpty( QueueNodePtr headPtr){
        return headPtr==NULL;
}

void printQueue( QueueNodePtr currentPtr ){
        if ( currentPtr == NULL){
                printf("Queue is empty\n");
        }else {
                printf("the queue contains\n");
                while (currentPtr !=NULL ){
                        printf ("%c --> ", currentPtr->data);
                        currentPtr= currentPtr->nextPtr;
                }
                printf("NULL\n\n");
        }
}

