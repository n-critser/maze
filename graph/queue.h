#ifndef QUEUE_H_
#define QUEUE_H_


/*
  Original List adaptation from :  
  https://isis.poly.edu/kulesh/stuff/src/klist/
  Changed  from the original

  * other sources : 
  * Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
  * O(1) TX queue with built-in allocator for ST-Ericsson CW1200 drivers

 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "grid.h"

// defined in grid.h  struct vertex {int x;int y;};

struct cqueue{
	int                      to;
        struct list_head         queue;
        size_t                   queue_size;
        size_t                   queue_id;
	int                      from;
        struct vertex            spot;
};


int init_cqueue_t( struct cqueue *newQ){
        /* size_t q_size; */
        
        INIT_LIST_HEAD(&newQ->queue);
        newQ->queue_size=0;
        newQ->queue_id=0;
        return 0;
};

int show_queue_t( struct cqueue *newQ){
        if (!newQ)
                return 1;
        struct cqueue *tmp;
        struct list_head *iterator;
        printf("show_queue_t using list_for_each()\n");
	list_for_each(iterator, &newQ->queue){
                
		/* at this point: pos->next points to the next item's 'list' variable and 
		 * pos->prev points to the previous item's 'list' variable. Here item is 
		 * of type struct cqueue. But we need to access the item itself not the 
		 * variable 'list' in the item! macro list_entry() does just that. See "How
		 * does this work?" below for an explanation of how this is done.
		 */
                tmp= list_entry(iterator, struct cqueue, queue);

                /* given a pointer to struct list_head, type of data structure it is part of,
		  * and it's name (struct list_head's name in the data structure) it returns a
		  * pointer to the data structure in which the pointer is part of.
		  * For example, in the above line list_entry() will return a pointer to the
		  * struct cqueue item it is embedded in!
		  */

                /*printf("to= %d from= %d\n", tmp->to, tmp->from);*/
                printf("\nspot.x=%d spot.y=%d\n queue_id=%zd queue_size=%zd \n ",
                       tmp->spot.x,
                       tmp->spot.y,
                       tmp->queue_id,
                       tmp->queue_size);
	}
        return 0;
}

int enqueue_t(struct cqueue *newQ,struct vertex *vert){
        printf("enqueue_t called with vertex %d,%d\n",vert->x,vert->y);
        
        struct cqueue *tmp;
        /*size_t currentSize=(newQ->list.prev)->queue_size;
         */
        /*create a node to add to the queue */
        tmp= (struct cqueue *)malloc(sizeof(struct cqueue));
        /*
        printf("enter to and from:");
        scanf("%d %d", &tmp->to, &tmp->from);
        */
        tmp->spot.x = vert->x;
        tmp->spot.y = vert->y;
        tmp->queue_size= newQ->queue_size++;
        tmp->queue_id= newQ->queue_id++;
        /* add the new item 'tmp' to the list of items in mylist */
        list_add_tail(&(tmp->queue), &(newQ)->queue);
        return 0;
}

int queue_size(struct cqueue *newQ){
        /* use queue_id as size of queue since its analogous */
        struct cqueue *tmp;
        struct list_head *iterator,*q;
	printf("getting size of queue\n");
        size_t q_size=0;

	list_for_each_safe(iterator, q, &newQ->queue){
                
                tmp= list_entry(iterator, struct cqueue, queue);
                q_size=tmp->queue_id;
	}

        
        return (int)q_size;

        
}

struct vertex dequeue_t(struct cqueue *newQ){
        /*
          dequeue_t:
          remove the 1st item in the queue.
          then decrement the queue_id of each other element
          This wastes a lot of cpu cycles since all we need is to get the 1st entry and leave
         */
        struct vertex ver;
        struct cqueue *tmp;
        //struct cqueue *next;
        struct list_head *iterator,*q,*next;
	printf("dequeue_t decrement id\n");

        list_for_each_safe(iterator, q, &newQ->queue){
                tmp= list_entry(iterator, struct cqueue, queue);
                if (tmp->queue_id == 0 ){
                        tmp->queue_id=-1;
                        ver = tmp->spot;
                        list_del(iterator);
                        free(tmp);
                        
                }
                tmp->queue_id--;
	}

        //iterator=&newQ->queue;
        //printf(iterator);
        //printf("\n");
        //tmp=list_first_entry_or_null(iterator,struct cqueue,queue);
        //&newQ->queue = iterator->next;
        //next =  iterator->next;
        //&newQ->queue=next;
        printf("freeing vertex %d, %d\n", tmp->spot.x, tmp->spot.y);

        //iterator=NULL;
        //&newQ->queue=next;
        /* update the id of each element in queue */
        return ver;
}

int isEmpty_t(struct cqueue *newQ){
        return list_empty(&newQ->queue);
}

#endif
