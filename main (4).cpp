#include <iostream>
#include <vector>

using namespace std;



vector<vector<double>> findCoFactor(vector <vector <double>> minor, int eleCol)
{
	int n = minor.size();
	vector <vector<double>> reducedMatrix(n - 1, vector<double> (n - 1));

	for (int i = 1; i < minor.size(); i++)
	{
		int k = 0;
		for (int j = 0; j < minor.size(); j++)
			if (j != eleCol)
			{
				reducedMatrix[i - 1][k] = minor[i][j];
				k++;
			}
	}

	return reducedMatrix;
}


double findDet(vector <vector<double>> cofMatrix)
{
	double determinant(0);
	//matrix of size 1x1
	if (cofMatrix.size() == 1)
		return cofMatrix[0][0];

	if (cofMatrix.size() == 2)
		return ((cofMatrix[0][0] * cofMatrix[1][1]) - (cofMatrix[1][0] * cofMatrix[0][1]));
	else
	{
		for (int i = 0; i < cofMatrix.size(); i++)
		{
			vector<vector<double>> redMatrix = findCoFactor(cofMatrix, i);
			determinant += cofMatrix[0][i] * pow(-1, i) *findDet(redMatrix);
		}

		return determinant;
	}
}

vector<double>CramersRule(vector<vector<double>> cofMatrix, vector<double> constMatrix) 
{
	int  n = cofMatrix.size();

	if (findDet(cofMatrix) == 0)
	{
		cout << "Matrix is singular.\n";
		exit(0);
	}

	vector<vector<double>> tempMatrix(n, vector<double>(n));
	tempMatrix = cofMatrix;

	vector<double> uniqueSoln(n);

	for (int i = 0; i < cofMatrix.size(); i++)
	{
		tempMatrix = cofMatrix;
		for (int j = 0; j < cofMatrix.size(); j++)
			tempMatrix[j][i] = constMatrix[j];
		uniqueSoln[i] = findDet(tempMatrix) / findDet(cofMatrix);
	}

	return uniqueSoln;
}

void displayMatrix(vector<double> varMatrix)
{
	cout << "Matrix: \n";
	for (int i = 0; i < varMatrix.size(); i++)
	{
		cout << varMatrix[i] << endl;
	}
}

int main()
{
	int size;

	//Sample Code
	/*vector <vector <double>> cofMatrix = { {1, 1, -1},
										   {3, -2, 1},
										   {1, 3, -2}};


	vector<double> constMatrix = { 6, -5, 14 };

	vector<double> varMatrix = CramersRule(cofMatrix, constMatrix);

	displayMatrix(varMatrix);

	cout << endl;*/

	cout << "Enter matrix size:\n";
	cin >> size;

	vector<vector<double>> cofMatrix(size, vector<double>(size));
	for (int i = 0; i < cofMatrix.size(); i++)
	{
		cout << "Enter variable coefficients in equation " << i + 1 << ": ";

		for (int j = 0; j < cofMatrix.size(); j++)
			cin >> cofMatrix[i][j];

		cout << endl;
	}

	cout << endl;

	vector<double> constMatrix(size);
	cout << "Enter equation constants:\n";
	for (int i = 0; i < size; i++)
		cin >> constMatrix[i];

	vector<double> varMatrix = CramersRule(cofMatrix, constMatrix);

	displayMatrix(varMatrix);

	cout << endl;

	return 0;
}