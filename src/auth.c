#include <stdio.h>
#include <string.h>
#include "record.h"
#include "auth.h"

int login(const char *email, const char *password) {
    FILE *fp = fopen("customer.txt", "r");
    customer c;

    if (fp == NULL) {
        printf("Unable to open customer.txt\n");
        return 0;
    }

    while (fscanf(fp, "%d %s %s %s", &c.id, c.name, c.email, c.pass) != EOF) {
        if (strcmp(c.email, email) == 0 && strcmp(c.pass, password) == 0) {
            fclose(fp);
            return 1;  //success
        }
    }

    fclose(fp);
    return 0;  //failed
}