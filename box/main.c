#include <stdio.h>

#include "box.hpp"
#include "list.hpp"
#include "vector.hpp"

int main() {

   box* vector = vector_ctor();
   box* list = list_ctor();
   int arr[5];
    for (int i = 0; i < 5; i++) {
        arr[i] = 2*i;
        list->push(list, (void*) &arr[i]);
    }

    int hey = 9;
    list->insert(list, 3, &hey);
    list->dump(list);
    
   int a[6];
    for (int i = 0; i < 5; i++) {
        a[i] = 2*i;
        vector->push(vector, &a[i]);
    }

    a[5] = 7;

    vector->insert(vector, 1, &a[5]);
    vector->dump(vector);

    //sort(vector);
    vector->dtor(vector);


   /*box* list   = list_ctor();
   int dat = 5;
   printf("%d\n", dat);
   list -> push(list, (int*)&dat);
   list -> dump(list);
   printf("kek %d\n", *(int*) list -> item(list, 0));
   dat = 3;
    list -> dump(list);
   dat = 6;
   list -> dump(list);
   //list_push(list, (int*)&dat);
   list -> push(list, (int*)&dat);
   list -> dump(list);
   printf("actual size = %d\n", list_size(list));
   printf("functional size = %d\n", list -> size (list));
   //printf("first %d second %d\n", *(int*) list -> front -> data, *(int*) list -> front -> next -> data);
   printf("kek %d\n", *(int*) list -> item(list, 0));
   list -> erase (list);
   printf("size = %d\n", list_size(list));
   printf("functional size = %d\n", list -> size (list));
    printf("hui sosi\n");
    list -> dtor(list);
    printf("size = %d\n", list -> size (list));
    //vector -> Dtor(vector);

*/
    return 0;
}
