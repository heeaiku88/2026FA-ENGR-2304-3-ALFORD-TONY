/* 
2026FA-ENGR-2304-3-ALFORD-TONY-P03
*/ 


#include<stdio.h>


//prototypes 
void iNputs(double eq[2][3]);
void mAths(double eq[2][3], double deter[3]);
void dIsplay(double deter[3]);



int main() {
    
    double eq[2][3];
    double deter[3];
    
    iNputs(eq);
    mAths(eq, deter);
    dIsplay(deter);
    

    return 0;
}


void iNputs(double eq[2][3]){
    printf("-------------Equation Solver-----------------");
    for (int i = 0; i < 2; i++){
        printf("Enter the x coefficient and press enter.");
        scanf("%lf", &eq[i][0]);
        printf("Enter the y coefficient and press enter.");
        scanf("%lf", &eq[i][1]);
        printf("Enter the equation's solution and press enter.");
        scanf("%lf", &eq[i][2]);
    }
}



void mAths(double eq[2][3], double deter[3] ){
    deter[0] = eq[0][0] * eq[1][1] - eq[1][0] * eq[0][1]; 
    deter[1] = eq[0][2] * eq[1][1] - eq[1][2] * eq[0][1];  
    deter[2] = eq[0][0] * eq[1][2] - eq[1][0] * eq[0][2];


}

void dIsplay(double deter[3]){
    if (deter[0] == 0) {
        printf("No unique solution.\n");
            }
            else{

            double x = deter[1] / deter[0];
            double y = deter[2] / deter[0];

            printf("Solution: x = %.2f, y = %.2f\n", x, y);
            }
}
