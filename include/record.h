#ifndef record_h
#define record_h

typedef struct{
    int id;
    char name[50];
    char email[50];
    char pass[20];
}customer;

void addcustomer(customer c);
void viewcustomer();
customer* loadrec(int *count);
void freelistrec(customer *list);

#endif