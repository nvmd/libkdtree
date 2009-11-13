/** \file
 * Defines the interface of the _Region class.
 *
 * \author Martin F. Krafft <libkdtree@pobox.madduck.net>
 */

#ifndef INCLUDE_KDTREE_REGION_HPP
#define INCLUDE_KDTREE_REGION_HPP

#include <cstddef>

#include "bounds.hpp"

namespace KDTree
{

  template <size_t const __K, typename _Val, typename _SubVal,
            typename _Acc, typename _Cmp>
    struct _Region
    {
       typedef Bounds_T<__K,_SubVal> Bounds;
      typedef _Val value_type;
      typedef _SubVal subvalue_type;

      // special typedef for checking against a fuzzy point (for find_nearest)
      // Note the region (first) component is not supposed to have an area, its
      // bounds should all be set to a specific point.
      typedef std::pair<Bounds,_SubVal> _CenterPt;

      _Region(_Acc const& __acc, const _Cmp& __cmp=_Cmp())
	: _M_acc(__acc), _M_cmp(__cmp) {}

      template <typename Val>
      _Region(Val const& __V,
	      _Acc const& __acc, const _Cmp& __cmp=_Cmp())
	: _M_acc(__acc), _M_cmp(__cmp)
      {
        for (size_t __i = 0; __i != __K; ++__i)
          {
             bounds.low_bounds[__i] = bounds.high_bounds[__i] = _M_acc(__V,__i);
          }
      }

      template <typename Val>
      _Region(Val const& __V, subvalue_type const& __R,
	      _Acc const& __acc, const _Cmp& __cmp=_Cmp())
	: _M_acc(__acc), _M_cmp(__cmp)
      {
        for (size_t __i = 0; __i != __K; ++__i)
          {
             bounds.set_low_bound( _M_acc(__V,__i) - __R, __i);
             bounds.set_high_bound( _M_acc(__V,__i) + __R, __i);
          }
      }

      Bounds const& get_bounds() const
      {
         return bounds;
      }

      bool
      intersects_with(_CenterPt const& __THAT) const
      {
        for (size_t __i = 0; __i != __K; ++__i)
          {
             // does it fall outside the bounds? 
             // ! low-tolerance <= x <= high+tolerance
             // ! (low-tol <= x and x <= high+tol)
             // !low-tol<=x or !x<=high+tol
             // low-tol>x or x>high+tol
             // x<low-tol or high+tol<x
            if (_M_cmp(__THAT.first.low_bounds[__i], bounds.low_bounds[__i] - __THAT.second)
             || _M_cmp(bounds.high_bounds[__i] + __THAT.second, __THAT.first.low_bounds[__i]))
              return false;
          }
        return true;
      }

      bool
      intersects_with(Bounds const& __THAT) const
      {
        for (size_t __i = 0; __i != __K; ++__i)
          {
            if (_M_cmp(__THAT.high_bounds[__i], bounds.low_bounds[__i])
             || _M_cmp(bounds.high_bounds[__i], __THAT.low_bounds[__i]))
              return false;
          }
        return true;
      }

      bool
      encloses(value_type const& __V) const
      {
        for (size_t __i = 0; __i != __K; ++__i)
          {
            if (_M_cmp(_M_acc(__V, __i), bounds.low_bounds[__i])
             || _M_cmp(bounds.high_bounds[__i], _M_acc(__V, __i)))
              return false;
          }
        return true;
      }

      Bounds bounds;
      _Acc _M_acc;
      _Cmp _M_cmp;
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
