#include <stdio.h>
int main(void)
{
	int n = 0, q = 0, q2 = 0, r = 1, c = 0;
	scanf("%d", &n);
	scanf("%d", &q2);
	for (int i = 1; i < n; i++)
	{
		scanf("%d", &c);
		if ((i % 2) == 1 && r != 0)
		{
			q = c; if (q2 <= q) r = 1; else r = 0;
		}
		if ((i % 2) == 0 && r != 0) {
			q2 = c; if (q <= q2) r = 1; else r = 0;
		}

	}
	printf("%d\n", r);
}

