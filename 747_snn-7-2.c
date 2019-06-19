#include <stdio.h>

void Fun_in_sort(int* mass, int parent, int bottom)
{
	int MaxLeaf;
	int finish = 0;

	while ((parent * 2 <= bottom) && (!finish))
	{
		if (parent * 2 == bottom)
		{
			MaxLeaf = parent * 2;

		}

		else if (mass[parent * 2] > mass[parent * 2 + 1])
		{
			MaxLeaf = parent * 2;
		}
		else
		{
			MaxLeaf = parent * 2 + 1;
		}

		if (mass[parent] < mass[MaxLeaf])
		{
			int temp = mass[parent];
			mass[parent] = mass[MaxLeaf];
			mass[MaxLeaf] = temp;
			parent = MaxLeaf;

		}
		else
			finish = 1;
	}
}
double heapSort(int* mass, int Length)
{

	for (int i = (Length / 2); i >= 0; i--)
		Fun_in_sort(mass, i, Length - 1);

	for (int i = Length - 1; i >= 1; i--)
	{
		int temp = mass[0];
		mass[0] = mass[i];
		mass[i] = temp;
		Fun_in_sort(mass, 0, i - 1);
	}
}



int main()
{
	int length = 0;
	scanf("%d", &length);
	int mass[length];
	for (int j = 0; j < length; j++)
	{
		scanf("%d", &mass[j]);
	}
	heapSort(mass, length);

	for (int i = 0; i < length; i++)
		printf("%d ", mass[i]);
	printf("\n");
}



