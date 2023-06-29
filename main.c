#include <stdio.h>

#define ROWS 25
#define COLS 7

typedef struct {
    int row;
    int col;
    int isAvailable;
} Seat;

void initializeSeats(Seat seats[ROWS][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            seats[i][j].row = i;
            seats[i][j].col = j;
            seats[i][j].isAvailable = 1; // 1 represents an available seat
        }
    }
}

void displaySeats(Seat seats[ROWS][COLS]) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%c ", seats[i][j].isAvailable ? 'O' : 'X'); // O represents an available seat, X represents an occupied seat
        }
        printf("\n");
    }
}

int reserveSeat(Seat seats[ROWS][COLS], int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid seat coordinates!\n");
        return 0;
    }

    if (seats[row][col].isAvailable) {
        seats[row][col].isAvailable = 0; // Mark the seat as occupied
        printf("Seat at Row %d, Column %d has been reserved.\n", row, col);
        return 1;
    } else {
        printf("Seat at Row %d, Column %d is already occupied.\n", row, col);
        return 0;
    }
}

int releaseSeat(Seat seats[ROWS][COLS], int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid seat coordinates!\n");
        return 0;
    }

    if (!seats[row][col].isAvailable) {
        seats[row][col].isAvailable = 1; // Mark the seat as available
        printf("Seat at Row %d, Column %d has been released.\n", row, col);
        return 1;
    } else {
        printf("Seat at Row %d, Column %d is already available.\n", row, col);
        return 0;
    }
}

int main() {
    Seat seats[ROWS][COLS];

    initializeSeats(seats);
    displaySeats(seats);

    // Reserve and release example seats
    reserveSeat(seats, 3, 4);
    reserveSeat(seats, 7, 2);
    reserveSeat(seats, 3, 4); // Trying to reserve the same seat again
    reserveSeat(seats, 14,2);
    reserveSeat(seats, 20,1);
    reserveSeat(seats, 25,7);
    releaseSeat(seats, 7, 2);
    releaseSeat(seats, 20,1);
    releaseSeat(seats, 5, 5); // Trying to release an already available seat

    printf("\nUpdated Seat Availability:\n");
    displaySeats(seats);

    return 0;
}
