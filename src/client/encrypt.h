#include <cmath>
#include <numeric>
 
// Two random prime numbers
double p = 3, q = 7;

// First part of public key:
double n = p * q;

// Finding other part of public key.
// e stands for encrypt
double e = 2;
double phi = (p - 1) * (q - 1);
while (e < phi) {
    // e must be co-prime to phi and
    // smaller than phi.
    if (std::gcd(e, phi) == 1)
        break;
    else
        e++;
}

// Private key (d stands for decrypt)
// choosing d such that it satisfies
// d*e = 1 + k * totient
int k = 2; // A constant value
double d = (1 + (k * phi)) / e;

double encrypt(double message)
{
    // Encryption c = (msg ^ e) % n
    double encrypted_msg = std::fmod(pow(message, e), n);
    printf("\nEncrypted data = %lf", encrypted_msg);
}

double decrypt(double encrypted_msg)
{
    // Decryption m = (c ^ d) % n
    double message = fmod(pow(encrypted_msg, d), n);
    printf("\nOriginal Message Sent = %lf", message);
 
    return 0;
}