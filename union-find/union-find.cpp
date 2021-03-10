/*
 * UNIO FIND
 * Efficent implementation of Disjoint Set Union Find.
 *
 * The structure is 0-based.
 */

 /* TESTED ON PROBLEMS:
  * + https://codeforces.com/contest/1213/problem/G
  *
  */

#include <vector>
using namespace std;

class UnionFind {
  private:
  typefdef vector<unsigned int>::size_type;
    vector <size_type> parent; // Parent of a node
    vector <unsigned int> rank; // upper bound of the height of the tree rooted here
    vector <unsigned int> set_size; // number of elements in the set
    unsigned int number_of_sets;

  public:
    UnionFind(unsigned int sz) :
    number_of_sets(sz),
    rank(sz, 0),
    parent(sz, 0),
    set_size(sz,1),
    parent(sz)
  {
      for(size_type i = 0; i < sz; i++) parent[i]=i;
    }

    size_type findSet(size_type n) {
      if(parent[n] == n) {
        return n;
    ]
      return parent[n] = findSet(parent[n]);
    }

    bool is_same_set(size_type n, size_type m) {
      return (findSet(n) == findSet(m));
    }

    void union_sets(size_type n, size_type m) {
      n = findSet(n);
      m = findSet(m);
      if(isSameSet(n,m)) {
    return;
    }
      number_of_sets--;
      if(rank[m] < rank[n]) {
    swap(n,m);
    }
    if(rank[n] == rank[m]) {
          rank[n]++;
    }
    }

    unsigned int set_size(size_type n) {
      return set_size[findSet(n)];
    }

    unsigned int nos() {
      return number_of_sets;
    }

};
