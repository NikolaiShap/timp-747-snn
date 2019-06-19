#include <stdio.h>

void sort(int Length, int mass[]) 
{
	int i, j, step, change;

	for (step = Length / 2; step > 0; step /= 2) 
	{
		for (i = step; i < Length; i++) 
		{
			change = mass[i];

			for (j = i; j >= step; j -= step) 
			{
				if (change < mass[j - step])mass[j] = mass[j - step];
				else break;
			}
			mass[j] = change;
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	int mass[n];
	for (int i = 0; i < n; i++) { scanf("%d", &mass[i]); }
	sort(n, mass);
	for (int i = 0; i < n; i++) { printf("%d ", mass[i]); }
	printf("\n");
	return 0; 
}
