# simpleRSA
simple RSA encrypting c++ library
</br>
Installation : 
cd cmake
cmake ..
make
libsimpleRSA.a will appear in the bin directory, you need to copy it where you want first, then copy also the header.

Compiling with simple RSA : 
g++ -lgmpxx -lgmp -lsimpleRSA main.cpp

| name                  | params                                                                    | Description                           | Return value       |
|-----------------------|---------------------------------------------------------------------------|---------------------------------------|--------------------|
| simpleRsa::keyGen     | mpz_class n, mpz_class e, mpz_class d                                     | Set params to a new couple of keys    |        void        |
| simpleRsa::encryption | mpz_class e, mpz_class n, std::ostream& os, std::istream &is, bool verbose| Encrypt from os to is                 |        void        |
| simpleRsa::decryption | mpz_class d, mpz_class n, std::ostream& os, std::istream &is, bool verbose| Decrypt from os to is                 |        void        |
