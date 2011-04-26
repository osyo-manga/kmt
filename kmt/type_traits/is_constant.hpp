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
#ifndef KMT_TYPE_TRAITS_IS_CONSTANT_H
#define KMT_TYPE_TRAITS_IS_CONSTANT_H

#include <boost/type_traits/integral_constant.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/enable_if.hpp>

namespace kmt{

namespace detail{

typedef struct{ char a[2]; } yes_type;
typedef struct{ char a[1]; } no_type;

template<int N>
yes_type
is_constant_check();

template<typename T>
no_type
is_constant_check();

template<typename T, int N = T::value>
struct is_constant_sfinae_helper{
	typedef void type;
};

} // namespace detail{

#define KMT_IS_CONSTANT(src_) \
	boost::mpl::bool_<        \
		sizeof(kmt::detail::is_constant_check<src_>()) == sizeof(kmt::detail::yes_type) \
	>

template<typename T, typename U = void>
struct is_constant_value : boost::mpl::false_{};

template<typename T>
struct is_constant_value<
	T,
	typename detail::is_constant_sfinae_helper<T>::type
> : boost::mpl::true_{};

template<typename T, typename U = void>
struct element_value : boost::mpl::identity<typename T::value>{};

template<typename T>
struct element_value<
	T,
	typename boost::enable_if<is_constant_value<T> >::type
> : boost::integral_constant<int, T::value>{};


} // namespace kmt

#endif /* TYPE_TRAITS_IS_CONSTANT */
