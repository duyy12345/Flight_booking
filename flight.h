#ifndef FLIGHT_H
#define FLIGHT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_FLIGHTS 100
#define DATA_FILE "flights.txt"

typedef struct {
    int id;
    char destination[50];
    int totalSeats;
    int bookedSeats;
} Flight;

// Global variables (declared as extern so multiple files can use them)
extern Flight flights[MAX_FLIGHTS];
extern int flight_count;

// System Setup & I/O
void loadFlights();
void saveFlights();
int getValidInt(const char* prompt);

// Core Operations
void bookSeat();
void cancelBooking();

// Searching & Display
void searchFlight();
void showAvailableSeats();
void displayAllFlights();

// Statistics & Sorting
void showStatistics();
void sortFlightsMenu();

#endif