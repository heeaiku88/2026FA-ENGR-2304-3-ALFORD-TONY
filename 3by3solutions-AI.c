/*
2026FA-ENGR-2304-3-ALFORD-TONY-P03AI
*/

/*
THIS IS THE PROGRAM AS GENERTED BY CHATGPT
*/


#include <stdio.h>
#include <math.h>

#define EPSILON 1e-10

/*
    Calculates the determinant of a 3x3 matrix:

    | a b c |
    | d e f |
    | g h i |
*/
double determinant3x3(double m[3][3])
{
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
         - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
         + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

int main(void)
{
    double A[3][3];
    double b[3];

    double Ax[3][3];
    double Ay[3][3];
    double Az[3][3];

    double detA;
    double detX;
    double detY;
    double detZ;

    double x, y, z;

    double lhs;
    double residual;

    int i, j;

    printf("3x3 System Solver Using Cramer's Rule\n\n");
    printf("Enter each equation in the form:\n");
    printf("ax + by + cz = d\n\n");

    /*
        Read the three equations from the user.
    */
    for (i = 0; i < 3; i++)
    {
        printf("Equation %d\n", i + 1);

        printf("Coefficient of x: ");
        if (scanf("%lf", &A[i][0]) != 1)
            return 1;

        printf("Coefficient of y: ");
        if (scanf("%lf", &A[i][1]) != 1)
            return 1;

        printf("Coefficient of z: ");
        if (scanf("%lf", &A[i][2]) != 1)
            return 1;

        printf("Constant d: ");
        if (scanf("%lf", &b[i]) != 1)
            return 1;

        printf("\n");
    }

    /*
        Copy the coefficient matrix A into
        Ax, Ay, and Az.
    */
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            Ax[i][j] = A[i][j];
            Ay[i][j] = A[i][j];
            Az[i][j] = A[i][j];
        }
    }

    /*
        Cramer's Rule:

        Ax = A with the x column replaced
             by the constants.

        Ay = A with the y column replaced.

        Az = A with the z column replaced.
    */
    for (i = 0; i < 3; i++)
    {
        Ax[i][0] = b[i];
        Ay[i][1] = b[i];
        Az[i][2] = b[i];
    }

    /*
        Calculate all four determinants.
    */
    detA = determinant3x3(A);
    detX = determinant3x3(Ax);
    detY = determinant3x3(Ay);
    detZ = determinant3x3(Az);

    printf("Determinants:\n");
    printf("det(A)  = %.10f\n", detA);
    printf("det(Ax) = %.10f\n", detX);
    printf("det(Ay) = %.10f\n", detY);
    printf("det(Az) = %.10f\n\n", detZ);

    /*
        Cramer's Rule only gives a unique solution
        when det(A) is not zero.
    */
    if (fabs(detA) < EPSILON)
    {
        printf("No unique solution exists.\n");
        printf("det(A) is zero or extremely close to zero.\n");
        printf("The system may be inconsistent or may have infinitely many solutions.\n");

        return 0;
    }

    /*
        CRAMER'S RULE:

              det(Ax)
        x = ----------
               det(A)

              det(Ay)
        y = ----------
               det(A)

              det(Az)
        z = ----------
               det(A)
    */
    x = detX / detA;
    y = detY / detA;
    z = detZ / detA;

    printf("Solution using Cramer's Rule:\n");
    printf("x = %.10f\n", x);
    printf("y = %.10f\n", y);
    printf("z = %.10f\n\n", z);

    /*
        VALIDATION

        Substitute x, y, and z back into each
        original equation.

        residual = calculated LHS - expected RHS

        A residual close to zero means that the
        calculated solution satisfies the equation.
    */
    printf("Validation by substitution:\n\n");

    for (i = 0; i < 3; i++)
    {
        lhs = A[i][0] * x
            + A[i][1] * y
            + A[i][2] * z;

        residual = lhs - b[i];

        printf("Equation %d:\n", i + 1);
        printf("  Calculated LHS = %.10f\n", lhs);
        printf("  Expected RHS   = %.10f\n", b[i]);
        printf("  Residual       = %.3e\n", residual);

        if (fabs(residual) < 1e-8)
        {
            printf("  Validation: PASS\n");
        }
        else
        {
            printf("  Validation: FAIL\n");
        }

        printf("\n");
    }

    return 0;
}