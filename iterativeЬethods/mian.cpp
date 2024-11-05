#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <iomanip>
#include <chrono>
#include <fstream>

using namespace std;

int k_max = 1000;
double eps = 1e-7;
double w = 0.5;

void printVec(vector<vector<double>>& mat)
{
	for (int i = 0; i < mat.size(); i++)
	{
		for (int q = 0; q < mat[i].size(); q++)
		{
			cout << mat[i][q] << " ";
		}
		for (int q = mat[i].size(); q < mat.size(); q++)
		{
			cout << mat[q][i] << " ";
		}
	}
}
void printVec(vector<double>& mat)
{
	for (int q = 0; q < mat.size() && q < 5; q++)
	{
		cout << mat[q] << " ";
	}
	for (int q = mat.size() - 5 > 5 ? mat.size() - 5 : 5; q < mat.size(); q++)
	{
		cout << mat[q] << " ";
	}
	cout << "\n";
}
void mulMat(vector<vector<double>>& matA, vector<double>& x, vector<double>& matB)
{
	for (int i = 0; i < matA.size(); i++) // получаем значения b
	{
		for (int q = 0; q < matA[i].size(); q++)
		{
			matB[i] += matA[i][q] * x[q];
		}
		for (int q = matA[i].size(); q < matA.size(); q++)
		{
			matB[i] += matA[q][i] * x[q];
		}
	}
}

int Jacobi(vector<vector<double>>& matA, vector<double>& x0, vector<double>& b)
{
	int g = 0;
	vector<double> x(0, x0.size());
	for (int i = 0; i < matA; i++)
	{

	}

	return g;
}

int main()
{
	srand(time(0));

	int n = 1000;
	int m = 12;

	vector<vector<double>> matAOriginal;
	vector<vector<double>> matA;

	vector<double> b(n, 0);

	vector<double> solutionOriginal(n, 0);
	vector<double> solution(n, 0);
	vector<double> solutionImprecise(n, 0);
	vector<double> x0(n, 0);
	
	for (int i = 0; i < n; i++) // заполняем матрицу А
	{
		vector <double> temp;
		for (int q = 0; q < i; q++)
		{
			temp.push_back(rand() % 201 - 100.0);
		}
		temp.push_back(0);
		matA.push_back(temp);
	}
	for (int i = 0; i < n; i++) // заполняем диагонали
	{
		double sum = 0;
		for (int q = 0; q < matA[i].size(); q++)
		{
			sum += abs(matA[i][q]);
		}
		for (int q = matA[i].size(); q < matA.size(); q++)
		{
			sum += abs(matA[q][i]);
		}
		matA[i][i] = rand() % 120 + 12.0 + sum;
	}
	matAOriginal = matA;
	for (double i = 0; i < n; i++)
	{
		solution[i] = m + i;
	}
	solutionOriginal = solution;

	mulMat(matAOriginal, solutionOriginal, b);

	cout << "x0:\n";
	printVec(x0);

	cout << "Solution:\n";
	printVec(solutionOriginal);
	cout << "\n";

	cout << "w = " << w << "\n"; // w = 0.5
	cout << "q = " << Jacobi(matA, x0, b) << "\n";
	printVec(x0);

}