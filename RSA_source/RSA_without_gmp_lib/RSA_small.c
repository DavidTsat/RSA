#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_phi_n(int p, int q)
{	
	return (p-1)*(q-1);
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

int get_d(int phi_n, int e)
{
	int x, y;
	gcdExtended(phi_n, e, &x, &y);

	if( y<0 )
 	{	
		return phi_n + y;
	}
	
	return y;
}

int modexp(int a, int b, int n)
{
	int r = 1;
    
	while(1)
	{
        	if(b % 2 == 1)
		{
            		r = r * a % n;
        	}
		b /= 2;
        	if( b == 0 )
		{
            		break;
		}
        	a = a * a % n;
	}
    return r;
}

int RSA_encrypt(int message, int e, int n)
{
	if ( message >= n)
	{
		fprintf(stderr, "Wrong message!\n");
		exit(EXIT_FAILURE);
	}	
	return modexp(message, e, n);
}

int RSA_decrypt(int dec, int d, int n)
{
	return modexp(dec, d, n);
}
int main()
{

	int p = 11;
	int q = 13;
	int e = 7;
	int d;
	int n = p*q;

	int phi_n = get_phi_n(p, q);	

	d = get_d(phi_n, e);
        
	int message = 127;
	
	int dec = RSA_encrypt(message, e, n);
	printf("enc = %d\n", dec);

	int enc = RSA_decrypt(dec, d, n);
	printf("dec = %d\n", enc);
}
