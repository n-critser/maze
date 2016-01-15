/*
  compile : gcc -Wall -g test_mod_queue.c -o mod_queue

 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"


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
        struct vertex * v;
        v= (struct vertex *)malloc(sizeof(struct vertex));
	for(i=5; i!=0; --i){

                
                v->x = i+2;
                v->y = i+10;
                enqueue_t(&mylist,v);
                
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
        printf ("cur_vert.x = %d cur_vert.y = %d\n\n", cur_vert.x ,cur_vert.y);
        //return 0;
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
	list_for_each(pos, &mylist.queue){

		/* at this point: pos->next points to the next item's 'list' variable and 
		 * pos->prev points to the previous item's 'list' variable. Here item is 
		 * of type struct cqueue. But we need to access the item itself not the 
		 * variable 'list' in the item! macro list_entry() does just that. See "How
		 * does this work?" below for an explanation of how this is done.
		 */
		 tmp= list_entry(pos, struct cqueue, queue);

		 /* given a pointer to struct list_head, type of data structure it is part of,
		  * and it's name (struct list_head's name in the data structure) it returns a
		  * pointer to the data structure in which the pointer is part of.
		  * For example, in the above line list_entry() will return a pointer to the
		  * struct cqueue item it is embedded in!
		  */

		 printf("x= %d , y = %d\n", tmp->spot.x, tmp->spot.y);

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
	list_for_each_entry(tmp, &mylist.queue, queue)
                printf("\nspot.x=%d spot.y=%d\n queue_size=%zu ", tmp->spot.x,tmp->spot.y,tmp->queue_size);
	printf("\n");
	

	/* now let's be good and free the cqueue items. since we will be removing items
	 * off the list using list_del() we need to use a safer version of the list_for_each() 
	 * macro aptly named list_for_each_safe(). Note that you MUST use this macro if the loop 
	 * involves deletions of items (or moving items from one list to another).
	 */
	printf("deleting the list using list_for_each_safe()\n");
	list_for_each_safe(pos, q, &mylist.queue){
		 tmp= list_entry(pos, struct cqueue, queue);
		 list_del(pos);
		 free(tmp);
	}

	return 0;
}
