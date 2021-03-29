/* EULER TOTIENT FUNCTION
 * This implementation is essantially based on prime factorization.
 *
 * The range version is instead a modification of the Sieve.
 */

#include <vector>

template<typename unsigned_integer>
unsigned_integer euler_phi(unsigned_integer n) {
  unsigned_integer ans = n;
  for (unsigned_integer i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) {
        n /= i;
      }
      ans -= ans/i;
    }
  }
  if (n > 1) {
    ans -= ans / n;
  }
  return ans;
}

template<typename unsigned_integer>
class EulerPhi {
  private:
    unsigned_integer max_n;
    vector<unsigned_integer> phi;

  public:
    EulerPhi(unsigned_integer max_n) : max_n(max_n), phi(max_n+1) {
      for (unsigned_integer i = 0; i <= max_n; i++) {
        phi[i] = i;
      }

      for (unsigned_integer p = 2; p <= max_n; p++) {
        if (phi[p] == p) {
          for (unsigned_integer j = p; j <= max_n; j += p) {
            phi[j] -= phi[j] / p;
          }
        }
      }
    }

    unsigned_integer get(unsigned_integer n) const {
      return phi[n];
    }
};