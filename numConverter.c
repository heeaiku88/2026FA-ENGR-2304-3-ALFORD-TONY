/*
2026FA-ENGR-2304-3-ALFORD-TONY-P02
*/

#include <stdio.h>
#include <string.h>

// Prototypes
char Bits2HexChar(int val);
void PrintHexChar2Bin(char hex);
void DecVSbin(void);
void Dec2Bin(void);
void Bin2Dec(void);
void HexVSbin(void);
int DetectHexMode(const char *usrStr, int *indxStrt);
int FindDotIndex(const char *usrStr, int indxStrt, int len);
void Hex2Bin(const char *usrStr, int indxStrt, int wholEnd, int indxDot, int len);
void Bin2Hex(const char *usrStr, int indxStrt, int wholEnd, int indxDot, int len);

int main() {
    char menOpt[20];

    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Decimal/Binary Conversions (Base 10)\n");
        printf("2. Hex/Binary Fraction Conversions\n");
        printf("Type 'exit' to quit.\n");
        printf("Enter choice: ");
        scanf("%s", menOpt);

        if (strcmp(menOpt, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        if (strcmp(menOpt, "1") == 0) {
            DecVSbin();
        } else if (strcmp(menOpt, "2") == 0) {
            HexVSbin();
        } else {
            printf("Invalid selection.\n");
        }
    }
    return 0;
}

// Decimal to Binary Submenu
void DecVSbin(void) {
    int subOpt;
    int ok;
    printf("\n--- Option 1 Sub-Menu ---\n");
    printf("1. Decimal to Binary (-127 to 127)\n");
    printf("2. Binary to Decimal\n");

    // validation
    do {
        printf("Choice: ");
        ok = scanf("%d", &subOpt);
        if (ok != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            printf("Invalid input, try again.\n");
        } else if (subOpt != 1 && subOpt != 2) {
            printf("Invalid choice, try again.\n");
        }
    } while (ok != 1 || (subOpt != 1 && subOpt != 2));

    if (subOpt == 1) {
        Dec2Bin();
    } else {
        Bin2Dec();
    }
}

// Decimal to binary
void Dec2Bin(void) {
    int decVal;
    int ok;

    // Validation
    do {
        printf("Enter decimal (-127 to 127): ");
        ok = scanf("%d", &decVal);
        if (ok != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            printf("Error: invalid input. Try again.\n");
        } else if (decVal < -127 || decVal > 127) {
            printf("Error: Out of range. Try again.\n");
        }
    } while (ok != 1 || decVal < -127 || decVal > 127);

    if (decVal < 0) {
        printf("1");
        decVal = -decVal;
    } else {
        printf("0");
    }
    for (int plc = 64; plc >= 1; plc /= 2) {
        if (decVal >= plc) {
            printf("1");
            decVal -= plc;
        } else {
            printf("0");
        }
    }
    printf("\n");
}

// Binary to Decimal
void Bin2Dec(void) {
    int rawBin;
    printf("Enter binary integer: ");
    scanf("%d", &rawBin);

    // sign flag
    int isNeg = 0;
    if (rawBin >= 10000000) {
        isNeg = 1;
        rawBin %= 10000000;
    }

    int decFinal = 0;
    int multi = 1;
    while (rawBin > 0) {
        decFinal += (rawBin % 10) * multi;
        rawBin /= 10;
        multi *= 2;
    }
    if (isNeg) decFinal = -decFinal;
    printf("Decimal Output: %d\n", decFinal);
}

// hex to binary Submenu
void HexVSbin(void) {
    char usrStr[100];
    printf("\nEnter positive Binary or Hex number (Hex starts with 0x): ");
    scanf("%s", usrStr);

    int indxStrt = 0;
    int isHex = DetectHexMode(usrStr, &indxStrt);

    int len = strlen(usrStr);
    int indxDot = FindDotIndex(usrStr, indxStrt, len);

    int wholEnd = (indxDot == -1) ? len : indxDot;

    if (isHex) {
        Hex2Bin(usrStr, indxStrt, wholEnd, indxDot, len);
    } else {
        Bin2Hex(usrStr, indxStrt, wholEnd, indxDot, len);
    }
}

// check for 0x 
int DetectHexMode(const char *usrStr, int *indxStrt) {
    int isHex = 0;
    if (usrStr[0] == '0' && (usrStr[1] == 'x' || usrStr[1] == 'X')) {
        isHex = 1;
        *indxStrt = 2; // skip 0x
    }
    return isHex;
}

// find decimal point
int FindDotIndex(const char *usrStr, int indxStrt, int len) {
    int indxDot = -1;
    for (int i = indxStrt; i < len; i++) {
        if (usrStr[i] == '.') {
            indxDot = i;
            break;
        }
    }
    return indxDot;
}

// Hex to Binary
void Hex2Bin(const char *usrStr, int indxStrt, int wholEnd, int indxDot, int len) {
    printf("Binary Result: ");
    // whole part
    for (int i = indxStrt; i < wholEnd; i++) {
        PrintHexChar2Bin(usrStr[i]);
    }
    // fraction, if any
    if (indxDot != -1) {
        printf(".");
        for (int i = indxDot + 1; i < len; i++) {
            PrintHexChar2Bin(usrStr[i]);
        }
    }
    printf("\n");
}

// Binary to Hex
void Bin2Hex(const char *usrStr, int indxStrt, int wholEnd, int indxDot, int len) {
    printf("Hex Result: 0x");

    // whole part, grouped into nibbles
    int wholeLen = wholEnd - indxStrt;
    int pad = (4 - (wholeLen % 4)) % 4; // leading zero pad?

    int curVal = 0;
    int bitCntr = 0;

    // account for pad zeros
    for (int i = 0; i < pad; i++) {
        bitCntr++;
    }

    // build number
    for (int i = indxStrt; i < wholEnd; i++) {
        curVal = (curVal * 2) + (usrStr[i] - '0');
        bitCntr++;
        if (bitCntr == 4) {
            printf("%c", Bits2HexChar(curVal));
            curVal = 0;
            bitCntr = 0;
        }
    }

    // handles remainder (ifneeded)
    if (indxDot != -1) {
        printf(".");
        curVal = 0;
        bitCntr = 0;

        for (int i = indxDot + 1; i < len; i++) {
            curVal = (curVal * 2) + (usrStr[i] - '0');
            bitCntr++;
            if (bitCntr == 4) {
                printf("%c", Bits2HexChar(curVal));
                curVal = 0;
                bitCntr = 0;
            }
        }
        // pad trailing zeros(if needed)
        if (bitCntr > 0) {
            while (bitCntr < 4) {
                curVal = curVal * 2;
                bitCntr++;
            }
            printf("%c", Bits2HexChar(curVal));
        }
    }
    printf("\n");
}

// 4 bits to hex char
char Bits2HexChar(int val) {
    if (val >= 0 && val <= 9) return '0' + val;
    return 'A' + (val - 10);
}

// hex char to 4 bits
void PrintHexChar2Bin(char hex) {
    int val = 0;
    if (hex >= '0' && hex <= '9') val = hex - '0';
    else if (hex >= 'A' && hex <= 'F') val = hex - 'A' + 10;
    else if (hex >= 'a' && hex <= 'f') val = hex - 'a' + 10;

    // place values 8,4,2,1
    for (int plc = 8; plc >= 1; plc /= 2) {
        if (val >= plc) {
            printf("1");
            val -= plc;
        } else {
            printf("0");
        }
    }
}
