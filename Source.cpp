/*
  Name: Solution to Matrices
  Author: Ian Howard
  Date: 9/6/2021
  Description: This codes finds vector solution x to a Matrice (A) and Vector solution (b) with the same number of columns
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <ctype.h>
#include <string>
#include <sstream>

void printVector(vector<vector<double>> v)
{
	for (int i = 0; i < v.size(); i++) //Condition for printing solution height
	{
		for (int j = 0; j < 1; j++) //Condition for printing solution length (1)
		{
			cout << v[i][j] << "\n"; //Outputs user solution vector
		}
	}
}

void printMatrix(vector<vector<double>> C)
{
	for (int i = 0; i < C.size(); i++) //Condition for printing matrix height
	{
		for (int j = 0; j < C[i].size(); j++) //Prints each ith row by size of ith row
		{
			cout << C[i][j] << " "; //Prints each value in row
		}
		cout << "\n"; //Prints next row
	}
}

//Extracts and stores cofactor matrix
vector<vector<double>> COMXN(vector<vector<double>> A, vector<vector<double>> comat, int g, int h, int n)
{
	int i = 0, j = 0;
	for (int M = 0; M < n; M++)
	{
		for (int N = 0; N < n; N++)
		{
			if (N != h && M != g)
			{
				comat[i][j++] = A[M][N];
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
	return comat;
}

double DETMXN(vector<vector<double>> A, vector<vector<double>> comat, size_t N, size_t M)
{
	double L = 0; //Store determinant
	const size_t J = N; //Matrix Size
	if (J == 1) //Returns only element in a 1x1 matrix
		return A[0][0];
	int s = -1; //Determinate sign setter

	//Calling cofactors and calculating determinant
	for (size_t j = 0; j < J; j++)
	{
		s = -s; // Sets sign of each term
		comat = COMXN(A, comat, 0, j, N);
		L += s * A[0][j] * DETMXN(comat, comat, N - 1, M);
	}
	return (L);
}

vector<vector<double>> ADJMAT(vector<vector<double>> Q, vector<vector<double>> bomat, size_t M, size_t N)
{ 
	int s = -1, d;
	const size_t O = M;
	const size_t P = N;
	typedef vector<vector<double>> A;
	typedef vector<double> Row;
	A cofmat, detmat, adjmat;
	Row row(P), bow(P - 1), cow (P);

	for (size_t i = 0; i < O; i++) //Condition finding the determenant matrix per selected row
	{
		for (size_t j = 0; j < P; j++) //Condition finding the determenant matrix per selected column
		{
			for (size_t k = 0; k < O; k++)
			{
				d = 0; //Reset counter for next rows storage
				if (k != i)
				{
					for (size_t l = 0; l < P; l++)
					{
						if (l != j) //Checks to see if position is not in selected row/column
						{
							bow[d] = Q[k][l]; //Stores determinant matrix row
							d++; //increased counter by 1 for next row position
						}
					}
					if (d == N - 1) //If the determenant row is full push back for next row
					{
						detmat.push_back(bow);
					}
				}
			}
			s = -s; //alternate sign of determinant
			{
				row[j] = s * DETMXN(detmat, bomat, N - 1, M - 1); //Calculates and stores cofactors
			}
			detmat.clear();
		}
		cofmat.push_back(row);
	}

	for (size_t i = 0; i < O; i++)
	{
		for (size_t j = 0; j < P; j++)
		{
			cow[j] = cofmat[j][i]; //transpose cofactor matrix into adjoint matrix
		}
		adjmat.push_back(cow);
	}
	return(adjmat);
}

int main()
{
	std::string y, m, n; //Initializing user input
	int L;

	cout << "Hello, \nThis program finds a solution vector x based on input matrix A and vector b \nwhere one unique solution exists by definition b exists and is equal to the column space of A\n\n\n"; //describes solver to user

	 //User inputs condition for a unique matrix solution
	do
	{
		cout << "Please enter the height (y) of the solution vector b: "; //Requests solution size input
		cin >> y; //User inputs solution size
		if (std:cin >> value)
		{
			while (y < 0)
			{
				cout << "\nIt must be a positive number: ";
				cin >> y;
			}
		}
		cout << "Please enter the length (n) of the matrix A: "; //Requests matrix length
		cin >> n; //User inputs matrix length
		while (n < 0)
		{
			cout << "\nIt must be a positive number: ";
			cin >> n;
		}
		cout << "Please enter the height (m) of the matrix A: "; //Requests matrix height
		cin >> m; //User inputs matrix height
		while (m < 0)
		{
			cout << "\nIt must be a positive number: ";
			cin >> m;
		}
		if (y != n || n != m)
		{
			cout << "There is no unique solution for matrix A and vector b entered\nPlease Try again\n\n\n";
		}
	} while (y != n || n != m);
	
	cout << "\n";//spacing for clean look between user inputs

	//Definitions
	const size_t Y = y;
	const size_t N = n;
	const size_t M = m;

	
	typedef vector<vector<double>> A;
	typedef vector<double> Row;
	A matrix, vector, comat, bomat, adjmat, invmat, x;
	Row row(M), bow(Y), cow(N-1), xow(Y);

	//Creates blank mxn matrix for cofactor storage
	for (size_t i = 0; i < n; i++) //Condition for loop, inputing row till solution height x is reached
	{
		for (size_t j = 0; j < n; j++) //2nd loop condition, inputing each row 
		{
			row[j];
		}
		comat.push_back(row); //Push row back for next row input
	}

	//Creates blank mxn matrix for adjoint storage
	for (size_t i = 0; i < n - 1; i++) //Condition for loop, inputing row till solution height x is reached
	{
		for (size_t j = 0; j < n - 1; j++) //2nd loop condition, inputing each row 
		{
			cow[j];
		}
		bomat.push_back(cow); //Push row back for next row input
	}

	//Creates blank vector for unique solution (x) storage
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			xow[j];
		}
		x.push_back(xow);
	}

	

	//User input for matrix of size M x N
	do
	{
		matrix = comat; //Initialize matrix using temp storage
		for (size_t i = 0; i < M; i++) //Condition for loop, inputing entire rows till matrix height m is reached
		{
			for (size_t j = 0; j < N; j++) //2nd loop condition, inputing each value in each row till matrix length n is reached 
			{

				cout << "Please enter matrix row " << i + 1 << " column " << j + 1 << ": "; //Requests user input for matrix row
				cin >> matrix[i][j]; //User inputs matrix row 
			}
		}
		L = DETMXN(matrix, comat, N, M); //Calculates determinant (A) and stores it 
		if (L == 0)
		{
			cout << "Unique solution x cannot be found for determinant (A) = " << L << "\n"; //Prompts user to reenter matrix if determinant (A) = 0
		}
	} while (L == 0);

	//User input for solution vector of size M
	for (size_t i = 0; i < Y; i++) //Condition for loop, inputing row till solution height x is reached
	{
		for (size_t j = 0; j < 1; j++) //2nd loop condition, inputing each row 
		{
			cout << "Please enter row " << i + 1 << " in the solution : "; //Requests user input for solution 
			cin >> bow[j]; //User input for soltuion
		}
		vector.push_back(bow); //Push row back for next row input
	}

	//Opeartions
	adjmat = ADJMAT(matrix, bomat, M, N); //Calculates adjoint (A) and stores it

	invmat = adjmat; //Temporarily stores the adjoint (A) as inverse (A)

	//Calculates and stores inverse (A)
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			invmat [i][j] /= L;
		}
	}

	//Calculates and stores unique solution (x)
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			x[i][0] += invmat[i][j] * vector[j][0];
		}
	}

	//Output
	cout << "Matrix A \n"; printMatrix(matrix); cout << "\n"; //Calls printMatrix function defined earlier
	cout << "Solution b \n"; printVector(vector); cout << "\n"; //Calls printVector function defined earlier
	cout << "Determinant (A) = " << L << "\n\n"; //Prints determinant (A)
	cout << "Adjoint (A) = \n"; printMatrix(adjmat); cout << "\n"; //Prints adjoint (A)
	cout << "Inverse (A) = \n"; printMatrix(invmat); cout << "\n"; //Prints inverse (A)
	cout << "Unique (x) solution for Ax=b: \n"; printVector(x); cout << "\n"; //Prints unique solution (x)

	system("Pause");
	return 0;
}
