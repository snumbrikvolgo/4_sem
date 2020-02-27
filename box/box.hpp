//
// created by snumb on 13.02.2020.
//

#ifndef pudge_box_h
#define pudge_box_h
typedef struct box{
    int (*size)     (struct box* object);

    void* (*item)   (struct box* object, int index);
    void  (*swap)   (struct box* object, int index_1, int index_2);

    void  (*push)   (struct box* object, void* data);
    void  (*pop)    (struct box* object);

    void  (*insert) (struct box* object, int index, void* data);
    void  (*remove) (struct box* object, int index);
    void  (*erase)  (struct box* object);

    void  (*dtor)   (struct box* object);
} box;
#endif //pudge_box_h
