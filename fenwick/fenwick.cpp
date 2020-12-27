/*
 * FENWICK TREE
 * This is an implementation of Binary Index Tree for a generic associative and cummotative operation.
 * The tree is 1-based: all the indeces from 1 to sz (included) are valid.
 * query(i) gives the result of a_1 + a_2 + ... + a_i. (+ is the generic operation)
 * updated(i, v) modify a_i to a_i + v.
 *
 * There is also an implementation of the RangeFenwick  for a generic associative and commutative and invertible
 * operation. It needs also an efficent implementation of the "multiplication" (appling many times the operation_identity
 * on the same element), throught multiple_operation(e, times). All the intervals of the class inludes boundaries.
 */

 /* TESTED ON PROBLEMS:
  * + RangeSumQuery    | https://www.spoj.com/problems/FENTREE/
  * + RangeXorQuery    | https://atcoder.jp/contests/abc185/tasks/abc185_f
  */

#include <vector>
using namespace std;

template<
  typename type_query,
  type_query operation(const type_query &, const type_query &),
  const type_query& operation_identity
>
class Fenwick {
  private:
    typedef typename vector<type_query>::size_type size_type;
    vector <type_query> tree;

  public:
    Fenwick(size_type  sz) {
      tree.assign(sz + 1, operation_identity);
    }

    type_query query(size_type i) {
      type_query ans = operation_identity;
      int k = int(i);
      while(k != 0) {
        ans = operation(ans, tree[size_type(k)]);
        k -= k & (-k);
      }

      return ans;
    }

    void update(size_type i, type_query v) {
      int k = int(i);
      while((unsigned int)(k) < tree.size() ) {
        tree[size_type(k)] = operation(tree[size_type(k)], v);
        k += k & (-k);
      }
    }
};

template<
  typename type_query,
  type_query operation(const type_query &, const type_query &),
  type_query multiple_operation(const type_query&, const typename vector<type_query>::size_type),
  type_query inverse(const type_query&),
  const type_query& operation_identity
>
class RangeFenwick {
  private:
    typedef typename vector<type_query>::size_type size_type;
    Fenwick<type_query, operation, operation_identity> F1, F2;

    type_query partial_sum(size_type k) {
      return operation(multiple_operation(F1.query(k), k), inverse(F2.query(k)));
    }

  public:
    RangeFenwick(size_type sz) :
      // The +1 after sz is needed to avoid problems when calling update(r+1, v)
      F1(sz+1),
      F2(sz+1)
    {
    }

    // query on the interval [l,r]
    type_query query(size_type l, size_type r) {
      return operation(partial_sum(r), inverse(partial_sum(l - 1)));
    }

    // update on the interval [l,r]
    void update(size_type l, size_type r, type_query v) {
      F1.update(l, v);
      F1.update(r + 1, inverse(v));
      F2.update(l, multiple_operation(v, l - 1));
      F2.update(r + 1, multiple_operation(inverse(v), r));
    }
};

/*
 * Specific Problems
 */
template <typename integer_type>
inline integer_type sum(const integer_type &a, const integer_type &b) {
  return a + b;
}

template <typename integer_type>
inline integer_type inverse_sum(const integer_type &a) {
  return -a;
}

template <typename integer_type>
inline integer_type multiplication(const integer_type &a, const typename vector<integer_type>::size_type t) {
  return a * integer_type(t);
}

template <typename integer_type>
const integer_type integer_zero_value = 0;

// Classic Fenwick implementation: query is partial sum; point update
template <typename integer_type>
using RSMClassicFenwick = Fenwick<
                        integer_type,
                        sum<integer_type>,
                        integer_zero_value<integer_type>
                      >;

// RSM implemented with RangeFenwick: query and updates on intervals.
template <typename integer_type>
using RSMFenwick = RangeFenwick<
                        integer_type,
                        sum<integer_type>,
                        multiplication<integer_type>,
                        inverse_sum<integer_type>,
                        integer_zero_value<integer_type>
                      >;
