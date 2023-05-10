#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;
// n - count images
const int n = 20;

// m - count feature
const int m = 5;

const double eps = 1e-10;
const int max_steps = 200;
const int N = n * 2; // 2 - dimensional
vector<vector<double>> X(n, vector<double>(m));

double f(vector<double> y)
{
	double result = 0.;

	for (int i(0); i < n - 1; i++)
	{
		for (int j(i + 1); j < n; j++)
		{
			double delta = 0.;
			for (int k(0); k < m; k++)
				delta += pow(X[i][k] - X[j][k], 2);

			//2 - dimensional
			result += pow(sqrt(delta) - sqrt(pow(y[2 * i] - y[2 * j], 2) + pow(y[2 * i + 1] - y[2 * j + 1], 2)), 2);
		}
	}

	return result;
}

double golden_ratio(vector<double> x, int index, double a, double b)
{
	double phi = (1. + sqrt(5.)) / 2.;
	double A = 0., B = 0.;
	double x1 = a + phi * (b - a);
	double x2 = b - phi * (b - a);

	int step = 0;

	while (b - a > eps)
	{
		x1 = b - ((b - a) / phi);
		x[index] = x1;
		A = f(x);

		x2 = a + ((b - a) / phi);
		x[index] = x2;
		B = f(x);

		A > B ? a = x1 : b = x2;

		if (step++ > max_steps)
			break;
	}

	return (a + b) / 2;
}

void descent_method(vector<double> x, double eps)
{
	double A = 0., B = f(x);
	double dx = 0.;

	int i = 0;
	for (; i < max_steps; i++) 
	{
		A = B; 

		for (int index = 0; index < N; index++)
			x[index] = golden_ratio(x, index, -5000, 5000);

		B = f(x);

		dx = fabs(A - B);
		if (dx <= eps)
			break;

		/*for (int i(0); i < n; i++)
			cout << x[2 * i] << " " << x[2 * i + 1] << "\n";*/

		/*cout << "\n\n\n";*/
	}

	ofstream output("output.csv");
	for (int i(0); i < N; i++)
		output << x[i] << '\n';
	output.close();

	cout << "Количество итераций: " << i + 1 << endl;

	cout << "Значение фукнции f(X): " << f(x) << endl;
	cout << "Полученная погрешность: " << dx << endl;

	/*
	cout << "\n\nПроверка вычислений\n\n\nРасстояние в " << m << " мерном пространстве:\n\n";
	for(int i(0); i < n - 1; i++)
		for (int j(i + 1); j < n; j++)
		{
			cout << "Расстояние между " << i + 1 << " - " << j + 1 << " точкой = ";
			double result = 0.;
			for (int q(0); q < X[0].size(); q++)
				result += pow(X[i][q] - X[j][q], 2);

			cout << sqrt(result) << endl;
		}

	cout << "\n\n\nРасстояние в 2-мерном пространстве:\n\n";
	for (int i(0); i < n - 1; i++)
		for (int j(i + 1); j < n; j++)
			cout << "Расстояние между " << i + 1 << " - " << j + 1 << " точкой = " << sqrt(pow(x[2 * i] - x[2 * j], 2) + pow(x[i == 0 ? 1 : 2 * i + 1] - x[2 * j + 1], 2)) << endl;

	*/
}

int main()
{
	setlocale(LC_ALL, "Russian");

	fstream input("data.txt");
	for (int i(0); i < n; i++)
		for (int j(0); j < m; j++)
			input >> X[i][j];

	vector<double> y_0(N);
	descent_method(y_0, eps);

	system("pause");
	return 0;
}