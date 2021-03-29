/*
 * RANGETREE
 * This rangetree implementation can handle any associative (even not commutative)
 * operation over an array. The tree uses the lazy propagation.
 * The implementation is 0-based (so also 0 is valid index): indeces are valid as
 * long as they are valid for initial array.
 * update_operation is the operation that can be applied to nodes for updating.
 * query_operation is the operation on which the segment tree is based.
 * combine_operation(act_value, size_int, upd_value) is the operation that return the
 * updated node, starting from act_value and size of the interval that the node represents
 * size_int, appling the update operation with upd_value to every node in the interval.
 * To make the lazy propagation works efficently combine_operation must be costant time.
 *
 * All the intervals used in the class methods include the boundaries.
 */

 /* TESTED ON PROBLEMS:
  * + RangeMinQuery    | https://codeforces.com/contest/52/problem/C
  * + RangeSumQuery    | https://www.spoj.com/problems/UPDATEIT/
  * + AdHoc            | https://training.olinfo.it/#/task/rangetree1
  * + AdHoc            | https://training.olinfo.it/#/task/rangetree2
  * + AdHoc (non com.) | https://training.olinfo.it/#/task/rangetree3
  * + RangeSumQuery    | https://www.spoj.com/problems/FENTREE/
  */

#include <vector>
#include <limits>
using namespace std;

template <
  typename type_query,
  typename type_update,
  type_query query_operation(const type_query &, const type_query &),
  type_update update_operation(const type_update &, const type_update &),
  type_query combine_operation(const type_query &, typename vector<type_query>::size_type, const type_update  &),
  const type_query& query_identity,
  const type_update& update_identity
>
class RangeTree {
  private:
    typedef typename vector<type_query>::size_type size_type; // It's assumed that it coincide with: vector<type_update>::size_type size_type
    size_type sz; // ize of the array 
    vector <type_query> tree; // 0 based segment-tree
    vector <type_update> lazy; // ausialiar tree for lazy propagation

    // Functions for moving between nodes
    static size_type left(size_type i) {
      return 2*i + 1;
    }

    static size_type right(size_type i) {
      return 2*i + 2;
    }

    static size_type parent(size_type i) {
      return (i - 1)/2;
    }

    // propagate the laziness of the node
    void propagate_lazy(size_type p, size_type L, size_type  R) {
      if(lazy[p] == update_identity) return;
      // Update this node
      tree[p] = combine_operation(tree[p], R + 1 - L , lazy[p]);

      // Propagate if it isnt a leaf
      if(L != R) {
        lazy[left(p)] = update_operation(lazy[left(p)], lazy[p]);
        lazy[right(p)] = update_operation(lazy[right(p)], lazy[p]);
      }

      // Reset the actual node
      lazy[p] = update_identity;
    }


    // Build the tree given initial vector
    void build(size_type p, size_type L, size_type R, const vector<type_query>& initial) {
      if(L == R) { // It is a leaf
        tree[p] = initial[L];
      } else {
        // Building children
        build(left(p), L, (L + R)/2,  initial);
        build(right(p), (L + R)/2 + 1, R,  initial);
        tree[p] = query_operation(tree[left(p)], tree[right(p)]);
      }
    }


    // Update the range [i, j] with the update_operation operation
    type_query update(size_type p, size_type L, size_type R, size_type i, size_type j, type_update v) {
      propagate_lazy(p, L, R);

      // No intersection
      if(i > R or j < L) {
        return tree[p];
      }

      // Contained
      if(L >= i and R <= j) {
        tree[p] = combine_operation(tree[p], R  + 1 - L, v);
        if(L != R) { // If it isnt a leaf
          lazy[left(p)] = update_operation(lazy[left(p)], v);
          lazy[right(p)] = update_operation(lazy[right(p)], v);
        }
        return tree[p];
      }

      // Updating this node
      return tree[p] = query_operation(update(left(p), L, (L + R)/2, i, j, v),
                                       update(right(p), (L + R)/2 + 1, R, i, j, v));
    }

    // Internal query, it has L and R as parametres
    type_query query(size_type p, size_type L, size_type R, const size_type i, const size_type j) {
      propagate_lazy(p, L ,R);

      if(i > R or j < L) { // No intersection
        return query_identity;
      }
      if(i <= L and R <= j) { // Contained
        return tree[p];
      }

      return query_operation(query(left(p), L, (L + R)/2, i, j),
                             query(right(p), (L + R)/2 + 1, R, i, j));
    }

  public:
    // Build the segment tree given 0-indexed initial
    RangeTree(const vector<type_query> &initial) {
      sz = initial.size();
      tree.assign(4*initial.size(), query_identity);
      lazy.assign(4*initial.size(), update_identity);

      build(0, 0, sz - 1, initial);
    }

    void update(size_type i, size_type j, type_update v) {
      update(0, 0, sz - 1, i, j, v);
    }

    type_query query(size_type i, size_type j) {
      return query(0, 0, sz - 1, i, j);
    }
};



/*********************
 * Specific Problems *
 *********************/

template <typename integer_type>
inline integer_type sum(const integer_type &a, const integer_type &b) {
  return a + b;
}

template <typename integer_type>
inline integer_type min_(const integer_type &a, const integer_type &b) {
  return min(a,b);
}

template <typename integer_type>
inline integer_type max_(const integer_type &a, const integer_type &b) {
  return max(a,b);
}

template <typename integer_type>
inline integer_type combine_sum_sum(const integer_type &a, typename vector<integer_type>::size_type t, const integer_type &b) {
  return a + (integer_type)(t) * b;
}

template <typename integer_type>
inline integer_type combine_sum_min_or_max(const integer_type &a, typename vector<integer_type>::size_type , const integer_type &b) {
  return a + b;
}

template <typename integer_type>
const integer_type integer_zero_value = 0;
template <typename integer_type>
const integer_type integer_max_value = numeric_limits<integer_type>::max();
template <typename integer_type>
const integer_type integer_min_value = numeric_limits<integer_type>::min();


template <typename integer_type>
using RangeSumQuery = RangeTree<
                        integer_type,
                        integer_type,
                        sum<integer_type>,
                        sum<integer_type>,
                        combine_sum_sum<integer_type>,
                        integer_zero_value<integer_type>,
                        integer_zero_value<integer_type>
                      >;

template <typename integer_type>
using RangeMinQuery = RangeTree<
                        integer_type,
                        integer_type,
                        min_<integer_type>,
                        sum<integer_type>,
                        combine_sum_min_or_max<integer_type>,
                        integer_max_value<integer_type>,
                        integer_zero_value<integer_type>
                      >;

template <typename integer_type>
using RangeMaxQuery = RangeTree<
                        integer_type,
                        integer_type,
                        max_<integer_type>,
                        sum<integer_type>,
                        combine_sum_min_or_max<integer_type>,
                        integer_min_value<integer_type>,
                        integer_zero_value<integer_type>
                      >;
