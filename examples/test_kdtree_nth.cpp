#define KDTREE_DEFINE_OSTREAM_OPERATORS

// Make SURE all our asserts() are checked
#undef NDEBUG

#include <kdtree++/kdtree.hpp>

#include <iostream>
#include <vector>
#include <limits>
#include <functional>
#include <set>

struct triplet
{
  typedef int value_type;

  triplet(value_type a, value_type b, value_type c)
  {
    d[0] = a;
    d[1] = b;
    d[2] = c;
  }

  triplet(const triplet & x)
  {
    d[0] = x.d[0];
    d[1] = x.d[1];
    d[2] = x.d[2];
  }

  double distance_to(triplet const& x) const
  {
     double dist = 0;
     for (int i = 0; i != 3; ++i)
        dist += (d[i]-x.d[i])*(d[i]-x.d[i]);
     return std::sqrt(dist);
  }

  inline value_type operator[](size_t const N) const { return d[N]; }

  value_type d[3];
};

inline bool operator==(triplet const& A, triplet const& B) {
  return A.d[0] == B.d[0] && A.d[1] == B.d[1] && A.d[2] == B.d[2];
}

std::ostream& operator<<(std::ostream& out, triplet const& T)
{
  return out << '(' << T.d[0] << ',' << T.d[1] << ',' << T.d[2] << ')';
}

inline double tac( triplet t, size_t k ) { return t[k]; }


typedef KDTree::KDTree<3, triplet, std::pointer_to_binary_function<triplet,size_t,double> > tree_type;



struct FindN_predicate
{
   typedef std::pair<double,triplet> Candidates;
   typedef std::vector<Candidate> Candidates;

   struct Data
   {
      Data(triplet t, size_t n) : target(t), num_wanted(n)
      {
         candidates.reserve(n);
      }

      // outputs
      // sorted vector, in order of nearest to furtherest
      // might not contain num if it did not find enough candidates
      Candidates candidates;

      // inputs
      triplet target;
      size_t num_wanted;
   };

   FindN_predicate(Data * data) : data(data), cs(&data->candidates) {}

   // note: when this returns true, libkdtree will trim the search range so that
   //       it will avoid visiting any items further away.
   // If we return false, then libkdtree will NOT trim the search space.
   //
   // So our goal is to ONLY return true when:
   //  a) we have N candidates in the list, and
   //  b) the item 't' is not closer than the second-worse candidate
   //
   // Here is a scenario...  If 't' is slightly closer or equal to the second-furtherest,
   // then it'll be added to the second-last spot in the candidate list.  The last item
   // in the candidate list will be further away than 't'.  So the last item in the list
   // could still be replaced by another item that is further than 't', AND closer than
   // the last item.  So we must allow libkdtree to visit items that are further away
   // than 't', THEREFORE we must return false and not allow libkdtree to trim the
   // search space.
   bool operator()( triplet const& t )
   {
      // check that we haven't been asked to find zero candidates
      // if so then our job is done!
      if (data->num_wanted > 0)
      {
         // what is the distance?
         double dist = data->target.distance_from(t);
         bool full = (cs->size() == data->num_wanted);

         // can it beat our Nth candidate? (if we have one)
         if (not full or dist < cs->back().first)
         {
            bool let_libktree_trim = false;

            // pop the last candidate, if we are full
            if (full)
            {
               cs->pop_back();

               // at this point, figure out what we will be returning: true or false
               // does our distance beat the second-furtherest item?
               // (which is now the last item since we just popped)
               //
               // beware of cases where we are looking for just 1 candidate
               let_libkdtree_trim = (cs->empty() or dist > cs->back().first);
            }

            // insert our new candidate in its rightful position
            cs->insert( lower_bound(cs->begin(),cs->end(),dist), Candidate(dist,t) );

            // time to return
            return let_libkdtree_trim;
         }
      }

      // if we end up here, either 't' wasn't close enough to
      // make the list, or we aren't looking for anything at all.
      // return true and allow libkdtree to trim the search space
      return true;
   }

   Data * data;
   Candidates * cs;  // shortcut for code
};




int main()
{
  tree_type tree(std::ptr_fun(tac));

  triplet c0(5, 4, 0); tree.insert(c0);
  triplet c1(4, 2, 1); tree.insert(c1);
  triplet c2(7, 6, 9); tree.insert(c2);
  triplet c3(2, 2, 1); tree.insert(c3);
  triplet c4(8, 0, 5); tree.insert(c4);
  triplet c5(5, 7, 0); tree.insert(c5);
  triplet c6(3, 3, 8); tree.insert(c6);
  triplet c7(9, 7, 3); tree.insert(c7);
  triplet c8(2, 2, 6); tree.insert(c8);
  triplet c9(2, 0, 6); tree.insert(c9);

  tree.optimise();

  std::cout << tree << std::endl;

  // time to test! TODO

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
