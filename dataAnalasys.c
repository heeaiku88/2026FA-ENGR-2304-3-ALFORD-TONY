/*
2026FA-ENGR-2304-3-ALFORD-TONY-P06
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_RECORDS  1300
#define DEFAULT_FILE "data.csv"
// enums
typedef enum {
    PLANT_L1, PLANT_L2, PLANT_L3, PLANT_L4, PLANT_L5, PLANT_L6,
    NUM_PLANTS
} Plant;

typedef enum {
    MENU_ANALYSIS = 1,
    MENU_REPORT,
    MENU_SEARCH_PLANT,
    MENU_SEARCH_ALL,
    MENU_EXIT
} MenuChoice;

//structures
typedef struct {
    int year, month, day;
    int units[NUM_PLANTS];
} ProductionRecord;

typedef struct {
    int    min, max, mode;
    double mean, median, variance, stdDev;
} PlantStats;


//prototypes
int        loadData(const char *filename, ProductionRecord records[], int maxRecords);
void       printRecord(const ProductionRecord *r);
void       bubbleSort(int arr[], int count);
PlantStats computeStats(const ProductionRecord records[], int count, Plant p);
void       plantAnalysis(const ProductionRecord records[], int count);
void       productionReport(const ProductionRecord records[], int count);
int        findDate(const ProductionRecord records[], int count, int year, int month, int day);
void       searchSinglePlant(const ProductionRecord records[], int count);
void       searchAllPlants(const ProductionRecord records[], int count);
void       showMenu(void);



int main(void)
{
    ProductionRecord records[MAX_RECORDS];
    int count, choice;

    count = loadData(DEFAULT_FILE, records, MAX_RECORDS);
    if (count < 0)
        return 1;

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n')       
                ;
            choice = 0;
        }

        switch (choice) {
            case MENU_ANALYSIS:
                plantAnalysis(records, count);
                break;
            case MENU_REPORT:
                productionReport(records, count);
                break;
            case MENU_SEARCH_PLANT:
                searchSinglePlant(records, count);
                break;
            case MENU_SEARCH_ALL:
                searchAllPlants(records, count);
                break;
            case MENU_EXIT:
                printf("\nGoodbye.\n");
                break;
            default:
                printf("\nInvalid choice. Please enter a number from 1 to 5.\n");
        }
    } while (choice != MENU_EXIT);

    return 0;
}

int loadData(const char *filename, ProductionRecord records[], int maxRecords)
{
    FILE *fp;
    char header[256];
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open \"%s\".\n", filename);
        return -1;
    }

    fgets(header, sizeof header, fp);

    while (count < maxRecords) {
        ProductionRecord *r = &records[count];

        if (fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d",
                   &r->year, &r->month, &r->day,
                   &r->units[PLANT_L1], &r->units[PLANT_L2], &r->units[PLANT_L3],
                   &r->units[PLANT_L4], &r->units[PLANT_L5], &r->units[PLANT_L6]) != 9)
            break;
        count++;
    }

    fclose(fp);
    return count;
}

void printRecord(const ProductionRecord *r)
{
    int p;

    printf("%04d-%02d-%02d  ", r->year, r->month, r->day);
    for (p = 0; p < NUM_PLANTS; p++)
        printf("L%d=%d  ", p + 1, r->units[p]);
    printf("\n");
}

void bubbleSort(int arr[], int count)
{
    int i, j, temp;

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

PlantStats computeStats(const ProductionRecord records[], int count, Plant p)
{
    PlantStats s;
    int col[MAX_RECORDS];
    int i, sum = 0, run, bestRun;
    double sqDiff = 0.0;

    for (i = 0; i < count; i++) {
        col[i] = records[i].units[p];
        sum += col[i];
    }
    s.mean = (double)sum / count;

    //sorting
    bubbleSort(col, count);

    s.min = col[0];
    s.max = col[count - 1];

    if (count % 2 == 1)
        s.median = col[count / 2];
    else
        s.median = (col[count / 2 - 1] + col[count / 2]) / 2.0;

    s.mode = col[0];
    bestRun = 1;
    run = 1;
    for (i = 1; i < count; i++) {
        if (col[i] == col[i - 1])
            run++;
        else
            run = 1;
        if (run > bestRun) {
            bestRun = run;
            s.mode = col[i];
        }
    }

    // pop variance and standard dev
    for (i = 0; i < count; i++) {
        double d = col[i] - s.mean;
        sqDiff += d * d;
    }
    s.variance = sqDiff / count;
    s.stdDev = sqrt(s.variance);

    return s;
}

void plantAnalysis(const ProductionRecord records[], int count)
{
    int p;

    printf("\nPLANT DATA ANALYSIS  (%d days of data)\n\n", count);
    printf("%-6s %4s %4s %5s %8s %8s %10s %8s\n",
           "Plant", "Min", "Max", "Mode", "Median", "Mean", "Variance", "Std Dev");
    printf("------------------------------------------------------------\n");

    for (p = 0; p < NUM_PLANTS; p++) {
        PlantStats s = computeStats(records, count, p);
        printf("L%-5d %4d %4d %5d %8.1f %8.2f %10.2f %8.2f\n",
               p + 1, s.min, s.max, s.mode, s.median, s.mean, s.variance, s.stdDev);
    }
}

void productionReport(const ProductionRecord records[], int count)
{
    PlantStats s;
    int p, i;
    int bestPlant = PLANT_L1, worstPlant = PLANT_L1;
    double bestMean, worstMean;
    int maxUnits = -1, maxUnitsRow = 0, maxUnitsPlant = 0;   
    int dayTotal, maxDayTotal = -1, maxDayRow = 0;

    
    s = computeStats(records, count, PLANT_L1);
    bestMean = worstMean = s.mean;
    for (p = 1; p < NUM_PLANTS; p++) {
        s = computeStats(records, count, p);
        if (s.mean > bestMean) {
            bestMean = s.mean;
            bestPlant = p;
        }
        if (s.mean < worstMean) {
            worstMean = s.mean;
            worstPlant = p;
        }
    }

    
    for (i = 0; i < count; i++) {
        dayTotal = 0;
        for (p = 0; p < NUM_PLANTS; p++) {
            if (records[i].units[p] > maxUnits) {
                maxUnits = records[i].units[p];
                maxUnitsRow = i;
                maxUnitsPlant = p;
            }
            dayTotal += records[i].units[p];
        }
        if (dayTotal > maxDayTotal) {
            maxDayTotal = dayTotal;
            maxDayRow = i;
        }
    }

    printf("\nPRODUCTION REPORT\n");
    printf("------------------------------------------------------------\n");
    printf("Best performing plant (overall):   L%d  (mean %.2f units/day)\n",
           bestPlant + 1, bestMean);
    printf("Worst performing plant (overall):  L%d  (mean %.2f units/day)\n",
           worstPlant + 1, worstMean);
    printf("Best single day for one plant:     L%d, %d units on %04d-%02d-%02d\n",
           maxUnitsPlant + 1, maxUnits, records[maxUnitsRow].year,
           records[maxUnitsRow].month, records[maxUnitsRow].day);
    printf("Best single day, all facilities:   %d units combined on %04d-%02d-%02d\n",
           maxDayTotal, records[maxDayRow].year, records[maxDayRow].month,
           records[maxDayRow].day);
}

int findDate(const ProductionRecord records[], int count, int year, int month, int day)
{
    int i;

    for (i = 0; i < count; i++) {
        if (records[i].year == year && records[i].month == month && records[i].day == day)
            return i;
    }
    return -1;
}

void searchSinglePlant(const ProductionRecord records[], int count)
{
    int plant, year, month, day, row;

    printf("\nSEARCH: SINGLE PLANT, SINGLE DATE\n");
    printf("Plant number (1-6): ");
    scanf("%d", &plant);
    if (plant < 1 || plant > NUM_PLANTS) {
        printf("Plant number must be from 1 to %d.\n", NUM_PLANTS);
        return;
    }

    printf("Date (year month day, e.g. 1995 6 10): ");
    scanf("%d %d %d", &year, &month, &day);

    row = findDate(records, count, year, month, day);
    if (row == -1)
        printf("No record found for %04d-%02d-%02d.\n", year, month, day);
    else
        printf("L%d produced %d units on %04d-%02d-%02d.\n",
               plant, records[row].units[plant - 1], year, month, day);
}

void searchAllPlants(const ProductionRecord records[], int count)
{
    int year, month, day, row;

    printf("\nSEARCH: ALL PLANTS, SINGLE DATE\n");
    printf("Date (year month day, e.g. 1995 6 10): ");
    scanf("%d %d %d", &year, &month, &day);

    row = findDate(records, count, year, month, day);
    if (row == -1)
        printf("No record found for %04d-%02d-%02d.\n", year, month, day);
    else
        printRecord(&records[row]);
}

void showMenu(void)
{
    printf("\n==============================================\n");
    printf("   MANUFACTURING PROCESS DATA ANALYSIS\n");
    printf("==============================================\n");
    printf("  1. Plant Data Analysis\n");
    printf("  2. Production Report\n");
    printf("  3. Search: one plant, one date\n");
    printf("  4. Search: all plants, one date\n");
    printf("  5. Exit\n");
    printf("----------------------------------------------\n");
    printf("Enter your choice (1-5): ");
}
