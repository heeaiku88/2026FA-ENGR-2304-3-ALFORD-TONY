/*
2026FA-ENGR-2304-3-ALFORD-TONY-P04
*/

#include <stdio.h>
#include <stdlib.h>   
#include <time.h>   
#include <math.h>  
#define EPSILON 0.0005

//prototypes
void createValues(int ChargeValues[]);
void truncate3(double *x);
void solveCircuit(int ChargeValues[], double answers[]);
void displayCircuit(int ChargeValues[]);
void getAnswers(double user[]);
void circuitCompare(double user[], double answers[], int correct[]);
void displayResults(double user[], double answers[], int correct[]);
int showMenu(void);




int main(void)
{
    int    ChargeValues[4];  
    double answers[5];        
    double user[5];           
    int    correct[5];       
    int    choice; 
 
    srand(time(NULL));        

    do {
        createValues(ChargeValues);
        solveCircuit(ChargeValues, answers);
        displayCircuit(ChargeValues);
        getAnswers(user);
        circuitCompare(user, answers, correct);
        displayResults(user, answers, correct);
        choice = showMenu();
    } while (choice != 0);
 
    printf("Goodbye!\n");
    return 0;
}

void createValues(int ChargeValues[])
{
    ChargeValues[0] = rand() % 10 + 1;      // Vs: 1 to 10 volts

    for (int k = 1; k < 4; k++)
        ChargeValues[k] = rand() % 20 + 1;  // R1, R2, R3: 1 to 20 ohms
}

void truncate3(double *x)
{
    *x = trunc(*x * 1000.0 + 1e-9) / 1000.0;
}

void solveCircuit(int ChargeValues[], double answers[])
{
    double Vs = ChargeValues[0];
    double R1 = ChargeValues[1];   
    double R2 = ChargeValues[2];
    double R3 = ChargeValues[3];
    double D, i1, i2;

    
    D  = R1*R2 + R1*R3 + R2*R3;   
    i1 = Vs * (R2 + R3) / D;
    i2 = Vs * R2 / D;


    answers[0] = i1;
    answers[1] = i2;
    answers[2] = R1 * i1;          // v1
    answers[3] = R2 * (i1 - i2);   // v2
    answers[4] = R3 * i2;          // v3

    
    for (int k = 0; k < 5; k++)
        truncate3(&answers[k]);
}

void displayCircuit(int ChargeValues[])
{
    printf("\n========== CIRCUIT PROBLEM ==========\n\n");
    printf("   +--- R1 ---+--------+\n");
    printf("   |          |        |\n");
    printf("   Vs         R2       R3\n");
    printf("   |          |        |\n");
    printf("   +----------+--------+\n\n");

    printf("Vs = %d V\n", ChargeValues[0]);
    printf("R1 = %d ohms\n", ChargeValues[1]);
    printf("R2 = %d ohms\n", ChargeValues[2]);
    printf("R3 = %d ohms\n\n", ChargeValues[3]);

    printf("Solve for i1, i2, v1, v2, and v3.\n");
    printf("Enter answers to 3 decimal places (truncate, do not round).\n\n");
}

int showMenu(void)
{
    int choice;

    do {
        printf("\n1 = New problem\n0 = Exit\nChoice: ");
        scanf("%d", &choice);
    } while (choice != 0 && choice != 1);

    return choice;
}

void getAnswers(double user[])
{
    const char *labels[5] = {"i1 (A)", "i2 (A)", "v1 (V)", "v2 (V)", "v3 (V)"};

    for (int k = 0; k < 5; k++) {
        printf("Enter %s: ", labels[k]);
        scanf("%lf", &user[k]);
    }
}

void displayResults(double user[], double answers[], int correct[])
{
    const char *labels[5] = {"i1", "i2", "v1", "v2", "v3"};
    int score = 0;

    printf("\n============== RESULTS ==============\n");

    for (int k = 0; k < 5; k++) {
        if (correct[k]) {
            printf("%s: %.3f  -- Correct\n", labels[k], user[k]);
            score++;
        } else {
            printf("%s: %.3f  -- Incorrect (answer: %.3f)\n",
                   labels[k], user[k], answers[k]);
        }
    }

    if (score == 5)
        printf("\nSUCCESS! All 5 answers correct.\n");
    else
        printf("\nFAILURE: %d of 5 correct.\n", score);
}

void circuitCompare(double user[], double answers[], int correct[])
{
    for (int k = 0; k < 5; k++) {
        truncate3(&user[k]);
        if (fabs(user[k] - answers[k]) < EPSILON)
            correct[k] = 1;
        else
            correct[k] = 0;
    }
}