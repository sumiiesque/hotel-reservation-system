#include <stdio.h>
#include <string.h>
#include "record.h"
#include "auth.h"
#include "rooms.h"
#include "reservation.h"

int main() {
    int choice;
    customer c;
    room r;
    reservation res;
    char email[50], password[20];
    int loggedin = 0;

    do {
        printf("\n--- HOTEL RESERVATION SYSTEM ---\n");
        printf("1. Register\n2. View Customers\n3. Login\n");
        printf("4. Add Room\n5. View Rooms\n6. Search by Type\n7. Search by Price\n");
        printf("8. Make Reservation\n9. View Available Rooms\n10. Cancel Reservation\n11. Generate Report\n0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice); getchar();

        switch (choice) {
            case 1: addcustomer(c); break;
            case 2: viewcustomer(); break;
            case 3:
                printf("Enter Email: "); fgets(email, sizeof(email), stdin); email[strcspn(email, "\n")] = 0;
                printf("Enter Password: "); fgets(password, sizeof(password), stdin); password[strcspn(password, "\n")] = 0;
                if (login(email, password)) { loggedin = 1; printf("Login successful.\n"); }
                else printf("Login failed.\n");
                break;
            case 4: if (loggedin) addroom(r); else printf("Login required.\n"); break;
            case 5: viewrooms(); break;
            case 6:
                printf("Enter Room Type: "); fgets(r.type, sizeof(r.type), stdin); r.type[strcspn(r.type, "\n")] = 0;
                Type(r.type); break;
            case 7:
                printf("Enter Max Price: "); float maxprice; scanf("%f", &maxprice); getchar();
                Price(maxprice); break;
            case 8:
                if (!loggedin) { printf("Login required.\n"); break; }
                printf("Enter Reservation ID, Customer ID, Room ID, Date (YYYY-MM-DD): ");
                scanf("%d %d %d", &res.reservationid, &res.customerid, &res.roomid); getchar();
                fgets(res.date, sizeof(res.date), stdin); res.date[strcspn(res.date, "\n")] = 0;
                makeRes(res); break;
            case 9: {
                int count; room* avail = Available(&count);
                for (int i = 0; i < count; i++)
                    printf("%d | %s | Rs %.2f\n", avail[i].roomid, avail[i].type, avail[i].price);
                freelistroom(avail); break;
            }
            case 10:
                printf("Enter Reservation ID to cancel: "); int resid; scanf("%d", &resid); getchar();
                if (cancelRes(resid)) printf("Reservation canceled.\n");
                else printf("Reservation not found.\n"); break;
            case 11: generate(); break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
    return 0;
}
