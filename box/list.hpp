//
// Created by snumb on 13.02.2020.
//

#ifndef PUDGE_LIST_H
#define PUDGE_LIST_H

#include <stdlib.h>

typedef struct list_elem{
	void* data;

	struct list_elem* next;
	struct list_elem* prev;

} list_elem;

typedef struct list{
	box pack;

	int size;
	list_elem* front;
	list_elem* back;
} list;


int list_size(box* object)
{
	list* it =(list*) object;
	return it -> size;
}

list_elem* list_find(list* it, int index)
{
	list_elem* cur = it -> front;
	printf("it -> front has %d\n", *(int*) cur -> data);
	printf("%d\n", index);
	if (index == 0){
		return cur;
	}

	for (int i = 0; i < index; i++){
		if (cur -> next)
			cur = cur -> next;
		else {
			printf("The list size is less than %d!\n", index);
			return NULL;
		}
	}
	return cur;

}

void* list_item (box* obj, int index) {
	list* it = (list*) obj;
	list_elem* cur = list_find(it, index);
	return cur->data;
}

void list_swap(box* obj, int item_1, int item_2)
{
	list* it = (list*) obj;
	if (item_1 > it -> size || item_2 > it -> size){
		printf("The list size %d is less than %d or %d!\n", it -> size, item_1, item_2);
		return;
	}

	list_elem* first = list_find(it, item_1); //watch for (box*)
	list_elem* second = list_find(it, item_2);


	void* tmp = first->data;

	first->data = second->data;
	second->data = tmp;
}

void list_insert (box* object, int index, void* data) {
	list* it = (list*) object;
	if (index + 1 > it->size) {
		printf("The list size is less than %d!\n", index);
		return;
	}

	list_elem* cur = it->front;
	for (int i = 0; i < index; i++)
		cur = cur->next;

	list_elem* item = (list_elem*) malloc(sizeof(list_elem));
	item->data = data;
	item->prev = cur;
	item->next = cur->next;

	if (cur->next)
		cur->next->prev = item;

	cur->next = item;

	it->size++;
}

void list_push(box* object, void* data)
{
	list* it =(list*) object;
	list_elem* item = (list_elem*) malloc(sizeof(list_elem));
	//printf("what I push %d\n", *(int*) data);


	item -> data = data;
	item -> next = NULL;

	if (it -> size > 0){
		printf("front when i push %d\n", *(int*) it -> front -> data);
		item -> prev = it -> back;
		it -> back -> next = item;
		it -> back = item;
	}
	else{
		item -> prev = NULL;
		it -> front = item;
		it -> back = item;
	}
	printf("front when i pusheeeed %d\n", *(int*) it -> front -> data);

	it -> size++;
}

void list_pop(box* object)
{
	list* it =(list*) object;

	if (it -> size < 1){
		printf("Nothing to pop\n");
		return;
	}

	list_elem* cur = it -> back;

	if (it -> size != 1){
		it -> back = cur -> prev;
		it -> back -> next = NULL;

	}
	else {
		it -> back = NULL;
		it -> front = NULL;
	}

	it -> size--;
	free(cur);

}

void list_remove (box* object, int index) {
	list*  it = (list*) object;

	if (index + 1 >  it->size) {
		printf("The list size is less than %d!\n", index);

		return;
	}

	list_elem* cur =  it -> front;
	for (int i = 0; i < index; i++)
		cur = cur -> next;

	if (cur->prev)
		cur->prev->next = cur->next;

	else
		it->front = cur->next;

	if (cur->next)
		cur->next->prev = cur->prev;

	else
		it->back = cur->prev;

	free(cur);

	it->size--;
}

void list_erase(box* object){
	list*  it = (list*) object;

	if(it -> size == 0){
		return;
	}
	while(it -> size > 0)
		list_pop(object);
}

void list_dtor(box* object) {
	list* it = (list*) object;
	list_erase(object);
	free(object);
}
void list_dump(box* obj) {
    list* it = (list*) obj;

    printf("\n");

    printf("+------ list dump ------+\n");
    printf("|    size: %d\n", it->size);

    list_elem* cur = it->front;
    printf("|    front: ");
    if (it->front)
        printf("%d [%p]\n", *((int*)cur->data), (void*) cur);

    else
        printf("? [NULL]\n");


    cur = it->back;
    printf("|    back: ");
    if (it->front)
        printf("%d [%p]\n", *((int*)cur->data), (void*) cur);

    else
        printf("? [NULL]\n");

    printf("|    items: ");
    cur = it->front;
    if (cur) {
        printf("\n");

        for (int i = 0; i < it->size; i++) {
            printf("|        %d: %d [%p]\n", i,
                                             *((int *) cur->data),
                                             (void *) cur);
            cur = cur->next;
        }
    }

    else
        printf("?\n");

    printf("\n");
}

box* list_ctor() {
	list* it = (list*) malloc(sizeof(list));

	// list part
	it -> size = 0;
	it -> front = NULL;
	it -> back = NULL;

	// box part
	it -> pack.size = list_size;
	it -> pack.dump = list_dump;
	it -> pack.swap = list_swap;
	it -> pack.item = list_item;

	it -> pack.push = list_push;
	it -> pack.pop  = list_pop;

	it -> pack.insert = list_insert;
	it -> pack.remove = list_remove;
	it -> pack.erase  = list_erase;


	it -> pack.dtor = list_dtor;

	return (box*) it;
}


#endif //PUDGE_LIST_H
