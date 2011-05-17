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
#ifndef KMT_MPL_EQUAL_TYPE_H
#define KMT_MPL_EQUAL_TYPE_H

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include "../type_traits/detail/has_type.hpp"

namespace kmt{ namespace mpl{

namespace detail{

template<typename T>
struct extract :
	boost::mpl::eval_if<kmt::detail::has_type<T>, T, boost::mpl::identity<T> >{};

}  // namespace detail{

template<typename T, typename U>
struct equal_type
	: boost::is_same<
		typename detail::extract<T>::type,
		typename detail::extract<U>::type
	>{};


} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_EQUAL_TYPE_H */
