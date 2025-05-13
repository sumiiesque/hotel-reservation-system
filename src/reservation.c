#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation.h"

void makeRes(reservation r) {
    FILE *fp = fopen("reservation.txt", "a");
    if (!fp) return;

    printf("Enter Reservation ID: "); scanf("%d", &r.reservationid);
    printf("Enter Customer ID: "); scanf("%d", &r.customerid);
    printf("Enter Room ID: "); scanf("%d", &r.roomid); getchar();
    printf("Enter Date (YYYY-MM-DD): ");
    fgets(r.date, sizeof(r.date), stdin);
    r.date[strcspn(r.date, "\n")] = 0;

    fprintf(fp, "%d %d %d %s\n", r.reservationid, r.customerid, r.roomid, r.date);
    fclose(fp);
}

int cancelRes(int id) {
    FILE *fp = fopen("reservation.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    reservation r;
    int found = 0;

    if (!fp || !tmp) return 0;

    while (fscanf(fp, "%d %d %d %s", &r.reservationid, &r.customerid, &r.roomid, r.date) != EOF) {
        if (r.reservationid == id) found = 1;
        else fprintf(tmp, "%d %d %d %s\n", r.reservationid, r.customerid, r.roomid, r.date);
    }

    fclose(fp); fclose(tmp);
    remove("reservations.txt");
    rename("temp.txt", "reservation.txt");

    return found;
}

void generate() {
    FILE *fp = fopen("reservation.txt", "r");
    reservation r;
    int count = 0;

    if (!fp) {
        printf("No reservations yet.\n");
        return;
    }

    while (fscanf(fp, "%d %d %d %s", &r.reservationid, &r.customerid, &r.roomid, r.date) != EOF) {
        count++;
        printf("Res ID: %d | Cust ID: %d | Room ID: %d | Date: %s\n", r.reservationid, r.customerid, r.roomid, r.date);
    }

    printf("Total Reservations: %d\n", count);
    fclose(fp);
}

reservation* loadres(int *count) {
    FILE *fp = fopen("reservation.txt", "r");
    reservation temp, *list = NULL;
    int capacity = 10;
    *count = 0;

    if (!fp) return NULL;

    list = malloc(capacity * sizeof(reservation));
    while (fscanf(fp, "%d %d %d %s", &temp.reservationid, &temp.customerid, &temp.roomid, temp.date) != EOF) {
        if (*count >= capacity) {
            capacity *= 2;
            list = realloc(list, capacity * sizeof(reservation));
        }
        list[(*count)++] = temp;
    }

    fclose(fp);
    return list;
}

void freer(reservation *list) {
    free(list);
}