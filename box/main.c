#include <stdio.h>

#include "box.hpp"
#include "list.hpp"

int main() {
    box* list   = list_ctor();
   // box* vector = VectorCtor();
   int dat = 5;
   printf("%d\n", dat);
   //list_push(list, (int*)&dat);
   list -> push(list, (int*)&dat);
   dat = 6;

   //list_push(list, (int*)&dat);
   list -> push(list, (int*)&dat);
   printf("size = %d\n", list_size(list));
   printf("kek %d\n", *(int*) list -> item(list, 1));
   list -> erase (list);
   printf("size = %d\n", list_size(list));
    printf("hui sosi\n");
    list -> dtor(list);
    printf("size = %d\n", list -> size (list));
    //vector -> Dtor(vector);


    return 0;
}