#ifndef simpleRsa_H
#define simpleRsa_H
#include <gmpxx.h>
#include <string>
namespace simpleRsa
{
	void bezout (mpz_class a, mpz_class b, mpz_class &u, mpz_class &v );
        mpz_class pow ( mpz_class number, mpz_class n, mpz_class mod);
        bool isPrime (mpz_class number);
        mpz_class rand();
	void keyGen (mpz_class &n, mpz_class &e, mpz_class &d);
        std::string int_to_binary (uint8_t number);
        uint8_t binary_to_int(std::string bin);
        void encryption(mpz_class key, mpz_class n, std::ostream &os, std::istream &is, bool verbose = false);
	void decryption (mpz_class key, mpz_class n, std::ostream &os, std::istream &is, bool verbose = false);
}

#endif
