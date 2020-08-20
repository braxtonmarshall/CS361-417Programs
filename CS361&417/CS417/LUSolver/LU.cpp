#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <cmath>

void MatrixDisplay(double** m, int n);
void MatrixDisplayTwo(double** m, int n, std::string s);
void MatrixDelete(double** m, int n);
int init_size(std::string s);
double** init_matrix(std::string s, int size);
double** init_LU(int size);
void Doolittle(double** m, double** lower, double** upper, int n);
void LUDecompSolver(double** m, double** lower, double** upper, int n);

std::string upperch = "U";
std::string lowerch = "L";
std::string matrixch = "M";

int main(){

    /* Declarations */
    int size = 0;
    double** matrix=NULL;
    double** lower=NULL;
    double** upper=NULL;
    std::string file;

    /* Parse File for Matrix & Vector Setup */
    std::cout << "File to solve: \n";
    std::cin >> file;
    size   = init_size(file);
    matrix = init_matrix(file, size);
    lower = init_LU(size);
    upper = init_LU(size);

    /* Find Lower and Upper Matrices using Doolittle Algorithm*/
    Doolittle(matrix, lower, upper, size);

    /* Display Matrices */
    MatrixDisplay(matrix, size);
    MatrixDisplayTwo(lower, size, lowerch);
    MatrixDisplayTwo(upper, size, upperch);

    /* Backsolve solution using Lower and Upper Matrices */
    LUDecompSolver(matrix, lower, upper, size);

    /* Delete Matrices*/
    MatrixDelete(matrix, size);
    MatrixDelete(lower, size);
    MatrixDelete(upper, size);
    return 0;
}

void MatrixDisplay(double** m, int n)
{   
    std::cout << "Displaying Matrix..\n";
    int i;
    for (i=0; i <= n; i++)
    {   
        if (i == n)
        {
            std::cout << "Displaying Vector..\n";
            for (int c = 0; c < n; c++)
            {   
                std::cout << "| " << "\t";
                std::cout << m[i][c] << "\t" << " |\n";
            }
        }
        else
        {   
            std::cout << "| ";
            for (int j=0; j < n; j++)
            {   
                std::cout.width (7);
                std::cout << std::left << std::setprecision(5) << m[i][j] << " ";
            }
            std::cout << "|\n";
        }
    }
}
void MatrixDisplayTwo(double** m, int n, std::string s)
{   
    if (s == "L")
    {
        std::cout << "Displaying Lower Matrix...\n";
    }
    else if (s == "U")
    {
        std::cout << "Displaying Upper Matrix...\n";
    }
    else
    {
        std::cout << "Displaying Matrix...\n";
    }
    for (int i=0; i < n; i++)
    {
        std::cout << "|\t";
        for (int j=0; j < n; j++)
        {
            std::cout << std::fixed << std::setprecision(7) << m[i][j] << "\t";
        }
        std::cout << "\t|\n";
    }
}
void MatrixDelete(double** m, int n)
{
    for (int i = 0; i < n+1; i++)
    {   
        delete m[i];
    }
    delete m;
}

int init_size(std::string s)
{   
    int n = 0;
    std::ifstream ifile (s);
    if (ifile.is_open())
    {
        ifile >> n;
        ifile.close();
    }
    return n;
}

double** init_matrix(std::string s, int size)
{   
    double** matrix = NULL;
    std::ifstream ifile (s);
    if (ifile.is_open())
    {
        ifile.ignore(256, '\n');
        matrix = new double*[size+1];
        for (int i=0; i < size+1; i++)
        {   
            matrix[i] = new double[size];
            for (int j=0; j<size; j++)
            {
                ifile >> matrix[i][j];
            }
        }
    }
    ifile.close();
    return matrix;
}
double** init_LU(int size)
{
    double** matrix = NULL;
    matrix = new double*[size+1];
    for (int i=0; i < size+1; i++)
    {
        matrix[i] = new double[size];
        for (int j=0; j<size; j++)
        {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}
void Doolittle(double** m, double** lower, double** upper, int n)
{
    for (int i = 0; i < n; i++)
    { 
  
        // Upper Triangular Matrix
        for (int k = i; k < n; k++)
        { 
            double sum = 0; 
            for (int j = 0; j < i; j++)
            {
                sum += (lower[i][j] * upper[j][k]); 
            }
            upper[i][k] = m[i][k] - sum; 
        } 
  
        // Lower Triangular Matrix 
        for (int k = i; k < n; k++)
        { 
            if (i == k)
            {
                lower[i][i] = 1;
            }
            else 
            { 
                double sum = 0; 
                for (int j = 0; j < i; j++)
                {
                    sum += (lower[k][j] * upper[j][i]); 
                } 
                lower[k][i] = (m[k][i] - sum) / upper[i][i]; 
            } 
        } 
    } 
}
void LUDecompSolver(double** m, double** lower, double** upper, int n)
{
    /* Create a temporary matrix to hold solution matrix y for Ly = b and solution matrix */
    double* tempmatrix = NULL;
    double* soln = NULL;
    tempmatrix = new double[n];
    soln = new double[n];
    for (int i=0; i < n; i++)
    {
        tempmatrix[i] = 0;
        soln[i] = 0;
    }
    /* Backsolve Ly = b, save results into temporary matrix y */
    for (int i=0; i < n; i++)
    {
        if (i == 0)
        {
                tempmatrix[i] = m[n][i];
        }
        else
        {
            for (int j=0; j < i; j++)
            {   
                if (j+1 == i)
                {
                    tempmatrix[i] = m[n][i] - (lower[i][j] * tempmatrix[j]) - tempmatrix[i];
                }
                else
                {
                    tempmatrix[i] = (lower[i][j] * tempmatrix[j]);
                }

            }
        } 
    }
    /* Backsolve Ux = y, save results into solution matrix*/
    for (int i = n-1; i >= 0; i--)
    {
        if (i == n-1)
        {
            soln[i] = tempmatrix[i] / upper[i][i];
        }
        else
        {
            for (int j=n-1; j>=i; j--)
            {
                if (j == i)
                {
                    soln[i] = ((tempmatrix[i] - soln[i]) / upper[i][j]);
                }
                else
                {
                    soln[i] = soln[i] + (upper[i][j] * soln[j]);
                }
            }
        }  
    }
    /* Display solution */
    std::ofstream outfile;
    int count = 0;
    outfile.open("qq2.txt");
    std::cout << "Displaying Solution Vector...\n";
    for (int i=0; i<n; i++)
    {
        std::cout << "|\t" << soln[i] << "\t|\n";
        count++;
        outfile << soln[i] << " ";
        if (count % 10 == 0)
        {
            outfile << "\n";
        }
    }
    /* Delete temporary matrix y and solution matrix x */
    delete tempmatrix;
    delete soln;
}





