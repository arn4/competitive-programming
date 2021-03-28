#include <bits/stdc++.h>
//#include <ext/rope>

using namespace std;
//using namespace __gnu_cxx;

/* DEBUG UTILITIES */
// outstream operator for pair
template <typename type_first, typename type_second>
ostream& operator << (ostream &out, const pair<type_first, type_second> P) {
  out << '{' << P.first << ',' << P.second << '}';
  return out;
}
// convert an iterable to a string that can be printed
template <typename type_iterator>
string ite2string(type_iterator begin, type_iterator end) {
  stringstream out;
  bool inserted = false;
  out << '[';
  while (begin != end) {
    out << *begin << ", ";
    inserted = true;
    begin++;
  }
  string ans = out.str();
  if (inserted) {
    ans.pop_back(); ans.pop_back();
  }
  return ans + ']';
}

template <class stream, class iterable, class begin = decltype(begin(declval<iterable>()))>
stream& operator << (stream& out, const iterable I) {
  out << ite2string(I.begin(), I.end());
  return out;
}

#if DEBUG
  #define dbg_var(x) clog << #x << ": " << x << endl;
  #define dbg_arr(x, len) clog << #x << ": " << ite2string(x, x + len) << endl;
  #define dbg_msg(x) clog << x << endl;
  ifstream input_from_file("input.txt");
  ofstream output_on_file("output.txt");
  //Comment next 2 lines for using IO with files during debug
  //#define cin input_from_file
  //#define cout output_on_file
#else
  #define dbg_var(x)
  #define dbg_arr(x, len)
  #define dbg_ite(x)
  #define dbg_msg(x)
  #define endl '\n'
#endif

/* SHORTCUTS */
#define forn(i, n) for (unsigned int i = 0; i < (unsigned int)(n); i++)
#define load(V) for (auto &v: V) {cin >> v;}
#define pb(a) push_back(a)
#define all(a) (a).begin(), (a).end()
#define st first
#define nd second
#define mp(a, b) make_pair(a, b)

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
/**********************************************************************/
/*                           END TEMPLATE                             */
/**********************************************************************/

int main() {
  // IO optimizer. Comment if interactive problem
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  // Code here...

  return 0;
}
