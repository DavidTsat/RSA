#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>


int check_range_of_message(mpz_t pt, mpz_t n)
{
    if (mpz_cmp(pt, n) > 0) {
	return 1;
    }

    return 0;
}

void RSA_encrypt(mpz_t ct, mpz_t pt, mpz_t e, mpz_t n)
{
    mpz_powm(ct, pt, e, n);
}

void RSA_decrypt(mpz_t pt, mpz_t ct, mpz_t d, mpz_t n)
{
    mpz_powm(pt, ct, d, n);	
}

void set_p_q(mpz_t p, mpz_t q, const char* p_str, const char* q_str)
{
	mpz_init_set_str(p, p_str, 10);
	mpz_init_set_str(q, q_str, 10);
}

void get_n(mpz_t p, mpz_t q, mpz_t n)
{	
	mpz_init(n);
	mpz_mul(n, p, q);
}

void get_phi_n(mpz_t p, mpz_t q, mpz_t phi_n)
{	
	mpz_t p_minus_one, q_minus_one, one;

	mpz_init(p_minus_one);
	mpz_init(q_minus_one);
	mpz_init(phi_n);
	mpz_init(one);
	
	mpz_init_set_str(one, "1", 10);
	
	mpz_sub(p_minus_one, p, one);
	mpz_sub(q_minus_one, q, one);

	mpz_mul(phi_n, p_minus_one, q_minus_one);
}

void get_coefficents_of_extended_Euclid(mpz_t s, mpz_t t, const mpz_t a, const mpz_t b) //a*s + b*t = g
{
	mpz_t g;

	mpz_init(g);
	mpz_init(s);
	mpz_init(t);
	
	mpz_gcdext (g,s,t,a,b);
}

void get_modular_inverse(mpz_t d, const mpz_t e, const mpz_t phi_n)
{
	mpz_t t, s, zero;
	
	mpz_init(t);
	mpz_init(s);
	mpz_init(d);
	mpz_init(zero);

	mpz_init_set_str(zero, "0", 10);
	
	get_coefficents_of_extended_Euclid(s, t, e, phi_n);
	
	if(mpz_cmp(s, zero) < 0)
	{	
		mpz_abs(d,s);
	}

	else
	{	
		mpz_set(d,s);
	}	
	// Clear local vars
}

int main(int argc, char* argv[])
{
	int i = 0;
	
	mpz_t p, q, n, phi_n, e, d;
	
	set_p_q(p, q, "32416190071", "32416188793");
	
	get_n(p, q, n);

	gmp_printf("n:   %Zd\n", n);
	
	get_phi_n(p,q,phi_n);

	gmp_printf("phi_n:   %Zd\n", phi_n);
	
	mpz_init_set_str(e, "65537", 10);
	
	gmp_printf("e:   %Zd\n", e);
	
	get_modular_inverse(d, e, phi_n);

	gmp_printf("d:   %Zd\n", d);
	
	for (i = 1; i < argc; ++i) {
	    //const char* plaintext = "Hello";
	    const char* plaintext = argv[i];
	    
	    char buffer[64] = { 0 };

	    mpz_t pt, ct, recovered;
	    
	    mpz_init(pt);

	    mpz_init(ct);

	    mpz_init(recovered);

	    mpz_import(pt, strlen(plaintext), 1, 1, 0, 0, plaintext); // from plaintext to bigint
	    
	    if (1 == check_range_of_message(pt, n)) {
		    fprintf(stderr, "%s", "Long message.\n");
		    exit(EXIT_FAILURE);
	    }
	    
	    RSA_encrypt(ct, pt, e, n);
	    gmp_printf("Encoded:   %Zd\n", ct);
	    
	    RSA_decrypt(recovered, ct, d, n);
	    gmp_printf("Decoded:   %Zd\n", recovered);
	    
	    mpz_export(buffer, NULL, 1, 1, 0, 0, pt); //from bigint to plaintext
	    printf("As String: %s\n", buffer);
     
	    mpz_clears(pt, ct, recovered, NULL);
	}
	mpz_clears(n, e, d, phi_n, NULL);
    	return 0; 
}
