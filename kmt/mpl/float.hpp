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
#ifndef KMT_MPL_FLOAT_H
#define KMT_MPL_FLOAT_H

#include <kmt/mpl/math/pow.hpp>
#include <boost/ratio/ratio.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/plus.hpp>

namespace kmt{ namespace mpl{

namespace detail{

namespace mpl = boost::mpl;

template<typename T>
struct keta_impl :
	mpl::if_<
		mpl::less_equal<T, mpl::int_<0> >,
		mpl::int_<0>,
		mpl::plus<keta_impl<mpl::divides<T, mpl::int_<10> > >, mpl::int_<1> >
	>::type
{};

template<typename T>
struct keta : detail::keta_impl<T>{};

template<std::size_t N, std::size_t M,
	typename keta = pow<boost::mpl::int_<10>, 
		detail::keta<boost::mpl::integral_c<std::size_t, M> > > >
struct float_impl : 
	boost::ratio<
		N * keta::value + M,
		keta::value
	>
{};

}  // namespace detail

template<std::size_t N, std::size_t M>
struct float_ : detail::float_impl<N, M>{};

} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_FLOAT_H */
