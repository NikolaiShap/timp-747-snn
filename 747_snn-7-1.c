#include <stdio.h>

void sort(int mass[], int start, int end ) 
{
	int i = start, j = end, d, beh = mass[(start + end) / 2];
	while (i <= j) {
		for (; mass[i] < beh; i++);
		for (; mass[j] > beh; j--);
		if (i <= j) {
			d = mass[i];
			mass[i++] = mass[j];
			mass[j--] = d;
		}
	}
	if (start < j) sort(mass, start, j);
	if (i < end) sort(mass, i, end);
}

int main()
{
	int len;
	scanf("%d", &len);
	int mass[len];
	for (int i = 0; i < len; i++)
	{
		scanf("%d", &mass[i]);
	}
	sort(mass, 0, len - 1);

	for (int i = 0; i < len; i++)
	{
		printf("%d ", mass[i]);
	}
	printf("\n");
	return 0;
}

