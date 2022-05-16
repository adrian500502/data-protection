#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <vector>
#include <fstream>
#include <windows.h>
#include <cstdio>

using namespace std;

unsigned int DJB(string text)
{
	unsigned int hash = 5381;

	for (unsigned int i = 0; i < text.size(); i++)
		hash = (hash << 5) + hash + text[i];

	return hash;
}

unsigned int Adler32(string text)
{
	unsigned int A = 1, B = 0, p = 65521, hash;

	for (unsigned int i = 0; i < text.size(); i++)
	{
		A += text[i] % p;
		B += A % p;
	}

	return hash = B * 65536 + A;
}

class Collision
{
public:
	string firstString = "";
	string secondString = "";
	unsigned int hash = 0;

	Collision(string S1, string S2, unsigned int H)
		: firstString(S1)
		, secondString(S2)
		, hash(H)
	{}
};

vector<string> randomStringGenerator(unsigned int D)
{
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist(97, 122); // z przedzialu a-z

	vector<string> stringsVector;
	for (unsigned int i = 0; i < 100000; i++)
	{
		string randomString = "";
		for (unsigned int j = 0; j < D; j++)
			randomString += static_cast<char>(dist(rng));

		stringsVector.push_back(randomString);
	}

	return stringsVector;
}

bool myPredicate(unsigned i, unsigned j) 
{
	return (i == j);
}

void countCollisionsAndSaveToFile(unsigned int (*fun)(string), unsigned int D, string fileName)
{
	string funName = (fun == DJB) ? "DJB"
		: (fun == Adler32) ? "Adler32"
		: "Incorrect function name!";

	vector<string> randomStringsVector = randomStringGenerator(D);
	vector<unsigned int> hashesVector;
	for (unsigned i = 0; i < randomStringsVector.size(); i++)
		hashesVector.push_back(fun(randomStringsVector.at(i)));

	vector<Collision> collisionsVector;
	for (unsigned i = 0; i < hashesVector.size(); i++)
	{
		for (unsigned j = i + 1; j < hashesVector.size(); j++)
		{
			if (hashesVector.at(i) == hashesVector.at(j))
			{
				Collision collision(randomStringsVector.at(i), randomStringsVector.at(j), hashesVector.at(i));
				collisionsVector.push_back(collision);
			}
		}
	}

	ofstream output;
	output.open(fileName);
	cout << funName << ", D = " << D << '\n';
	output << funName << ", D = " << D << '\n';
	unsigned int numberOfCollisions = 0;
	for (auto& z : collisionsVector)
	{
		numberOfCollisions++;
		output << z.firstString << "  " << z.secondString << "  " << z.hash << '\n';
	}   cout << "Ilosc kolizji: " << numberOfCollisions << "\n\n";
	output << "Ilosc kolizji: " << numberOfCollisions;
	output.close();
}

int main()
{
	countCollisionsAndSaveToFile(DJB, 8, "output_DJB_8.txt");
	countCollisionsAndSaveToFile(DJB, 100, "output_DJB_100.txt");
	countCollisionsAndSaveToFile(Adler32, 8, "output_Adler32_8.txt");
	countCollisionsAndSaveToFile(Adler32, 100, "output_Adler32_100.txt");

	//system("pause");
	return EXIT_SUCCESS;
}