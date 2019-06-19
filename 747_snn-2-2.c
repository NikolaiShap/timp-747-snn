#include <stdio.h>
#include<malloc.h>

int main()
{
	char *tmp;
	char tmp1 ='(';
	char tmp2 =')';
	int x = 0, y = 0, count;
	scanf("%d", &count);
	tmp = (char*)malloc(count);
	for (int i = 0; i < count; i++)
	{
		getchar();
		scanf("%c", &tmp[i]);
		if (tmp[i] == tmp1) x++;
		else if (tmp[i] == tmp2) y++;

	}
	if (x == y) printf("1");
	else printf("0");

    
}
