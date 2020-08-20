#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

void MatrixDisplay(double** m, int n);
void MatrixDelete(double** m, int n);
int init_size(std::string s);
double** init_matrix(std::string s, int size);
void GaussianSolver9000(double** m, int n);
void swap_row(double** m, int i, int k, int n);
void divide_row(double** m, int k, int n);
void forward_elim(double** m, int k, int n);
double* find_absvalue(double** m, int k, int n);
void backsolver500(double** m, int n);


int main(){

	/* Declarations */
	int size = 0;
	double** matrix=NULL;
	std::string file;
	/* Parse File for Matrix & Vector Setup */
	std::cout << "File to solve: \n";
	std::cin >> file;
	size   = init_size(file);
	matrix = init_matrix(file, size);
	/* Solve */
	GaussianSolver9000(matrix, size);
	/* Display Results*/
	//MatrixDisplay(matrix, size);
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

void MatrixDelete(double** m, int n)
{
	for (int i = 0; i < n+1; i++)
	{	
		delete m[i];
	}
	delete m;
}

void GaussianSolver9000(double** m, int n)
{
	double abval = 0;
	double* row_retriever = NULL;
	int row = 0;
	for (int k = 0; k < n; k++)
	{	
		/* find Absolute Value */
		row_retriever = find_absvalue(m, k, n);
		abval = row_retriever[0];
		row = row_retriever[1];
		delete row_retriever;
		if (abval == 0.0)
		{
			/*if (m[n][k] == 0.0)
			{
				std::cout << " Matrix has infinite solutions... Returning...\n";
				return;
			}
			else
			{
				std::cout << " Matrix is inconsistent... Returning...\n";
				return;
			}
			*/
		}
		/* Swap */
		swap_row(m, row, k, n);
		/* Divide */
		divide_row(m, k, n);
		/* eliminate values */
		if (k < (n-1)){forward_elim(m, k, n);}
	}
	backsolver500(m, n);
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
		//ifile.ignore(256, '\n');
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

void swap_row(double** m, int i, int k, int n)
{
	double* swapper = NULL;
	double swapperv = 0.0;
	/*Matrix*/
	swapper = m[k];
	m[k] = m[i];
	m[i] = swapper;
	/* Vector */
	swapperv = m[n][k];
	m[n][k] = m[n][i];
	m[n][i] = swapperv;
}

double* find_absvalue(double** m, int k, int n)
{	
	double abval = 0.0;
	double* ret = new double[2];
	int row = 0;
	for (int i = k; i < n; i++)
	{	
		if (std::abs(abval) < std::abs(m[i][k]))
		{
			abval = m[i][k];
			row = i;
		}
	}
	ret[0] = abval;
	ret[1] = row;
	return ret;	
}

void divide_row(double** m, int k, int n)
{
	double divider = 1.0;
	divider = m[k][k];
	if (k==(n-1))
	{	
		if (m[n][k] == 0 || divider == 0){
			m[n][k] = 0;
			m[k][k] = 0;
		}
		else{
		m[n][k] = (m[n][k] / divider);
		m[k][k] = (m[k][k] / divider);
		}
	}

	else
	{
		if (m[n][k] != 0.0){m[n][k] = (m[n][k] / divider);}
		for (int l = 0; l < n; l++)
		{
			if (m[k][l] != 0){m[k][l] = (m[k][l] / divider);}
		}
	}	
}

void forward_elim(double** m, int k, int n)
{	
	double eliminator = 0.0;
	for (int l = 1; l < n; l++)
	{	
		if ((k+l) < n)
		{
			eliminator = ((-1) * m[k+l][k] * m[k][k]);
			m[n][k+l] = (eliminator * m[n][k]) + m[n][k+l];
			for (int j = 0; j < n; j++)
			{	
				if ((k+j) < n)
				{
					m[k+l][k+j] = (eliminator * m[k][j+k]) + m[k+l][k+j];	
				}
			}
		}
	}
}

void backsolver500(double** m, int n)
{
	double* soln = NULL;
	std::ofstream outfile;
	outfile.open("q1.txt");
	soln = new double[n];
	for (int i=n-1; i >= 0; i--)
	{	
		soln[i] = m[n][i];
		for(int j=i+1; j<n; j++){soln[i] -= (soln[j] * m[i][j]);}
	}
	std::cout << "----------- Solution -------------\n";
	for (int i = 0; i < n; i++)
		{
			if (std::abs(soln[i]) < 1.00e-3){soln[i] = 0;}
			std::cout << "X" << i+1 << ": " << soln[i] << "\n";
			outfile << soln[i] << " ";
			if ( (i % 9) == 0)
			{
				outfile << "\n";
			}
		}
	delete soln;
}