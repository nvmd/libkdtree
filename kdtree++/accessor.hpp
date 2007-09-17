/** \file
 * Defines the interface for the Accessor class.
 *
 * \author Martin F. Krafft <krafft@ailab.ch>
 * \date $Date: 2004/11/26 06:02:56 $
 * \version $Revision: 1.6 $
 */

#ifndef INCLUDE_KDTREE_ACCESSOR_HPP
#define INCLUDE_KDTREE_ACCESSOR_HPP

#include <cstddef>

namespace KDTree
{
   template <typename _Val>
      struct _Bracket_accessor
      {
         typedef typename _Val::value_type result_type;

         result_type
            operator()(_Val const& V, size_t const N) const throw ()
            {
               return V[N];
            }
      };

} // namespace KDTree

#endif // include guard

/* COPYRIGHT --
 *
 * This file is part of libkdtree++, a C++ template KD-Tree sorting container.
 * libkdtree++ is (c) 2004 Martin F. Krafft <krafft@ailab.ch>
 * and distributed under the terms of the Artistic Licence.
 * See the ./COPYING file in the source tree root for more information.
 *
 * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES
 * OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
