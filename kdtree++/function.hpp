/** \file
 * Defines the various functors and interfaces used for KDTree.
 *
 * \author Martin F. Krafft <libkdtree@pobox.madduck.net>
 * \author Sylvain Bougerel <sylvain.bougerel.devel@gmail.com>
 */

#ifndef INCLUDE_KDTREE_ACCESSOR_HPP
#define INCLUDE_KDTREE_ACCESSOR_HPP

#include <cstddef>
#include <cmath>

namespace KDTree
{
  template <typename _Val>
  struct _Bracket_accessor
  {
    typedef typename _Val::value_type result_type;

    result_type
    operator()(_Val const& V, size_t const N) const
    {
      return V[N];
    }
  };

  template <typename _Tp>
  struct always_true
  {
    bool operator() (const _Tp& ) const { return true; }
  };

  /**
   *  @brief functor that calculates a distance between 2 vector (in
   *  mathematical sense) using an euclidean metric in a way that avoids
   *  overflow.
   *
   *  The function works using double in the backend, so TypeDistance must be
   *  castable into a double and vice-versa.
   *
   *  The template types V1 and V2 are used by the tree to pass 2 vectors for
   *  which the operator[] is defined. This operator can be uses to get the
   *  vector's element for a particular dimension.
   */
  typename <typename TypeDistance>
  struct euclidean_distance
  {
    typedef TypeDistance distance_type;

    typename <typename V1, typename V2>
    distance_type distance(const V1& a, const V2& b, size_t d)
    {
      // first pass to determine max val
      double w = 0.0;
      for (size_t i=0; i<d; ++i)
	{
	  double c = fabs(static_cast<double>(a[i]-b[i]));
	  if (c > w) { w = c }
	}

      if (w == 0.0) { return static_cast<distance_type>(0.0); }

      // second pass to compute the distance
      double r = 0.0;
      for (size_t i=0; i<d; ++i)
	{
	  double x = fabs(static_cast<double>(a[i]-b[i])) / w;
	  r += x * x;
	}
      return static_cast<distance_type>(w * sqrt(r));
    }
  };

} // namespace KDTree

#endif // include guard

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
