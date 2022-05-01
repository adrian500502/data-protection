#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <cstdio>
#include <string>
#include <windows.h>

using namespace std;

long long NWD(long long a, long long b)
{
	long long c = 0;
	while (b != 0)
	{
		c = a % b;
		a = b;
		b = c;
	}

	return a;
}

long long invmod(long long A, long long B)
{
	vector<long long> vectorQ, vectorR, vectorS;
	vectorQ.push_back(0);
	vectorQ.push_back(0);

	if (A > B)
	{
		vectorR.push_back(A);
		vectorR.push_back(B);
		vectorS.push_back(1);
		vectorS.push_back(0);
	}
	else if (B > A)
	{
		vectorR.push_back(B);
		vectorR.push_back(A);
		vectorS.push_back(0);
		vectorS.push_back(1);
	}

	long long idx = 0;
	while (vectorR.back() != 0)
	{
		vectorQ.push_back(vectorR.at(idx) / vectorR.at(idx + 1));
		vectorR.push_back(vectorR.at(idx) % vectorR.at(idx + 1));
		if (vectorR.back() != 0)
			vectorS.push_back(vectorS[idx] - (vectorS[idx + 1] * vectorQ.back()));

		idx++;
	}

//	for (int i = 0; i < vectorQ.size(); i++)
//		cout << "vectorQ[" << i << "] = " << vectorQ[i] << '\n';
//    cout << '\n';
//
//	for (int i = 0; i < vectorR.size(); i++)
//		cout << "vectorR[" << i << "] = " << vectorR[i] << '\n';
//    cout << '\n';
//
//	for (int i = 0; i < vectorS.size(); i++)
//		cout << "vectorS[" << i << "] = " << vectorS[i] << '\n';
//    cout << '\n';


	if (vectorS.back() < 0)
		return vectorS.back() + B;

	else if (vectorR.at(vectorR.size() - 2) != 1)
		return -1;

	else if (vectorR.back() == 0 && vectorR.at(vectorR.size() - 2) == 1)
		return vectorS.back();

	else
		return EXIT_FAILURE;
}

int main()
{
	long long A = 0, B = 0, outcome = 0;
	/*cout << "Podaj A: "; cin >> A;
	cout << "Podaj B (modulo): "; cin >> B;

	if (NWD(A, B) == 1)
	{
		outcome = invmod(A, B);
		cout << "a = " << A << ", b = " << B << ", s = " << outcome << ", a * s mod b = " << (A * outcome) % B << '\n';
	}
	else
	{
		cout << "a = " << A << ", b = " << B << ", Liczby nie sa wzglednie pierwsze\n";
	}*/

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 1000000000); // define the range

	for (int i = 0; i < 100; i++)
	{
		A = distr(gen);
		B = distr(gen);

		if (NWD(A, B) == 1)
		{
			outcome = invmod(A, B);
			cout << i << ") a = " << A << ", b = " << B << ", s = " << outcome << ", a * s mod b = " << (A * outcome) % B << '\n';
		}
		else
			cout << i << ") a = " << A << ", b = " << B << ", Liczby nie sa wzglednie pierwsze\n";
	}

    system("PAUSE");
	return EXIT_SUCCESS;
}
