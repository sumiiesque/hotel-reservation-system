#ifndef rooms_h
#define rooms_h

typedef struct {
    int roomid;
    char type[20];
    float price;
    int available;
} room;

void addroom(room r);
void viewrooms();
void Type(const char *type);
void Price(float maxprice);
room* loadrooms(int *count);
room* available(int *count);
void freelistroom(room *list);


#endif