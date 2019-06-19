#include <stdio.h>

int TipStep(int step)
{
	step = (int)(step / 1.247);
	if (step < 1)
		step = 1;
	return step;
}

void sort(int mass[], int Length)
{
	int step = Length;
	while (1)
	{
		step = TipStep(step);
		int fin = 0;
		for (int i = 0; i < Length - step; i++)
		{
			int j = i + step;
			if (mass[i] > mass[j])
			{
				int t = mass[i];
				mass[i] = mass[j];
				mass[j] = t;
				fin = 1;
			}
		}
		if (step == 1 && !fin)
			break;
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	int mass[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &mass[i]);
	}
	sort(mass, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", (mass[i]));

	}
	printf("\n");
}
