#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Define macros for constants
#define MAX_PRODUCTIONS 10
#define MAX_SYMBOLS 100

// Function prototypes
void followFirst(char, int, int);

void follow(char);

void findFirst(char, int, int);

// Global variables
int count, n = 0;
int m = 0;  // Initialize m for storing final result of sets

// Stores the production rules
char production[MAX_PRODUCTIONS][MAX_SYMBOLS];

// Stores the final result of the First Sets
char calc_first[MAX_PRODUCTIONS][MAX_SYMBOLS];

// Stores the final result of the Follow Sets
char calc_follow[MAX_PRODUCTIONS][MAX_SYMBOLS];

void init();

// Temporary arrays for storing sets
char f[MAX_SYMBOLS], first[MAX_SYMBOLS];

void printFirst();

void printFollow();

int main() {
    count = 9; // Number of production rules

    // The Input grammar
    strcpy(production[0], "S=ACB");
    strcpy(production[1], "S=CbB");
    strcpy(production[2], "S=Ba");
    strcpy(production[3], "A=da");
    strcpy(production[4], "A=BC");
    strcpy(production[5], "B=g");
    strcpy(production[6], "B=#");
    strcpy(production[7], "C=h");
    strcpy(production[8], "C=#");

    init();

    printFirst();

    printf("-----------------------------------------------\n\n");

    printFollow();
}

void printFirst() {
    int point2, xxx, ptr = -1, jm = 0, point1 = 0;
    char done[count];

    for (int k = 0; k < count; k++) {
        char c = production[k][0];
        point2 = 0;
        xxx = 0;

        // Checking if First of c has already been calculated
        for (int kay = 0; kay <= ptr; kay++)
            if (c == done[kay])
                xxx = 1;

        if (xxx == 1)
            continue;

        // Function call
        findFirst(c, 0, 0);
        ptr += 1;

        // Adding c to the calculated list
        done[ptr] = c;
        printf("\n First(%c) = { ", c);
        calc_first[point1][point2++] = c;

        // Printing the First Sets of the grammar
        for (int i = 0 + jm; i < n; i++) {
            int chk = 0;

            for (int lark = 0; lark < point2; lark++) {

                if (first[i] == calc_first[point1][lark]) {
                    chk = 1;
                    break;
                }
            }
            if (chk == 0) {
                printf("%c, ", first[i]);
                calc_first[point1][point2++] = first[i];
            }
        }
        printf("}\n");
        jm = n;
        point1++;
    }
    printf("\n");
}

void printFollow() {
    char donee[count];
    int xxx, point2, ptr = -1, point1 = 0, km = 0, land = 0;

    for (int e = 0; e < count; e++) {
        char ck = production[e][0];
        point2 = 0;
        xxx = 0;

        // Checking if Follow of ck has already been calculated
        for (int kay = 0; kay <= ptr; kay++)
            if (ck == donee[kay])
                xxx = 1;

        if (xxx == 1)
            continue;
        land += 1;

        // Function call
        follow(ck);
        ptr += 1;

        // Adding ck to the calculated list
        donee[ptr] = ck;
        printf(" Follow(%c) = { ", ck);
        calc_follow[point1][point2++] = ck;

        // Printing the Follow Sets of the grammar
        for (int i = 0 + km; i < m; i++) {
            int chk = 0;
            for (int lark = 0; lark < point2; lark++) {
                if (f[i] == calc_follow[point1][lark]) {
                    chk = 1;
                    break;
                }
            }
            if (chk == 0) {
                printf("%c, ", f[i]);
                calc_follow[point1][point2++] = f[i];
            }
        }
        printf(" }\n\n");
        km = m;
        point1++;
    }
}

void init() {
    // Initializing the calc_first and calc_follow array
    for (int k = 0; k < count; k++) {
        for (int kay = 0; kay < MAX_SYMBOLS; kay++) {
            calc_first[k][kay] = '!';
            calc_follow[k][kay] = '!';
        }
    }
}

void follow(char c) {
    // Adding "$" to the follow set of the start symbol
    if (production[0][0] == c)
        f[m++] = '$';

    for (int i = 0; i < MAX_PRODUCTIONS; i++) {
        for (int j = 2; j < MAX_SYMBOLS; j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0') {
                    // Calculate the first of the next Non-Terminal in the production
                    followFirst(production[i][j + 1], i, (j + 1)); // Adjust index to j+1
                }

                if (production[i][j + 1] == '\0' && c != production[i][0]) {
                    // Calculate the follow of the Non-Terminal in the L.H.S. of the production
                    follow(production[i][0]);
                }
            }
        }
    }
}

void findFirst(char c, int q1, int q2) {

    // The case where we encounter a Terminal
    if (!(isupper(c))) {
        first[n++] = c;
    }
    for (int j = 0; j < count; j++) {
        if (production[j][0] == c) {
            if (production[j][2] == '#') {
                if (production[q1][q2] != '\0' && (q1 != 0 || q2 != 0)) {
                    // Recursion to calculate First of New Non-Terminal we encounter after epsilon
                    findFirst(production[q1][q2], q1, (q2 + 1));
                } else
                    first[n++] = '#';
            } else if (!isupper(production[j][2])) {
                first[n++] = production[j][2];
            } else {
                // Recursion to calculate First of New Non-Terminal we encounter at the beginning
                findFirst(production[j][2], j, 2); // Adjust index to 2
            }
        }
    }
}

void followFirst(char c, int c1, int c2) {
    // The case where we encounter a Terminal
    if (!(isupper(c))) {
        f[m++] = c;
    } else {
        int i;
        // Find the index of the non-terminal in calc_first
        for (i = 0; i < count; i++) {
            if (calc_first[i][0] == c)
                break;
        }

        // Include the First set of the non-terminal in the Follow set
        for (int j = 1; calc_first[i][j] != '!'; j++) {
            if (calc_first[i][j] != '#') {
                f[m++] = calc_first[i][j];
            } else {
                // If epsilon found in First set, include Follow set of left symbol
                if (production[c1][c2] == '\0') {
                    // Case where we reach the end of a production
                    follow(production[c1][0]);
                } else {
                    // Recursion to the next symbol in case we encounter a "#"
                    followFirst(production[c1][c2], c1, c2 + 1);
                }
            }
        }

        // If First set contains epsilon and there's more symbols in the production
        if (calc_first[i][1] == '#' && production[c1][c2] != '\0') {
            // Include Follow set of left symbol
            follow(production[c1][0]);
        }
    }
}
