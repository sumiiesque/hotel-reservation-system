#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rooms.h"

void addroom(room r) {
    FILE *fp = fopen("room.txt", "a");
    if (!fp) return;

    printf("Enter Room ID: "); scanf("%d", &r.roomid); getchar();
    printf("Enter Room Type: ");
    fgets(r.type, sizeof(r.type), stdin);
    r.type[strcspn(r.type, "\n")] = 0;

    printf("Enter Price: "); scanf("%f", &r.price);
    printf("Is Available (1=Yes, 0=No): "); scanf("%d", &r.available);

    fprintf(fp, "%d %s %.2f %d\n", r.roomid, r.type, r.price, r.available);
    fclose(fp);
}

void viewrooms() {
    FILE *fp = fopen("room.txt", "r");
    room r;

    if (!fp) return;

    while (fscanf(fp, "%d %s %f %d", &r.roomid, r.type, &r.price, &r.available) != EOF)
        printf("Room %d | Type: %s | Price: Rs %.2f | Available: %d\n", r.roomid, r.type, r.price, r.available);

    fclose(fp);
}

void Type(const char *type) {
    FILE *fp = fopen("room.txt", "r");
    room r;

    if (!fp) return;

    while (fscanf(fp, "%d %s %f %d", &r.roomid, r.type, &r.price, &r.available) != EOF)
        if (r.available && strcmp(r.type, type) == 0)
            printf("Room %d | Rs %.2f\n", r.roomid, r.price);

    fclose(fp);
}

void Price(float maxprice) {
    FILE *fp = fopen("room.txt", "r");
    room r;

    if (!fp) return;

    while (fscanf(fp, "%d %s %f %d", &r.roomid, r.type, &r.price, &r.available) != EOF)
        if (r.available && r.price <= maxprice)
            printf("Room %d | %s | Rs %.2f\n", r.roomid, r.type, r.price);

    fclose(fp);
}

room* loadrooms(int *count) {
    FILE *fp = fopen("room.txt", "r");
    room temp, *list = NULL;
    int capacity = 10;
    *count = 0;

    if (!fp) return NULL;

    list = malloc(capacity * sizeof(room));
    while (fscanf(fp, "%d %s %f %d", &temp.roomid, temp.type, &temp.price, &temp.available) != EOF) {
        if (*count >= capacity) {
            capacity *= 2;
            list = realloc(list, capacity * sizeof(room));
        }
        list[(*count)++] = temp;
    }

    fclose(fp);
    return list;
}

room* available(int *count) {
    int total;
    room *all = loadRooms(&total);
    if (!all) return NULL;

    room *avail = malloc(total * sizeof(room));
    *count = 0;

    for (int i = 0; i < total; i++) {
        if (all[i].available == 1)
            avail[(*count)++] = all[i];
    }

    free(all);
    return avail;
}

void freelistroom(room *list) {
    free(list);
}