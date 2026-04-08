#include "flight.h"

Flight flights[MAX_FLIGHTS];
int flight_count = 0;

// --- Helper Functions ---
int getValidInt(const char* prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        while(getchar() != '\n'); 
        printf("Invalid! Enter a number: ");
    }
    return value;
}

int findFlightIndex(int id) {
    for (int i = 0; i < flight_count; i++) {
        if (flights[i].id == id) return i;
    }
    return -1;
}

// --- Data Persistence ---
void loadFlights() {
    FILE *file = fopen(DATA_FILE, "r");
    if (!file) return; 
    
    flight_count = 0;
    while (fscanf(file, "%d,%49[^,],%d,%d\n", &flights[flight_count].id, flights[flight_count].destination, &flights[flight_count].totalSeats, &flights[flight_count].bookedSeats) == 4) {
        flight_count++;
    }
    fclose(file);
}

void saveFlights() {
    FILE *file = fopen(DATA_FILE, "w");
    if (!file) return;
    
    for (int i = 0; i < flight_count; i++) {
        fprintf(file, "%d,%s,%d,%d\n", flights[i].id, flights[i].destination, flights[i].totalSeats, flights[i].bookedSeats);
    }
    fclose(file);
}

// --- Booking and Cancellation ---
void bookSeat() {
    int idx = findFlightIndex(getValidInt("\nEnter flight ID: "));
    if (idx == -1) { printf("Flight not found.\n"); return; }

    int avail = flights[idx].totalSeats - flights[idx].bookedSeats;
    int seats = getValidInt("Enter number of seats to book: ");
    
    if (seats > 0 && seats <= avail) {
        flights[idx].bookedSeats += seats;
        printf("=> %d seat(s) booked successfully!\n", seats);
    } else {
        printf("=> Error: Invalid amount or overbooking. Only %d seats available.\n", avail);
    }
}

void cancelBooking() {
    int idx = findFlightIndex(getValidInt("\nEnter flight ID: "));
    if (idx == -1) { printf("Flight not found.\n"); return; }

    int seats = getValidInt("Enter number of seats to cancel: ");
    if (seats > 0 && seats <= flights[idx].bookedSeats) {
        flights[idx].bookedSeats -= seats;
        printf("=> %d seat(s) cancelled successfully.\n", seats);
    } else {
        printf("=> Error: Invalid amount.\n");
    }
}

// --- Advanced Search ---
void searchFlight() {
    char dest[50];
    printf("\nEnter destination: ");
    scanf("%49s", dest); 
    
    for (int i = 0; i < flight_count; i++) {
        if (strstr(flights[i].destination, dest)) {
            printf("- Match: ID %d | %s | Available: %d\n", flights[i].id, flights[i].destination, flights[i].totalSeats - flights[i].bookedSeats);
        }
    }
}

// --- Display Functions ---
void displayAllFlights() {
    printf("\n--- All Flights ---\n");
    for(int i = 0; i < flight_count; i++) {
        printf("ID: %d | Dest: %-10s | Total: %d | Booked: %d\n", flights[i].id, flights[i].destination, flights[i].totalSeats, flights[i].bookedSeats);
    }
}

void showAvailableSeats() {
    printf("\n--- Available Seats ---\n");
    for(int i = 0; i < flight_count; i++) {
        int avail = flights[i].totalSeats - flights[i].bookedSeats;
        if (avail > 0) printf("Flight %d (%s) : %d available\n", flights[i].id, flights[i].destination, avail);
    }
}

// --- Statistics ---
void showStatistics() {
    if (flight_count == 0) return;

    int total = 0, maxPass = 0, maxAvail = 0;

    for (int i = 0; i < flight_count; i++) {
        total += flights[i].bookedSeats;
        if (flights[i].bookedSeats > flights[maxPass].bookedSeats) maxPass = i;
        
        int avail = flights[i].totalSeats - flights[i].bookedSeats;
        int currentMaxAvail = flights[maxAvail].totalSeats - flights[maxAvail].bookedSeats;
        if (avail > currentMaxAvail) maxAvail = i;
    }

    printf("\n--- Statistics ---\n");
    printf("Total Flights: %d | Total Seats Booked: %d\n", flight_count, total);
    printf("Highest Passengers: Flight %d (%s)\n", flights[maxPass].id, flights[maxPass].destination);
    printf("Most Available Seats: Flight %d (%s)\n", flights[maxAvail].id, flights[maxAvail].destination);
}

// --- Sorting ---
int cmpDest(const void *a, const void *b) { return strcmp(((Flight*)a)->destination, ((Flight*)b)->destination); }
int cmpBook(const void *a, const void *b) { return ((Flight*)b)->bookedSeats - ((Flight*)a)->bookedSeats; }
int cmpAvail(const void *a, const void *b) { 
    Flight *f1 = (Flight*)a, *f2 = (Flight*)b;
    return (f2->totalSeats - f2->bookedSeats) - (f1->totalSeats - f1->bookedSeats); 
}

void sortFlightsMenu() {
    int choice = getValidInt("\nSort by: 1.Destination 2.Booked Seats 3.Available Seats: ");
    
    if (choice == 1) qsort(flights, flight_count, sizeof(Flight), cmpDest);
    else if (choice == 2) qsort(flights, flight_count, sizeof(Flight), cmpBook);
    else if (choice == 3) qsort(flights, flight_count, sizeof(Flight), cmpAvail);
    else { printf("Invalid choice.\n"); return; }
    
    printf("=> Flights sorted successfully.\n");
}