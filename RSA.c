#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

char* p = "7176089";
char* q = "7184699";
 
void multiply(char* a, char* b, char* res)
{
	int lenA = strlen(a);
	int lenB = strlen(b);

	int i, j;


	int* c = malloc(sizeof(int)*(lenA+lenB));

	memset(c, 0, sizeof(int) * (strlen(a) + strlen(b)));

	for (i = lenA - 1; i >= 0; i--)
		for (j = lenB - 1; j >= 0; j--)					
			c[i + j + 1] += (b[j] - '0') * (a[i] - '0');

	for (i = lenA + lenB - 1; i >= 0; i--)
	{
		if (c[i] >= 10)
		{
			c[i - 1] += c[i] / 10;
			c[i] %= 10;
		}
	}
		
	i = 0;
	while (c[i] == 0)
		i++;

	j = 0;
	while (i < lenA + lenB)
	{
		res[j] = c[i] + '0';
		i++; j++;
	}

	res[j] = 0;
	free(c);
}

char* get_n(char* p, char* q)
{
	char* res = malloc(strlen(p) + strlen(q));

	multiply(p, q, res);
	
	return res;
}

int gcdExtended(int a, int b, int *x, int *y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
 
    int x1, y1;
    int gcd = gcdExtended(b%a, a, &x1, &y1);
 
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}

int main()
{
	mpz_t nnn;
	char* n = get_n(p, q);

	printf("%s\n",n);
	
	char* phi_n = get_n("7176088","7184698");
	printf("%s\n", phi_n);
	
        int a = 99;
        int b = 78;
	int x, y, gcd;
	gcd = gcdExtended(a, b, &x, &y);
	printf("GCD: %d, x = %d, y = %d", gcd, x, y);
	return 0;
}
