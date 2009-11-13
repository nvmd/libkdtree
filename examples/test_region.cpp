#define KDTREE_DEFINE_OSTREAM_OPERATORS

// Make SURE all our asserts() are checked
#undef NDEBUG

#include <kdtree++/kdtree.hpp>

#include <deque>
#include <iostream>
#include <vector>
#include <limits>
#include <functional>
#include <set>

// used to ensure all triplets that are accessed via the operator<< are initialised.
std::set<const void*> registered;

struct triplet
{
  typedef int value_type;

  triplet(value_type a, value_type b, value_type c)
  {
    d[0] = a;
    d[1] = b;
    d[2] = c;
    bool reg_ok = (registered.find(this) == registered.end());
    assert(reg_ok);
    registered.insert(this).second;
  }

  triplet(const triplet & x)
  {
    d[0] = x.d[0];
    d[1] = x.d[1];
    d[2] = x.d[2];
    bool reg_ok = (registered.find(this) == registered.end());
    assert(reg_ok);
    registered.insert(this).second;
  }

  ~triplet()
  {
    bool unreg_ok = (registered.find(this) != registered.end());
    assert(unreg_ok);
    registered.erase(this);
  }

  double distance_to(triplet const& x) const
  {
     double dist = 0;
     for (int i = 0; i != 3; ++i)
        dist += (d[i]-x.d[i])*(d[i]-x.d[i]);
     return sqrt(dist);
  }

  inline value_type operator[](size_t const N) const { return d[N]; }

  value_type d[3];
};



inline bool operator==(triplet const& A, triplet const& B) {
  return A.d[0] == B.d[0] && A.d[1] == B.d[1] && A.d[2] == B.d[2];
}

std::ostream& operator<<(std::ostream& out, triplet const& T)
{
  assert(registered.find(&T) != registered.end());
  return out << '(' << T.d[0] << ',' << T.d[1] << ',' << T.d[2] << ')';
}

inline double tac( triplet t, size_t k ) { return t[k]; }


struct MyRegion
{
   typedef KDTree::Bounds_T<3,double> Bounds;

   MyRegion()
   {
      bounds.set_low_bound(0,0);
      bounds.set_low_bound(0,1);
      bounds.set_low_bound(0,2);
      bounds.set_high_bound(4,0);
      bounds.set_high_bound(4,1);
      bounds.set_high_bound(8,2);
   }

   Bounds const& get_bounds() const
   {
      return bounds;
   }

   bool encloses( triplet const& x ) const
   {
      for (int i = 0; i != 3; ++i)
         if (x[i] < bounds.low_bounds[i] || x[i] > bounds.high_bounds[i])
            return false;
      return true;
   }

   bool intersects_with( Bounds const& b ) const
   {
      for (int i = 0; i != 3; ++i)
      {
         if (b.high_bounds[i] < bounds.low_bounds[i]
               || bounds.high_bounds[i] < b.low_bounds[i])
            return false;
      }
      return true;
   }

   Bounds bounds;
};



typedef KDTree::KDTree<3, triplet, std::pointer_to_binary_function<triplet,size_t,double> > tree_type;



struct Visitor
{
   void operator()( triplet const& x ) const
   {
      std::cout << "Visited: " << x << std::endl;
   }
};


int main()
{
  tree_type src(std::ptr_fun(tac));

  triplet c0(5, 4, 0); src.insert(c0);
  triplet c1(4, 2, 1); src.insert(c1);
  triplet c2(7, 6, 9); src.insert(c2);
  triplet c3(2, 2, 1); src.insert(c3);
  triplet c4(8, 0, 5); src.insert(c4);
  triplet c5(5, 7, 0); src.insert(c5);
  triplet c6(3, 3, 8); src.insert(c6);
  triplet c7(9, 7, 3); src.insert(c7);
  triplet c8(2, 2, 6); src.insert(c8);
  triplet c9(2, 0, 6); src.insert(c9);

  std::cout << src << std::endl;

  src.optimise();

   MyRegion region;
   Visitor visitor;
   src.visit_within_range(region,visitor);

  return 0;
}

/* COPYRIGHT --
 *
 * This file is part of libkdtree++, a C++ template KD-Tree sorting container.
 * libkdtree++ is (c) 2004-2007 Martin F. Krafft <libkdtree@pobox.madduck.net>
 * and Sylvain Bougerel <sylvain.bougerel.devel@gmail.com> distributed under the
 * terms of the Artistic License 2.0. See the ./COPYING file in the source tree
 * root for more information.
 *
 * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES
 * OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
