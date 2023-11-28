#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_BUSES 50
#define MAX_BOOKINGS 100

// Structures
typedef struct {
    int bus_id;
    char destination[50];
    int capacity;
    int booked_seats;
} Bus;

typedef struct {
    char username[20];
    char password[20];
} Employee;

typedef struct {
    int booking_id;
    int bus_id;
    char passenger_name[50];
} Booking;

// Function prototypes
int login(Employee employees[], int num_employees, char username[], char password[]);
void displayMenu();
void manageBuses(Bus *buses, int *num_buses);
void addBus(Bus *buses, int *num_buses);
void deleteBus(Bus *buses, int *num_buses);
void modifyBus(Bus *buses, int num_buses);
void viewAllBuses(Bus *buses, int num_buses);
void bookSeat(Bus *buses, int num_buses, Booking *bookings, int *num_bookings);
void displayBookingHistory(Booking *bookings, int num_bookings);
void saveBookingHistory(Booking *bookings, int num_bookings);
void cleanupMemory(Bus *buses, Booking *bookings);

int main() {
    Employee employees[] = {{"admin", "admin123"}};
    Bus *buses = NULL;
    int num_buses = 0;
    Booking *bookings = NULL;
    int num_bookings = 0;

    int logged_in = 0;
    char username[20], password[20];

    // Login loop
    do {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        logged_in = login(employees, sizeof(employees) / sizeof(employees[0]), username, password);

        if (!logged_in) {
            printf("Invalid username or password. Please try again.\n");
        }

    } while (!logged_in);

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                manageBuses(buses, &num_buses);
                break;
            case 2:
                bookSeat(buses, num_buses, bookings, &num_bookings);
                break;
            case 3:
                displayBookingHistory(bookings, num_bookings);
                break;
            case 4:
                saveBookingHistory(bookings, num_bookings);
                break;
            case 5:
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    // Clean up memory
    cleanupMemory(buses, bookings);

    return 0;
}

// Function definitions...

void cleanupMemory(Bus *buses, Booking *bookings) {
    free(buses);
    free(bookings);
}

int login(Employee employees[], int num_employees, char username[], char password[]) {
    for (int i = 0; i < num_employees; i++) {
        if (strcmp(username, employees[i].username) == 0 && strcmp(password, employees[i].password) == 0) {
            printf("Login successful. Welcome, %s!\n", username);
            return 1;
        }
    }
    return 0;
}

void displayMenu() {
    printf("\n     WELCOME TO NAKONS BUS STATION SYSTEM    \n");
    printf("\n===== Bus Station System Menu =====\n");
    printf("1. Manage Buses\n");
    printf("2. Book a Seat\n");
    printf("3. Display Booking History\n");
    printf("4. Save Booking History to File\n");
    printf("5. Exit\n");
}

void manageBuses(Bus *buses, int *num_buses) {
    int bus_choice;

    do {
        printf("\n===== Manage Buses =====\n");
        printf("1. Add Bus\n");
        printf("2. Delete Bus\n");
        printf("3. Modify Bus\n");
        printf("4. View All Buses\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &bus_choice);

        switch (bus_choice) {
            case 1:
                addBus(buses, num_buses);
                break;
            case 2:
                deleteBus(buses, num_buses);
                break;
            case 3:
                modifyBus(buses, *num_buses);
                break;
            case 4:
                viewAllBuses(buses, *num_buses);
                break;
            case 5:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (bus_choice != 5);
}

void addBus(Bus *buses, int *num_buses) {
    printf("\n===== Add Bus =====\n");

    if (*num_buses < MAX_BUSES) { // Check if there is space for a new bus
        buses = (Bus *)realloc(buses, (*num_buses + 1) * sizeof(Bus));
        if (buses == NULL) {
            fprintf(stderr, "Memory allocation failed for buses.\n");
            exit(EXIT_FAILURE);
        }

        printf("Enter Bus ID: ");
        scanf("%d", &buses[*num_buses].bus_id);

        printf("Enter Destination: ");
        scanf("%s", buses[*num_buses].destination);

        printf("Enter Capacity: ");
        scanf("%d", &buses[*num_buses].capacity);

        buses[*num_buses].booked_seats = 0;

        (*num_buses)++;
        printf("Bus added successfully!\n");
    } else {
        printf("Cannot add more buses. Maximum limit reached.\n");
    }
}

void deleteBus(Bus *buses, int *num_buses) {
    printf("\n===== Delete Bus =====\n");

    if (*num_buses > 0) { // Check if there are buses to delete
        int bus_id, found = 0;

        printf("Enter Bus ID to delete: ");
        scanf("%d", &bus_id);

        for (int i = 0; i < *num_buses; i++) {
            if (buses[i].bus_id == bus_id) {
                found = 1;

                // Remove the bus by shifting remaining buses
                for (int j = i; j < *num_buses - 1; j++) {
                    buses[j] = buses[j + 1];
                }

                buses = (Bus *)realloc(buses, (*num_buses - 1) * sizeof(Bus));
                if (buses == NULL && *num_buses > 1) {
                    fprintf(stderr, "Memory reallocation failed for buses.\n");
                    exit(EXIT_FAILURE);
                }

                (*num_buses)--;
                printf("Bus deleted successfully!\n");
                break;
            }
        }

        if (!found) {
            printf("Bus not found.\n");
        }
    } else {
        printf("No buses available to delete.\n");
    }
}

void modifyBus(Bus *buses, int num_buses) {
    printf("\n===== Modify Bus =====\n");

    if (num_buses > 0) { // Check if there are buses to modify
        int bus_id, found = 0;

        printf("Enter Bus ID to modify: ");
        scanf("%d", &bus_id);

        for (int i = 0; i < num_buses; i++) {
            if (buses[i].bus_id == bus_id) {
                found = 1;

                printf("Enter new Destination: ");
                scanf("%s", buses[i].destination);

                printf("Enter new Capacity: ");
                scanf("%d", &buses[i].capacity);

                printf("Bus modified successfully!\n");
                break;
            }
        }

        if (!found) {
            printf("Bus not found.\n");
        }
    } else {
        printf("No buses available to modify.\n");
    }
}

void viewAllBuses(Bus *buses, int num_buses) {
    printf("\n===== All Buses =====\n");
    printf("Bus ID\tDestination\tCapacity\tBooked Seats\n");
    for (int i = 0; i < num_buses; i++) {
        printf("%d\t%s\t%d\t%d\n", buses[i].bus_id, buses[i].destination, buses[i].capacity, buses[i].booked_seats);
    }
}

void bookSeat(Bus *buses, int num_buses, Booking *bookings, int *num_bookings) {
    printf("\n===== Book a Seat =====\n");

    int bus_id, num_seats;
    printf("Enter the Bus ID: ");
    scanf("%d", &bus_id);

    for (int i = 0; i < num_buses; i++) {
        if (buses[i].bus_id == bus_id) {
            printf("Enter the number of seats to book (available seats: %d): ", buses[i].capacity - buses[i].booked_seats);
            scanf("%d", &num_seats);

            if (num_seats > 0 && num_seats <= (buses[i].capacity - buses[i].booked_seats)) {
                buses[i].booked_seats += num_seats;

                bookings = (Booking *)realloc(bookings, (*num_bookings + 1) * sizeof(Booking));
                if (bookings == NULL) {
                    fprintf(stderr, "Memory allocation failed for bookings.\n");
                    exit(EXIT_FAILURE);
                }

                bookings[*num_bookings].booking_id = *num_bookings + 1;
                bookings[*num_bookings].bus_id = bus_id;
                printf("Enter passenger name: ");
                scanf("%s", bookings[*num_bookings].passenger_name);

                (*num_bookings)++;

                printf("Booking successful!\n");
            } else {
                printf("Invalid number of seats. Please try again.\n");
            }
            return;
        }
    }

    printf("Invalid Bus ID. Please try again.\n");
}

void displayBookingHistory(Booking *bookings, int num_bookings) {
    printf("\n===== Booking History =====\n");
    printf("Booking ID\tBus ID\tPassenger Name\n");
    for (int i = 0; i < num_bookings; i++) {
        printf("%d\t%d\t%s\n", bookings[i].booking_id, bookings[i].bus_id, bookings[i].passenger_name);
    }
}

void saveBookingHistory(Booking *bookings, int num_bookings) {
    FILE *file = fopen("booking_history.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "Booking ID\tBus ID\tPassenger Name\n");
    for (int i = 0; i < num_bookings; i++) {
        fprintf(file, "%d\t%d\t%s\n", bookings[i].booking_id, bookings[i].bus_id, bookings[i].passenger_name);
    }

    fclose(file);
    printf("Booking history saved to file successfully.\n");
}
