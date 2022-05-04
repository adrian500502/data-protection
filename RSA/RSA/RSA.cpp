#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

bool probne(long long N)
{
    long long temp = (long long)sqrt(N);

    for (int i = 2; i <= temp; i++)
    {
        if (N % i == 0)
            return false;
    }

    return true;
}
long long powmod(long long a, long long b, long long c)
{
    long long outcome = 1, y = a;

    while (b > 0)
    {
        if (b % 2 == 1)
            outcome = (outcome * y) % c;

        y = (y * y) % c;
        b = b / 2;
    }

    return outcome % c;
}
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

    if (vectorS.back() < 0)
        return vectorS.back() + B;
    else if (vectorR.at(vectorR.size() - 2) != 1)
        return -1;
    else if (vectorR.back() == 0 && vectorR.at(vectorR.size() - 2) == 1)
        return vectorS.back();
    else
        return EXIT_FAILURE;
}
void RSA(const string& fileName)
{
    long long p, q;
    while (true)
    {
        cout << "Podaj p: "; cin >> p;
        cout << "Podaj q: "; cin >> q;

        if (probne(p) == true && probne(q) == true)
            break;
        else
            cout << "Obie liczby nie sa pierwsze, wprowadz p i q ponownie.\n";
    }

    long long n = p * q;
    cout << "n = " << n << '\n';
    long long fi = ((p - 1) * (q - 1));
    cout << "fi(n) = fi(" << n << ") = " << fi << '\n';
    long long e;

    while (true)
    {
        cout << "Podaj e: "; cin >> e;
        if (NWD(e, fi) == 1 && e < fi && e > 0)
            break;
        else
            cout << "NWD(e, fi) != 1 lub e nie jest z przedzialu 1 < e < fi\n";
    }

    long long d = invmod(e, fi);
    cout << "d = " << d << '\n';

    // wczytywanie wiadomosci z pliku
    ifstream input;
    string str, tmp;
    bool first = false;
    input.open(fileName, std::ios::in);
    if (input.good())
    {
        while (!input.eof())
        {
            if (first)
                str += "\n";
            if (!first)
                first = true;
            tmp.clear();
            getline(input, tmp);
            str += tmp;
        }
    }
    input.close();
    cout << "\nMessage: " << str << '\n';

    // wypisywanie wiadomosci zamienionej na znaki ASCII
    vector<long long> vecASCII;
    for (int i = 0; i < str.length(); i++)
        vecASCII.push_back(int(str[i]));

    cout << "ASCII: ";
    for (const auto& i : vecASCII)
        cout << i << ' ';

    // szyfrowanie wiadomosci
    vector<long long> vecCiphered;
    for (const auto& i : vecASCII)
        vecCiphered.push_back(powmod(i, e, n));

    cout << "\nCiphered: ";
    for (const auto& i : vecCiphered)
        cout << i << ' ';

    // deszyfrowanie wiadomosci
    vector<long long> vecDeciphered;
    for (const auto& i : vecCiphered)
        vecDeciphered.push_back(powmod(i, d, n));

    cout << "\nDeciphered: ";
    for (const auto& i : vecDeciphered)
        cout << i << ' ';

    // ponowna zamiana na tekst ktory mozemy odczytac
    string revertedStr;
    for (const auto& i : vecDeciphered)
        revertedStr += char(i);

    cout << "\nReverted message: " << revertedStr << "\n\n";
}

int main()
{
    RSA("input.txt");

    system("PAUSE");
    return EXIT_SUCCESS;
}
