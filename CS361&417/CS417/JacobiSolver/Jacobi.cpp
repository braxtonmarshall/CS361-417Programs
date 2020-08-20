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
double* init_solution(int size);
void JacobiSolver(double** m, double* soln, int n, double error);

int main()
{
    /* Declarations */
    int size = 0;
    double error = 0.0;
    double** matrix=NULL;
    double* soln=NULL;
    std::string file;

    /* Parse File for Matrix & Vector Setup */
    std::cout << "File to solve: \n";
    std::cin >> file;
    size   = init_size(file);
    matrix = init_matrix(file, size);
    soln = init_solution(size);

    /* Display Matrices */
    MatrixDisplay(matrix, size);
    
    /* Jacobi Iteration */
    std::cout << "Enter a tolerable error: \n";
    std::cin >> error;
    JacobiSolver(matrix, soln, size, error);

    /* Delete Matrices*/
    MatrixDelete(matrix, size);
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
double* init_solution(int size)
{
    double* matrix = NULL;
    matrix = new double[size];
    for (int i=0; i < size; i++)
    {
        matrix[i] = 1;
    }

    return matrix;
}
void JacobiSolver(double** m, double* soln, int n, double error)
{   
    int error_reached = 0;
    double divisor = 0.0;
    double* soln_temp=NULL;
    double* soln_old=NULL;
    double* error_array=NULL;
    soln_temp = new double[n];
    soln_old = new double[n];
    error_array = new double[n];
    int count = 0;
    int error_count = 0;

    /* Initialize Old Solution Array */
    for (int i=0; i < n; i++)
    {
        soln_old[i] = 1;
    }
    /* Main Logic Loop */
    do
    {
        count += 1;
        std::cout << "Solution Run " << count << ":\t";

        /* Calculate new X1, X2, X3 */
        for (int i=0; i < n; i++)
        {   
            /* store solution values */
            divisor = m[i][i];
            /* calculate new solution values */
            for (int j=0; j<n; j++)
            {
                
                if (j == n-1)
                {
                    if (i != n-1)
                    {
                        soln_temp[i] = soln_temp[i] + (m[i][j] * soln_old[j]);
                    }
                    soln[i] = ((m[n][i] - soln_temp[i]) / divisor);

                    /* clear temp solution array */
                    soln_temp[i] = 0;
                }
                else if (j != i)
                {
                    soln_temp[i] = soln_temp[i] + (m[i][j] * soln_old[j]);
                }
            }
            std::cout << "X" << i+1 << ": " << soln[i] << "\t";
        }
        std::cout << "\n";

        /* Check Error */
        error_count = 0;
        //std::cout << "--> ";
        for (int i=0; i < n; i++)
        {
            error_array[i] = std::fabs(soln[i] - soln_old[i]);
            //std::cout << "X" << i+1 << " error: " << error_array[i] << "\t";
            if (error_array[i] < error)
            {
                error_count++;
            }
            if (error_count == n)
            {
                error_reached = 1;
            }
        }
        std::cout << "\n";
        /* Copy over Solution array to Solution_Old Array */
        for (int i=0; i<n; i++)
        {
            soln_old[i] = soln[i];
        }

    } while (error_reached == 0);

    /* Display Solution */
    std::ofstream outfile;
    outfile.open("q3.txt");
    count = 0;
    std::cout << "Final Solution:\t";
    for (int i=0; i<n; i++)
    {
        std::cout << "X" << i+1 << ": " << soln[i] << "\t";
        count++;
        outfile << soln[i] << " ";
        if (count % 10 == 0){
            outfile << "\n";
        }
    }
    std::cout << "\n";
    /* Delete Matrices */
    delete soln_temp;
    delete soln_old;
    delete soln;
}