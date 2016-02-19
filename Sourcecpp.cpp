#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

int rows = 2;
int cols = 2;

vector<vector<int>> Iterative(vector<vector<int>> a, vector<vector<int>> b)
{

	vector <vector<int>> c;

	vector <int> v;
		int rows = a.size();
		int cols = a[0].size();
		int range = b[0].size();

	c.resize(rows, vector<int>(range, 0));
	int sum = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < range; j++)
		{
			for (int k = 0; k < cols; k++)
			{
				sum = sum + a[i][k] * b[k][j];
			}
			c[i][j] = sum;
			sum = 0;
		}
	}
	
	for (int i = 0; i<rows; i++)
	{
	for (int j = 0; j<cols; j++)
	{
	cout<<c[i][i]<<" ";

	}
	cout<<"\n";
	}
	return c;
}


vector<vector<int>> Cal_Sum_Strassen(vector<vector<int>> a, vector<vector<int>> b)
{
	int n = a.size();
	vector<vector<int>> Result;
	Result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			Result[i][j] = a[i][j] + b[i][j];
		}
	}
	return Result;
}

vector<vector<int>> Cal_Sub_Strassen(vector<vector<int>> a, vector<vector<int>> b)
{
	int n = a.size();
	vector<vector<int>> Result;
	Result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			Result[i][j] = a[i][j] - b[i][j];
		}
	}
	return Result;
}

vector<vector<int>> Strassen(vector<vector<int>> a, vector<vector<int>> b)
{
	int i, j;
	int n = a.size();

	vector<vector<int>> c;
	c.resize(n, vector<int>(n, 0));

	if (n == 1)
	{
		c[0][0] = a[0][0] * b[0][0];
		return c;
	}
	else {
		vector<vector<int>> a11, a12, a21, a22;
		vector<vector<int>> b11, b12, b21, b22;
		vector<vector<int>> c11, c12, c21, c22;
		vector<vector<int>> p1, p2, p3, p4, p5, p6, p7;

		a11.resize(n / 2, vector<int>(n / 2, 0));
		a12.resize(n / 2, vector<int>(n / 2, 0));
		a21.resize(n / 2, vector<int>(n / 2, 0));
		a22.resize(n / 2, vector<int>(n / 2, 0));

		b11.resize(n / 2, vector<int>(n / 2, 0));
		b12.resize(n / 2, vector<int>(n / 2, 0));
		b21.resize(n / 2, vector<int>(n / 2, 0));
		b22.resize(n / 2, vector<int>(n / 2, 0));

		c11.resize(n / 2, vector<int>(n / 2, 0));
		c12.resize(n / 2, vector<int>(n / 2, 0));
		c21.resize(n / 2, vector<int>(n / 2, 0));
		c22.resize(n / 2, vector<int>(n / 2, 0));

		p1.resize(n / 2, vector<int>(n / 2, 0));
		p2.resize(n / 2, vector<int>(n / 2, 0));
		p3.resize(n / 2, vector<int>(n / 2, 0));
		p4.resize(n / 2, vector<int>(n / 2, 0));
		p5.resize(n / 2, vector<int>(n / 2, 0));
		p6.resize(n / 2, vector<int>(n / 2, 0));
		p7.resize(n / 2, vector<int>(n / 2, 0));

		vector<vector<int>> aResult;
		vector<vector<int>> bResult;
		aResult.resize(n / 2, vector<int>(n / 2, 0));
		bResult.resize(n / 2, vector<int>(n / 2, 0));


		for (i = 0; i < n / 2; i++)
		{
			for (j = 0; j < n / 2; j++)
			{
				a11[i][j] = a[i][j];
				a12[i][j] = a[i][j + n / 2];
				a21[i][j] = a[i + n / 2][j];
				a22[i][j] = a[i + n / 2][j + n / 2];

				b11[i][j] = b[i][j];
				b12[i][j] = b[i][j + n / 2];
				b21[i][j] = b[i + n / 2][j];
				b22[i][j] = b[i + n / 2][j + n / 2];
			}
		}

		aResult = Cal_Sum_Strassen(a11, a22);
		bResult = Cal_Sum_Strassen(b11, b22);
		p1 = Strassen(aResult, bResult);

		aResult = Cal_Sum_Strassen(a21, a22);
		p2 = Strassen(aResult, b11);

		bResult = Cal_Sub_Strassen(b12, b22);
		p3 = Strassen(a11, bResult);

		bResult = Cal_Sub_Strassen(b21, b11);
		p4 = Strassen(a22, bResult);

		aResult = Cal_Sum_Strassen(a11, a12);
		p5 = Strassen(aResult, b22);

		aResult = Cal_Sub_Strassen(a21, a11);
		bResult = Cal_Sum_Strassen(b11, b12);
		p6 = Strassen(aResult, bResult);

		aResult = Cal_Sub_Strassen(a12, a22);
		bResult = Cal_Sum_Strassen(b21, b22);
		p7 = Strassen(aResult, bResult);

		c12 = Cal_Sum_Strassen(p3, p5);
		c21 = Cal_Sum_Strassen(p2, p4);

		aResult = Cal_Sum_Strassen(p1, p4);
		bResult = Cal_Sum_Strassen(aResult, p7);
		c11 = Cal_Sub_Strassen(bResult, p5);

		aResult = Cal_Sum_Strassen(p1, p3);
		bResult = Cal_Sum_Strassen(aResult, p6);
		c22 = Cal_Sub_Strassen(bResult, p2);


		for (i = 0; i < n / 2; i++)
		{
			for (j = 0; j < n / 2; j++)
			{
				c[i][j] = c11[i][j];
				c[i][j + n / 2] = c12[i][j];
				c[i + n / 2][j] = c21[i][j];
				c[i + n / 2][j + n / 2] = c22[i][j];
			}
		}
	}

	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			cout << c[i][i] << " ";

		}
		cout << "\n";
	}

	return c;
}


int main()
{
	vector<vector<int>> a;
	vector<vector<int>> b;

	a.resize(rows, vector<int>(cols, 0));
	b.resize(rows, vector<int>(cols, 0));

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			a[i][j] = rand() % 10 + 1;
			b[i][j] = rand() % 10 + 1;
		}
	}
	cout << "Iterative Method:\n";
	Iterative(a, b);

	cout << "Strassen Method:\n";
	Strassen(a, b);
	system("Pause");

	getchar();
	return 0;
}