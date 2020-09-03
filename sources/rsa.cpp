#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include "rsa.h"
	void simpleRsa::bezout (mpz_class a, mpz_class b, mpz_class &u, mpz_class &v )
	{
		u = 1;
		v = 0;
		mpz_class u1;
		mpz_class v1;
		while (b != 0)
		{
			mpz_class r =a%b;
			mpz_class q = a/b;
			mpz_class u2 = u - (q*u1);
			mpz_class v2 = v - (q*v1);
			a = b;
			b = r;
			u = u1;
			v = v1;
			u1 = u2;
			v1 = v2;
		}
	}
	mpz_class simpleRsa::pow ( mpz_class number, mpz_class n, mpz_class mod)
	{
		mpz_class res = 1;
		while (n > 0)
		{
			if(n%2 == 1)
			{
				res *= number;
				res%=mod;
			}
			n/=2;
			number *= number;
			number %= mod;
		}
		return res;
	}

	bool simpleRsa::isPrime (mpz_class number)
	{
        	std::random_device r;
        	std::uniform_int_distribution<unsigned int> distribution(0, std::numeric_limits<unsigned int>::max());
        	for(unsigned int it=0; it < 3; ++it)
        	{
                	if(pow(distribution(r), number-1, number) != 1)
                	{
                        	return false;
                	}
        	}
       	 	return true;
	}
	mpz_class simpleRsa::rand()
	{
		std::random_device r;
                std::uniform_int_distribution<char> distribution('0', '9');
		std::string str = "1";
		for(unsigned int it = 0; it < 199; ++it)
		{
			str.push_back(char(distribution(r)));
		}
		return  mpz_class(str);
	}
	std::string simpleRsa::int_to_binary (uint8_t number)
	{
		std::string str;
		for(unsigned int it=0; it < 8; ++it)
		{
			if(number%2 == 0)
				str.push_back('0');
			else
				str.push_back('1');
			number = number >> 1;
		}
		std::reverse(str.begin(), str.end());
		return str;
	}
	uint8_t simpleRsa::binary_to_int(std::string bin)
	{
		uint8_t number = 0;
		for(unsigned int it=0; it < 8; ++it)
                {
			if(bin[it] == '1')
				++number;
			if(it != 7)
			number = number << 1;
		}
		return number;
	}
	void simpleRsa::encryption(mpz_class key, mpz_class n, std::ostream &os, std::istream &is, bool verbose)
	{
		//encrypt 512 bit (64 bytes) each turn
		auto start = std::chrono::steady_clock::now();
		is.seekg(0, std::ios::end);
		unsigned int size = is.tellg();
		is.seekg(0, std::ios::beg);
		unsigned int read = 0;
		unsigned int pourcent = 0;
		while(!is.eof())
		{
			std::string data_str;
			uint8_t data [64];
			is.read((char*)&data, sizeof(uint8_t)*64);
			for(unsigned int it=0; it < 64; ++it)
			{
				data_str += simpleRsa::int_to_binary(data[it]);
			}
			data_str = pow(mpz_class(data_str, 2), key, n).get_str();
			os << data_str << std::endl;
			if(verbose)
			{
				read += 64;
				if(pourcent != int((read*100)/size))
				{
					std::cout << int((read*100)/size) << " % encrypted\n";
					pourcent = int((read*100)/size);
				}
			}
		}
		if(verbose)
		{
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;
    			std::cout << "elapsed time: " << elapsed_seconds.count() << " seconds."<<"\n";
		}
	}
	void simpleRsa::decryption (mpz_class key, mpz_class n, std::ostream &os, std::istream &is, bool verbose)
	{
		auto start = std::chrono::steady_clock::now();
		is.seekg(0, std::ios::end);
                unsigned int size = is.tellg();
                is.seekg(0, std::ios::beg);
                unsigned int read = 0;
                unsigned int pourcent = 0;
		std::string data_str;
		while(getline(is, data_str))
		{
			read+=data_str.size() +1;
			if(verbose)
				data_str = pow(mpz_class(data_str), key, n).get_str(2);
			while(data_str.size() < 512)
			{
				data_str.insert(0, "0");
			}
			uint8_t data[64];
			for(unsigned int it=0; it < 64; ++it)
                        {
				data[it] = simpleRsa::binary_to_int(data_str.substr(it*8, 8));
			}
			os.write((char*)&data, sizeof(uint8_t)*64);
			if(verbose)
                        	if(pourcent != int((read*100)/size))
                        	{
                                	std::cout << int((read*100)/size) << " % decrypted\n";
                                	pourcent = int((read*100)/size);
                        	}
		}
		if(verbose)
                {
                        auto end = std::chrono::steady_clock::now();
                        std::chrono::duration<double> elapsed_seconds = end-start;
                        std::cout << "elapsed time: " << elapsed_seconds.count() << " seconds."<<"\n";
                }
	}

	void simpleRsa::keyGen (mpz_class &n, mpz_class &e, mpz_class &d)
        {
                mpz_class primes [2];
                for(unsigned int it = 0; it < 2; ++it)
                {
                        primes[it] = simpleRsa::rand();
                        while(!simpleRsa::isPrime(primes[it]))
                        {
                                primes[it] = simpleRsa::rand();
                        }
                }
                mpz_class phi = (primes[0]-1)*(primes[1]-1);
                e = simpleRsa::rand();
                while(!simpleRsa::isPrime(e) && e !=  primes [0] && e != primes[1])
                {
                        e = simpleRsa::rand();
                }
                mpz_class u;
                mpz_class v;
                simpleRsa::bezout(e, phi, u, v);
                d = u;
                if(d < 0)
                {
                        d += (mpz_class(d/phi)+1)*phi;
                }
                n=primes[0] * primes[1];
        }
