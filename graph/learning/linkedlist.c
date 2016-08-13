/*from Dietel c-programming */
#include<stdio.h>
#include<stdlib.h>

struct listNode {
        char data;
        struct listNode *nextPtr;
};

/* make listNode alias */
typedef struct listNode ListNode;
/* ListNode pointer alias */
typedef ListNode* ListNodePtr;

void insert (ListNodePtr *sPtr, char value);
char delete(ListNodePtr *sPtr, char value);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
void instructions(void);

int main(){
        ListNodePtr startPtr=NULL;
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
                        insert(&startPtr,item);
                        printList( startPtr);
                        break;
                case 2:
                        if ( !isEmpty( startPtr ) ) {
                                printf( "enter character to be deleted: ");
                                scanf("\n%c", &item);
                                if ( delete( &startPtr, item) ) {
                                        printf( "%c deleted.\n",item);
                                        printList( startPtr);
                                } else {
                                        printf( "%c not founcd.\n\n",item);
                                }
                        }else {
                                printf ( "list is empty\n");
                        }
                        break;

                default:
                        printf("invalid choice\n");
                        instructions();
                        break;
                }
                printf("choice ?");
                scanf("%d", &choice);
        }
                
                

        printf( "end of program\n");
        return 0;
}

void instructions(void){
        printf("enter 1 (insert)\n  2(delete )\n 3(end)\n");
}

void insert(ListNodePtr *sPtr, char value){
        ListNodePtr newPtr,previousPtr,currentPtr;
        newPtr = malloc( sizeof( ListNode ) );
        if( newPtr != NULL ){
                newPtr->data = value;
                newPtr->nextPtr= NULL;

                previousPtr = NULL;
                currentPtr = *sPtr;
                /* traverse the list looking for insertion point */
                while( currentPtr != NULL && value > currentPtr->data ){
                        previousPtr = currentPtr;
                        currentPtr = currentPtr->nextPtr;
                }

                if (previousPtr == NULL){
                        newPtr->nextPtr = *sPtr;
                        *sPtr = newPtr;
                }else {
                        previousPtr->nextPtr = newPtr;
                        newPtr->nextPtr = currentPtr;
                }

        } else {
                printf("%c not inserted \n NOt enough memory\n",value);
        }
}

char delete( ListNodePtr *sPtr, char value){
        ListNodePtr  tempPtr,previousPtr,currentPtr;
        if ( value == (*sPtr )->data) {
                tempPtr = *sPtr;
                *sPtr = (*sPtr)->nextPtr;
                free ( tempPtr);
                return value;
        }else {
                previousPtr = *sPtr;
                currentPtr= (*sPtr)->nextPtr;

                while (currentPtr != NULL && currentPtr->data !=value){
                        previousPtr = currentPtr;
                        currentPtr= currentPtr->nextPtr;
                }

                if ( currentPtr != NULL){
                        tempPtr = currentPtr;
                        previousPtr->nextPtr = currentPtr->nextPtr;
                        free( tempPtr);
                        return value;
                }
        }
        return 0;
}

int isEmpty( ListNodePtr sPtr){
        return sPtr==NULL;
}

void printList( ListNodePtr currentPtr ){
        if ( currentPtr == NULL){
                printf("List is empty\n");
        }else {
                printf("the list contains\n");
                while (currentPtr !=NULL ){
                        printf ("%c --> ", currentPtr->data);
                        currentPtr= currentPtr->nextPtr;
                }
                printf("NULL\n\n");
        }
}

