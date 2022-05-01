#include <iostream>
#include <math.h>
#include <windows.h>

long long powmod(long long a, long long b, long long c)
{
    long long outcome = 1, y = a;

    while (b > 0)
    {
        if (b % 2 == 1)
        {
            outcome = (outcome * y) % c;
        }

        y = (y * y) % c;
        b = b / 2;
    }

    return outcome % c;
}


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

int main()
{
    //long long a, b, c;
    //std::cin >> a >> b >> c;

    //long long outcome = powmod(a, b, c);
    //std::cout << outcome;
    std::cout << "Podaj liczbe 'g': ";
    long long g; std::cin >> g;

    std::cout << "Podaj liczbe 'p': ";
    long long p; std::cin >> p;

    bool isPrimary;
    isPrimary = probne(p);

    std::cout << "Czy jest liczba pierwsza? " << isPrimary << '\n';
    if (isPrimary == 0)
        return 1;

    std::cout << "Podaj swoje 'a': ";
    long long a; std::cin >> a;

    long long A = powmod(g, a, p);
    std::cout << "A = " << A;

    std::cout << "\nPodaj b: ";
    long long B; std::cin >> B;
    long long Ka = powmod(B, a, p);

    std::cout << "\nK(a) = " << Ka;

    std::cout << '\n';
    system("pause");

    return 0;
}
