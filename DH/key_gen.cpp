#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;


long long int Large_Number(int n_bits)
{	
	long long int mx = pow(2, n_bits) - 1;
	long long int mn = (mx >> 1) + 1; //division by 2

	long long prime = mn + (rand() % (mx - mn + 1)); 
	return prime;
}


long long int Expon(long long int a, long long int d, const long long int& p)
{ // a^(d) mod p = 1
	long long int r = 1;
	while (d)
	{
		if (d & 1)
		{
			r *= a;
			r %= p;
			d -= 1;
		}
		else
		{
			a = (a*a) % p;
			d >>= 1;
		}
	}
	return r;
}

bool isPrime(const long long int& p, int n_bits)
{
	bool flag = true;

	if (p == 2)
		flag = true;

	else if (!(p & 1)) // if last bit is not 1 (even)
		flag = false;

	else //Millner-Rabin
	{
		long long int p_1 = p - 1, a, x, d = 0;
		int r = 0;
		
		d = p_1;
		while ((d & 1) == 0)
		{
			d >>= 1;
			r++;
		}
		//cout << "/" << p << " Self - check " << pow(2, r) * d << "/";
	
		// p-1 = d * 2^r
		for (int i = 0; i < n_bits; i++)
		{
			a = 2 + rand() % ((p - 2) - 2);
			x = Expon(a, d, p);
			if (x != 1 && x != p_1)
			{
				flag = false;
				break;
			}
				
		}
	}
	return flag;
}

void Factorization(long long int n, vector <int>& prime_div)
{
	

	if (n % 2 == 0)
	{
		do
		{
			n /= 2;
		} while (n % 2 == 0);

		prime_div.push_back(2);
	}

	long int i = 3;
	long int sqrt_n = sqrt(n);

	while (i <= sqrt_n)
	{
		if (n % i == 0)
		{
			do
			{
				n /= i;
			} while (n % i == 0);

			prime_div.push_back(i);
		}
		i += 2;
	}

	if (n > 2)
		prime_div.push_back(n);
}

long int Prim_Root(const long long int& p)
{
	long long int phi = p - 1;
	vector <int> prime_div;
	Factorization(phi, prime_div);

	//for (int i = 0; i < prime_div.size(); i++)
	//	cout << prime_div[i] << " ";
	long long int g = 2;
	for (; g <= phi; g++)
	{
		bool flag = true;

		// if g is prim_root then for each 1<l<phi(n)   g^l mod n != 1
		for (auto it = prime_div.begin(); it != prime_div.end(); it++)
		{
			if (Expon(g, phi / (*it), p) == 1)
			{
				flag = false;
				break;
			}
		}

		if (flag)
			break;
	}

	return g;
}


int main()
{
	srand(time(NULL)); //each time random int

	long long int p;
	int n_bits = 8;
	bool status = false;

	while (!status)
	{
		p = Large_Number(8);
		status = isPrime(p, n_bits);
		//cout << status << " " << p << endl;
	}
	cout << "Prime number: " << p << endl;
	cout << "Prime root: " << Prim_Root(p);
	
}