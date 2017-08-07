#include <iostream>
#include <vector>
using namespace std;

#define MAX 1000
int fibo[MAX];
int fibonacci(int N)
{
	if (N == 0) return 0;
	if (N == 1) return 1;
	if (N == 2) return 1;
        if (fibo[N] != 0)
		return fibo[N];
	else {
		fibo[N] = fibonacci(N-1) + fibonacci(N-2);
	}
	return fibo[N];
}

int main()
{
	cout << " the output of fibonacci numbers are as follows " << endl;
	for (int i=0; i<10; i++)
	{

		cout << i << "  " << fibonacci(i) << endl;

	}
	return 0;
}
