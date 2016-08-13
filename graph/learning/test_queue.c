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
	struct list_head         list;
        struct list_head         queue;
        size_t                   queue_size;
        size_t                   queue_id;
	int                      from;
        struct vertex            spot;
};


int init_cqueue_t( struct cqueue *newQ){
        /* size_t q_size; */
        
        INIT_LIST_HEAD(&newQ->list);
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
        printf("traversing the list using list_for_each()\n");
	list_for_each(iterator, &newQ->list){
                
		/* at this point: pos->next points to the next item's 'list' variable and 
		 * pos->prev points to the previous item's 'list' variable. Here item is 
		 * of type struct cqueue. But we need to access the item itself not the 
		 * variable 'list' in the item! macro list_entry() does just that. See "How
		 * does this work?" below for an explanation of how this is done.
		 */
                tmp= list_entry(iterator, struct cqueue, list);

                /* given a pointer to struct list_head, type of data structure it is part of,
		  * and it's name (struct list_head's name in the data structure) it returns a
		  * pointer to the data structure in which the pointer is part of.
		  * For example, in the above line list_entry() will return a pointer to the
		  * struct cqueue item it is embedded in!
		  */

                /*printf("to= %d from= %d\n", tmp->to, tmp->from);*/
                printf("\nto= %d from= %d spot.x=%d spot.y=%d\n queue_id=%zd queue_size=%zd \n ",
                       tmp->to,
                       tmp->from,
                       tmp->spot.x,
                       tmp->spot.y,
                       tmp->queue_id,
                       tmp->queue_size);
	}
        return 0;
}

int enqueue_t(struct cqueue *newQ){
        struct cqueue *tmp;
        /*size_t currentSize=(newQ->list.prev)->queue_size;
         */
        /*create a node to add to the queue */
        tmp= (struct cqueue *)malloc(sizeof(struct cqueue));
        printf("enter to and from:");
        scanf("%d %d", &tmp->to, &tmp->from);
        tmp->spot.x = tmp->to+5;
        tmp->spot.y = tmp->from+6;
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
        struct list_head *iterator,*q;
	printf("deleting the list using list_for_each_safe()\n");
        tmp=list_first_entry_or_null(iterator,struct cqueue,queue);
        printf("freeing item to= %d from= %d\n", tmp->to, tmp->from);
        ver = tmp->spot;
        list_del(iterator);
        free(tmp);
        /* update the id of each element in queue */
	list_for_each_safe(iterator, q, &newQ->queue){
                tmp= list_entry(iterator, struct cqueue, queue);
                tmp->queue_id--;
	}
        return ver;
}

int isEmpty_t(struct cqueue *newQ){
        return list_empty(&newQ->queue);
}

int main(int argc, char **argv){

	struct cqueue *tmp;
	struct list_head *pos, *q;
	unsigned int i;

	struct cqueue mylist;
        init_cqueue_t(&mylist);
	
	/* or you could have declared this with the following macro
	 * LIST_HEAD(mylist); which declares and initializes the list
	 */

	/* adding elements to mylist */
	for(i=5; i!=0; --i){


                enqueue_t(&mylist);
                
		/* INIT_LIST_HEAD(&tmp->list); 
		 *
		 * this initializes a dynamically allocated list_head. we
		 * you can omit this if subsequent call is add_list() or 
		 * anything along that line because the next, prev
		 * fields get initialized in those functions.
		 */

		/* add the new item 'tmp' to the list of items in mylist */

                /* list_add_tail(&(tmp->list), &(mylist.list)); */
                
                /* you can also use list_add() which adds new items to
		 * the list
		 */
	}
	printf("\n");

        show_queue_t(&mylist);

        /* remove one entry from queue */
        struct vertex cur_vert= dequeue_t(&mylist);
        printf ("cur_vert.x = %d cur_vert.y = %d", cur_vert.x ,cur_vert.y);

        show_queue_t(&mylist);
	/* now you have a circularly linked list of items of type struct cqueue.
	 * now let us go through the items and print them out
	 */


	/* list_for_each() is a macro for a for loop. 
	 * first parameter is used as the counter in for loop. in other words, inside the
	 * loop it points to the current item's list_head.
	 * second parameter is the pointer to the list. it is not manipulated by the macro.
	 */
	printf("traversing the list using list_for_each()\n");
	list_for_each(pos, &mylist.list){

		/* at this point: pos->next points to the next item's 'list' variable and 
		 * pos->prev points to the previous item's 'list' variable. Here item is 
		 * of type struct cqueue. But we need to access the item itself not the 
		 * variable 'list' in the item! macro list_entry() does just that. See "How
		 * does this work?" below for an explanation of how this is done.
		 */
		 tmp= list_entry(pos, struct cqueue, list);

		 /* given a pointer to struct list_head, type of data structure it is part of,
		  * and it's name (struct list_head's name in the data structure) it returns a
		  * pointer to the data structure in which the pointer is part of.
		  * For example, in the above line list_entry() will return a pointer to the
		  * struct cqueue item it is embedded in!
		  */

		 printf("to= %d from= %d\n", tmp->to, tmp->from);

	}
	printf("\n");
	/* since this is a circularly linked list. you can traverse the list in reverse order
	 * as well. all you need to do is replace 'list_for_each' with 'list_for_each_prev'
	 * everything else remain the same!
	 *
	 * Also you can traverse the list using list_for_each_entry() to iterate over a given
	 * type of entries. For example:
	 */
	printf("traversing the list using list_for_each_entry()\n");
	list_for_each_entry(tmp, &mylist.list, list)
                printf("\nto= %d from= %d spot.x=%d spot.y=%d\n queue_size=%zu ", tmp->to, tmp->from,tmp->spot.x,tmp->spot.y,tmp->queue_size);
	printf("\n");
	

	/* now let's be good and free the cqueue items. since we will be removing items
	 * off the list using list_del() we need to use a safer version of the list_for_each() 
	 * macro aptly named list_for_each_safe(). Note that you MUST use this macro if the loop 
	 * involves deletions of items (or moving items from one list to another).
	 */
	printf("deleting the list using list_for_each_safe()\n");
	list_for_each_safe(pos, q, &mylist.list){
		 tmp= list_entry(pos, struct cqueue, list);
		 printf("freeing item to= %d from= %d\n", tmp->to, tmp->from);
		 list_del(pos);
		 free(tmp);
	}

	return 0;
}
