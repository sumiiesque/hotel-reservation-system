#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

void addcustomer(customer c) {
    FILE *fp = fopen("customer.txt", "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &c.id); getchar();

    printf("Enter Name: ");
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = 0;

    printf("Enter Email: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = 0;

    printf("Enter Password: ");
    fgets(c.pass, sizeof(c.pass), stdin);
    c.pass[strcspn(c.pass, "\n")] = 0;

    fprintf(fp, "%d %s %s %s\n", c.id, c.name, c.email, c.pass);
    fclose(fp);
    printf("Customer added.\n");
}

void viewcustomers() {
    FILE *fp = fopen("customer.txt", "r");
    customer c;

    if (!fp) {
        printf("Error reading file.\n");
        return;
    }

    while (fscanf(fp, "%d %s %s %s", &c.id, c.name, c.email, c.pass) != EOF)
        printf("ID: %d | Name: %s | Email: %s\n", c.id, c.name, c.email);

    fclose(fp);
}

customer* loadrec(int *count) {
    FILE *fp = fopen("customer.txt", "r");
    customer temp, *list = NULL;
    int capacity = 10;
    *count = 0;

    if (!fp) return NULL;

    list = malloc(capacity * sizeof(customer));

    while (fscanf(fp, "%d %s %s %s", &temp.id, temp.name, temp.email, temp.pass) != EOF) {
        if (*count >= capacity) {
            capacity *= 2;
            list = realloc(list, capacity * sizeof(customer));
        }
        list[(*count)++] = temp;
    }

    fclose(fp);
    return list;
}

void freelistrec(customer *list) {
    free(list);
}