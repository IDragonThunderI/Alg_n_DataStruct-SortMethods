#include <iostream>
#include <functional>
#include <ctime>
#include <cmath>
using namespace std;

void init(int B[], int n);
void copy(int A[], int B[], int n);
void print(int B[], int n);
void Inclusion_sort(int B[], int n);
void Selection_sort(int B[], int n);
void Bubble_sort(int B[], int n);
void Shell_sort(int B[], int n);
void Hoar_sort(int B[], int n);
void Qsort(int B[], int f, int l);
void Heap_sort(int B[], int n);
void Make_heap(int B[], int L, int R);
void result(string title, function<void(int[], int)> sort, int B[], int n);

int main()
{
	system("chcp 1251");
	system("cls");

	int n;
	cout << "Введите размер массива: ";
	cin >> n;
	
	int* A = new int[n];
	int* B = new int[n];
	
	init(A, n);
	print(A, n);
	
	copy(A, B, n);
	result("Inclusion_sort", Inclusion_sort, B, n);
	print(B, n);
	
	copy(A, B, n);
	result("Selection_sort", Selection_sort, B, n);
	print(B, n);
	
	copy(A, B, n);
	result("Bubble_sort", Bubble_sort, B, n);
	print(B, n);
	
	copy(A, B, n);
	result("Shell_sort", Shell_sort, B, n);
	print(B, n);
	
	copy(A, B, n);
	result("Hoar_sort", Hoar_sort, B, n);
	print(B, n);

	copy(A, B, n);
	result("Heap_sort", Heap_sort, B, n);
	print(B, n);

	delete[] A, B;

	system("pause");
	return 0;
}

void init(int A[], int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		A[i] = rand() % 100 + 1;
}

void copy(int A[], int B[], int n)
{
	for (int i = 0; i < n; i++)
		B[i] = A[i];
}

void print(int B[], int n)
{
	if (n <= 100)
	{
		cout << "Arr = {";
		for (int i = 0; i < n; i++)
			cout << B[i] << " ";
		cout << "}" << endl << endl;
	}
}

void Inclusion_sort(int B[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int buf = B[i];
		int j = i - 1;

		while (buf < B[j] && j >= 0)
		{
			B[j + 1] = B[j];
			j--;
		}

		B[j + 1] = buf;
	}
}

void Selection_sort(int B[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int buf = B[i];
		int min = i;

		for (int j = i + 1; j < n; j++)
		{
			if (B[j] < buf)
			{
				buf = B[j];
				min = j;
			}
		}
			
		B[min] = B[i];
		B[i] = buf;
	}
}

void Bubble_sort(int B[], int n)
{
	int buf;
	
	for (int i = 0; i < n - 1; i++)
	{
		int count = 0;

		for (int j = n - 1; j > i; j--)
		{
			if (B[j] < B[j - 1])
			{
				buf = B[j];
				B[j] = B[j - 1];
				B[j - 1] = buf;
				count = 1;
			}
		}

		if (count == 0)
			break;
	}
}

void Shell_sort(int B[], int n)
{
	int interval_arr[100];
	int step = (int)(round(log(n) / log(3)) - 1);

	if (step < 1)
		step = 1;

	interval_arr[step] = 1;

	for (int k = step; k >= 1; k--)
		interval_arr[k - 1] = 3 * interval_arr[k] + 1;

	for (int s = 0; s <= step; s++)
	{
		int curr_interval = interval_arr[s];
		
		for (int j = curr_interval; j < n; j++)
		{
			int index = j - curr_interval;
			int buf = B[j];
			
			while (index >= 0 && buf <= B[index])
			{
				B[index + curr_interval] = B[index];
				index -= curr_interval;
			}

			B[index + curr_interval] = buf;
		}
	}
}

void Hoar_sort(int B[], int n)
{
	Qsort(B, 0, n - 1);
}

void Qsort(int B[], int f, int l)
{
	int first = f, last = l;
	int separator = B[((first + last) / 2)];

	while (first <= last)
	{
		while (B[first] < separator)
			first++;
		while (B[last] > separator)
			last--;
		if (first <= last)
		{
			int buf = B[first];
			B[first] = B[last];
			B[last] = buf;
			first++;
			last--;
		}
	}

	if (f < last)
		Qsort(B, f, last);
	if (first < l)
		Qsort(B, first, l);
}

void Heap_sort(int B[], int n)
{
	int L = n / 2;
	int R = n - 1;

	while (L > 0)
	{
		L--;
		Make_heap(B, L, R);
	}

	while (R > 0)
	{
		int buf = B[0];
		B[0] = B[R];
		B[R] = buf;
		R--;
		Make_heap(B, L, R);
	}
}

void Make_heap(int B[], int L, int R)
{
	int i = L;
	int j = 2 * L + 1;
	int x = B[L];

	if ((j < R) && (B[j] < B[j + 1]))
		j++;

	while ((j <= R) && (x < B[j]))
	{
		int buf = B[i];
		B[i] = B[j];
		B[j] = buf;
		i = j;
		j = 2 * j + 1;
		if ((j < R) && (B[j] < B[j + 1]))
			j++;
	}
}

void result(string title, function<void(int[], int)> sort, int B[], int n)
{
	cout << title << ": ";
	clock_t start, finish;

	start = clock();
	sort(B, n);
	finish = clock();

	cout << (double)(finish - start) / CLOCKS_PER_SEC << " sec." << endl << endl;
}
