#include "flight.h"

int main() {
    // 5.1 Load Data on Startup
    loadFlights();
    
    if (flight_count == 0) {
        flights[0] = (Flight){101, "Tokyo", 100, 20};
        flights[1] = (Flight){102, "Seoul", 150, 149};
        flights[2] = (Flight){103, "New York", 200, 180};
        flight_count = 3;
        printf("Added initial test data.\n");
    }

    int choice;
    while(1) {
        printf("\n===================================\n");
        printf("       FLIGHT BOOKING SYSTEM       \n");
        printf("===================================\n");
        printf("1. View All Flights\n");
        printf("2. Book Seats\n");
        printf("3. Cancel Booking\n");
        printf("4. Search Flight (By Destination)\n");
        printf("5. Show Available Seats\n");
        printf("6. View System Statistics\n");
        printf("7. Sort Flights\n");
        printf("0. Save & Exit\n");
        printf("-----------------------------------\n");
        
        choice = getValidInt("Enter your choice: ");

        switch(choice) {
            case 1: displayAllFlights(); break;
            case 2: bookSeat(); break;
            case 3: cancelBooking(); break;
            case 4: searchFlight(); break;
            case 5: showAvailableSeats(); break;
            case 6: showStatistics(); break;
            case 7: sortFlightsMenu(); break;
            case 0:
                printf("\nSaving data...\n");
                saveFlights(); 
                printf("Exiting system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please select between 0 and 7.\n");
        }
    }
    return 0;
}