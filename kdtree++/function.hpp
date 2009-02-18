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
   * @brief the following section defines distance calculation functors.
   *
   * The paragraph below will illustrate how a prototype distance calculator
   * looks like and what it means. Then user can use either of the 2
   * following distance calculation. By default, euclidean distance is used.
   *
   *  struct my_distance_calculator_name
   *  {
   *    typedef my_distance_type distance_type;
   *    template<typename V1, typename V2>
   *    distance_type distance(const V1& a, const V2& b, size_t dim) const;
   *    template<typename V1, typename V2>
   *    distance_type proj_distance(const V1& a, const V2& b,
   *    			    size_t dim, size_t proj_dim) const;
   *  };
   *
   *  The first declaration defines the type in which to express the distance,
   *  this type will be returned to the user when making a nearest neighbor
   *  search in the tree.
   *
   *  The second declaration define the distance between 2 element of the tree.
   *  The types V1 and V2 are a wrapper around the element type of the tree
   *  that always provides the braket accessor.
   *
   *  The third declaration is mostly similar to the second one. However the
   *  result of the computation should be the distance that is computed between
   *  the 2 elements as if they where projected on a specific dimension. The
   *  dimension for the projection is given by proj_dim.
   *
   *  A distance functor declared in such way can be used to compute orthogonal
   *  distances, manhanttan distances, euclidean distances, but also riemanean
   *  distances (i.e. for Earth surface distance calculation with lat/long
   *  systems).
   */

  /**
   *  @brief functor that calculates a manhattan distance between 2 vectors (in
   *  mathematical sense). A manhattan distance is simply the addition of all
   *  the difference in the vector.
   *
   *  The manhattan distance is a very simple distance calculation that will
   *  illustrate easily the distance calculator.
   *
   *  WARNING: In case of very large differences, the distance could overflow.
   */
  template <typename TypeDistance>
  struct manhattan_distance
  {
    typedef TypeDistance distance_type;

    template <typename V1, typename V2>
    distance_type distance(const V1& a, const V2& b, const size_t dim) const
    {
      distance_type r = 0;
      for (size_t i=0; i<dim; ++i)
	{
	  r += fabs(a[i] - b[i]);
	}
      return r;
     }

    template <typename V1, typename V2>
    distance_type proj_distance(const V1& a, const V2& b,
				const size_t dim, const size_t proj_dim) const
    {
	    return fabs(a[proj_dim] - b[proj_dim]);
    }
  }; 

  /**
   *  @brief functor that calculates a distance between 2 vectors (in
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
  template <typename TypeDistance>
  struct euclidean_distance
  {
    typedef TypeDistance distance_type;

    template <typename V1, typename V2>
    distance_type distance(const V1& a, const V2& b, const size_t dim) const
    {
      // first pass to determine max val
      double w = 0.0;
      for (size_t i=0; i<dim; ++i)
	{
	  double c = fabs(static_cast<double>(a[i]-b[i]));
	  if (c > w) { w = c; }
	}

      if (w == 0.0) { return static_cast<distance_type>(0.0); }

      // second pass to compute the distance
      double r = 0.0;
      for (size_t i=0; i<dim; ++i)
	{
	  double x = fabs(static_cast<double>(a[i]-b[i])) / w;
	  r += x * x;
	}
      return static_cast<distance_type>(w * sqrt(r));
    }

    template <typename V1, typename V2>
    distance_type proj_distance(const V1& a, const V2& b,
				const size_t dim, const size_t proj_dim) const
    {
      return static_cast<distance_type>
	(fabs(static_cast<double>(a[proj_dim] - b[proj_dim])));
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
