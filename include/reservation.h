#ifndef reservation_h
#define reservation_h

typedef struct {
    int reservationid;
    int customerid;
    int roomid;
    char date[11]; // format: YYYY-MM-DD
} reservation;


void makeRes(reservation r);
int cancelRes(int id);
void generate();
reservation* loadres(int *count);
void freer(reservation *list);

#endif