//
// kmt-library
//
// Copyright (c) 2011 
// osyo-manga : http://d.hatena.ne.jp/osyo-manga/
// 
// Readme:
// https://github.com/osyo-manga/kmt/blob/master/README
//
// License:
// Boost Software License - Version 1.0
// <http://www.boost.org/LICENSE_1_0.txt>
//
#ifndef KMT_MPL_MATH_POW_H
#define KMT_MPL_MATH_POW_H

#include <boost/mpl/if.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/int.hpp>

namespace kmt{ namespace mpl{

namespace detail{

namespace mpl = boost::mpl;

template<typename base, typename exponent>
struct pow_impl : 
	mpl::if_<
		mpl::less_equal<exponent, mpl::int_<0> >,
		mpl::int_<1>,
		mpl::multiplies<pow_impl<base, mpl::minus<exponent, mpl::int_<1> > >, base>
	>::type
{};

} // namespace detail{

template<typename base, typename exponent>
struct pow : detail::pow_impl<base, exponent>{};

template<std::size_t base, std::size_t exponent>
struct pow_c : pow<
	boost::mpl::integral_c<std::size_t, base>,
	boost::mpl::integral_c<std::size_t, exponent>
>{};


} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_MATH_POW_H */
