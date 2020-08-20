#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<math.h>
#include <string.h>
#include <fstream>
#include <cmath>

int init_size(std::string s);
double** init_matrix(std::string s, int size);
double* init_guess(int size);
int main()
{
   /* Declarations */
   int size = 0;
   double error = 0.0;
   double** matrix=NULL;
   double* guess=NULL;
   std::string file;
   float temp, lambda_new, lambda_old;
   int i,j,step=1;
   /* Parse File for Matrix & Vector Setup */
   std::cout << "File to solve: \n";
   std::cin >> file;
   size   = init_size(file);
   matrix = init_matrix(file, size);
   guess = init_guess(size);

   double* guess_new= new double[size];
   /* Setting precision and writing floating point values in fixed-point notation. */
   std::cout<< std::setprecision(3)<< std::fixed;


   /* Reading tolerable error */
   std::cout<<"Enter Tolerable Error: ";
   std::cin>>error;


   /* Initializing Lambda_Old */
   lambda_old = 1;
   /* Multiplication */

   /* Setting label for repetition */
   up:
   for(i=1;i<=size;i++)
   {
      temp = 0.0;
      for(j=1;j<=size;j++)
      {
        temp = temp + matrix[i][j]*guess[j];
      }
      guess_new[i] = temp;
   }

   /* Replacing x by x_new */
   for(i=1;i<=size;i++)
   {
      guess[i] = guess_new[i];
   }

   /* Finding largest value from x*/
   lambda_new = fabs(guess[1]);
   for(i=2;i<=size;i++)
   {
      if(fabs(guess[i])>lambda_new)
      {
        lambda_new = fabs(guess[i]);
      }
   }

   /* Normalization */
   for(i=1;i<=size;i++)
   {
      guess[i] = guess[i]/lambda_new;
   }

   /* Display */
   std::cout<< std::endl<< std::endl<<"STEP-"<< step<< std::endl;
   std::cout<<"Eigen Value = "<< lambda_new<< std::endl;
   std::cout<<"Eigen Vector: "<< std::endl;
   std::cout<<"[";
   for(i=1;i<=size;i++)
   {
      std::cout<< guess[i]<<"\t";
   }
     std::cout<<"\b\b\b]"; /* \b is for backspace */

   /* Checking Accuracy */
   if(fabs(lambda_new-lambda_old)>error)
   {
      lambda_old=lambda_new;
      step++;
      goto up;
   }
   else
   {
      int count = 0;
      std::ofstream outfile;
      outfile.open("q5.txt");
      for(i=1; i<size; i++)
      {
         count++;
         outfile << guess[i] << " ";
         if (count % 10 == 0)
         {
            outfile << "\n";
         }
      }
   }
   return(0);
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
double* init_guess(int size)
{
    double* matrix = NULL;
    matrix = new double[size];
    for (int i=0; i < size; i++)
    {
        matrix[i] = 1;
    }

    return matrix;
}