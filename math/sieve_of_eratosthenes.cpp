/*
 * SIEVE of ERATOSTHENES
 * This is an implementation of the Sieve of Erarosthenes.
 * Classic is the basic implementation that can answer only to is_prime question.
 * MinimumPrimeFactor is a modification that can easilly factorize any number,
 * with a complexity that is nearly costant (O(logn*loglogn) at worst case, much better in practice).
 */

#include <vector>
#include <unordered_set>
#include <map>
using namespace std;

template<typename unsigned_integer>
class ClassicSieve {
  private:
    vector<unsigned_integer> prime;
    unsigned_integer max_n;
  public:
    ClassicSieve(unsigned_integer max_n) : max_n(max_n), prime(max_n, true) {
      // 1 is not prime
      prime[1] = false;

      // even numbers
      for(unsigned_integer i = 4; i <= max_n; i+=2) {
        prime[i] = false;
      }

      // all the others
      for (unsigned_integer p = 3; p*p <= max_n; p++) {
        if (prime[p]) {
          for(unsigned_integer j = 2*p; j <= max_n; j+=p) {
            prime[j] = false;
          }
        }
      }
    }

    bool is_prime(unsigned_integer n) const {
      return prime[n];
    }
};


template<typename unsigned_integer>
class MinimumPrimeFactor {
  private:
    unsigned_integer max_n;
    vector<unsigned_integer> lp;
  public:
    vector<unsigned_integer> prime_list;
    MinimumPrimeFactor(unsigned_integer max_n) : max_n(max_n), lp(max_n+1, 0) {
      for (unsigned_integer i=2; i<=max_n; ++i) {
        if (lp[i] == 0) {
          lp[i] = i;
          prime_list.push_back(i);
        }
        for(auto p: prime_list) {
          if (p*i > max_n) {
            break;
          }
          lp[p*i] = p;
        }
      }
    }

    unsigned_integer mpf(unsigned_integer n) const {
      return lp[n];
    }

    map<unsigned_integer, unsigned_integer> factorize(unsigned_integer n) const {
      map<unsigned_integer, unsigned_integer> factors;
      while (lp[n]!=n) {
        factors[lp[n]]++;
        n /= lp[n];
      }
      factors[n]++;

      return factors;
    }

    bool is_prime(unsigned_integer n) const {
      return (lp[n]==n);
    }
};
