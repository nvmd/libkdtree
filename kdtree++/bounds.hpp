/** \file
 * Defines the interface of the Bounds_T<> class.
 *
 * \author Paul Harris <paulharris@computer.org>
 */

#ifndef INCLUDE_KDTREE_BOUNDS_HPP
#define INCLUDE_KDTREE_BOUNDS_HPP

#include <cstddef>

#include "node.hpp"

namespace KDTree
{

   template <size_t const K, typename SubVal>
   struct Bounds_T
   {
      typedef SubVal subvalue_type;

      void set_low_bound(subvalue_type val, size_t const level)
      {
         assert(level < K);
         low_bounds[level] = val;
      }

      void set_high_bound(subvalue_type val, size_t const level)
      {
         assert(level < K);
         high_bounds[level] = val;
      }

      subvalue_type low_bounds[K], high_bounds[K];
   };

} // namespace KDTree

#endif // include guard

/* COPYRIGHT --
 *
 * This file is part of libkdtree++, a C++ template KD-Tree sorting container.
 * libkdtree++ is (c) 2004-2007 Martin F. Krafft <libkdtree@pobox.madduck.net>
 * and Sylvain Bougerel <sylvain.bougerel.devel@gmail.com> 
 * and Paul Harris <paulharris@computer.org>
 * distributed under the terms of the Artistic License 2.0. 
 * See the ./COPYING file in the source tree root for more information.
 *
 * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES
 * OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
