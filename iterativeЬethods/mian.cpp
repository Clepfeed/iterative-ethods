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
		cout << "\n";
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
	for (int i = 0; i < matA.size(); i++) // получаем значени€ b
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

double norm(vector<double>& x0, vector<double>& x)
{
	double normSol = 0;
	for (int i = 0; i < x0.size(); i++)
	{
		normSol += abs(x0[i]);
	}
	double normSolImprecise = 0;
	for (int i = 0; i < x0.size(); i++)
	{
		normSolImprecise += abs(x0[i] - x[i]);
	}
	return normSolImprecise / normSol;
}

double normAbs(vector<double>& x0, vector<double>& x)
{
	double normSolImprecise = 0;
	for (int i = 0; i < x0.size(); i++)
	{
		normSolImprecise += abs(x0[i] - x[i]);
	}
	return normSolImprecise;
}

int Jacobi(vector<vector<double>>& a, vector<double>& x0, vector<double>& b)
{
	int k = 1;
	vector<double> x(0, x0.size());
	x = x0;
	for (; k < k_max; k++)
	{
		x0 = x; // запоминаем вектор шага k
		for (int i = 0; i < x0.size(); i++) // все x в векторе решений
		{
			x[i] = b[i];
			double sum = 0;
			int j = 0;
			for (; j < a[i].size() && j < i; j++) // перва€ сумма до i - 1
			{
				sum += a[i][j] * x0[j];
			}
			for (; j < a.size() && j < i; j++)
			{
				sum += a[j][i] * x0[j];
			}
			x[i] -= sum;
			sum = 0;
			j++; // i + 1
			for (; j < a[i].size(); j++) // втора€ сумма до n
			{
				sum += a[i][j] * x0[j];
			}
			for (; j < a.size(); j++)
			{
				sum += a[j][i] * x0[j];
			}
			x[i] -= sum;
			x[i] /= a[i][i];
			//cout << x[i] << " ";
		}
		if (norm(x0, x) < eps)
			break;
	}
	x0 = x;
	return k;
}

int relaxation(vector<vector<double>>& a, vector<double>& x0, vector<double>& b, double w)
{
	int k = 1;
	vector<double> x(0, x0.size());
	x = x0;
	for (; k < k_max; k++)
	{
		x0 = x; // запоминаем вектор шага k
		for (int i = 0; i < x0.size(); i++) // все x в векторе решений
		{
			x[i] = b[i];
			double sum = 0;
			int j = 0;
			for (; j < a[i].size() && j < i; j++) // перва€ сумма до i - 1
			{
				sum += a[i][j] * x[j];
			}
			for (; j < a.size() && j < i; j++)
			{
				sum += a[j][i] * x[j];
			}
			x[i] -= sum;
			sum = 0;
			j++; // i + 1
			for (; j < a[i].size(); j++) // втора€ сумма до n
			{
				sum += a[i][j] * x0[j];
			}
			for (; j < a.size(); j++)
			{
				sum += a[j][i] * x0[j];
			}
			x[i] -= sum;
			x[i] *= (w / a[i][i]);
			x[i] = (1 - w) * x0[i] + x[i];
		}
		if (norm(x0, x) < eps)
			break;
	}
	x0 = x;
	return k;
}

int main()
{
	srand(time(0));

	int n = 1000;
	int m = 12;
	vector<double> w = {0.5, 1, 1.5};

	vector<vector<double>> matA;

	vector<double> b(n, 0);

	vector<double> solution(n, 0);
	vector<double> solutionImprecise(n, 0);
	vector<double> x0(n, 0);
	
	for (int i = 0; i < n; i++) // заполн€ем матрицу ј
	{
		vector <double> temp;
		for (int q = 0; q < i; q++)
		{
			temp.push_back(rand() % 201 - 100.0);
		}
		temp.push_back(0);
		matA.push_back(temp);
	}
	for (int i = 0; i < n; i++) // заполн€ем диагонали
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
	for (double i = 0; i < n; i++)
	{
		solution[i] = m + i;
	}
	mulMat(matA, solution, b);

	cout << "x0:\n";
	printVec(x0);
	cout << "Solution:\n";
	printVec(solution);
	cout << "\n";

	cout << std::fixed << std::setprecision(22);

	cout << "Jacobi:\n";

	solutionImprecise = x0;
	cout << "q = " << Jacobi(matA, solutionImprecise, b) << "\n";
	cout << "Imprecise solution:\n";
	printVec(solutionImprecise);
	cout << "Relative error: " << norm(solution, solutionImprecise) << "\n";
	cout << "Absolute error: " << normAbs(solution, solutionImprecise) << "\n";


	cout << "\nRalaxation method:\n";
	for (int i = 0; i < w.size(); i++)
	{
		cout << std::fixed << std::setprecision(3);
		cout << "w: " << w[i] << "\n";
		solutionImprecise = x0;
		cout << "q = " << relaxation(matA, solutionImprecise, b, w[i]) << "\n";
		cout << std::fixed << std::setprecision(22);
		cout << "Imprecise solution:\n";
		printVec(solutionImprecise);
		cout << "Relative error: " << norm(solution, solutionImprecise) << "\n";
		cout << "Absolute error: " << normAbs(solution, solutionImprecise) << "\n\n";
	}
	return 0;
}