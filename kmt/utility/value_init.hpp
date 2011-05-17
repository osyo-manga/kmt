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
#ifndef KMT_UTILITY_VALUE_INIT_H
#define KMT_UTILITY_VALUE_INIT_H

#include <boost/utility/value_init.hpp>
#include <boost/utility/enable_if.hpp>
#include "../type_traits/detail/has_value_type.hpp"

namespace kmt{

namespace detail{

namespace mpl = boost::mpl;

struct initializer_empty{};

template<typename T, typename Initializer, typename sfinae = void>
struct initialized_impl : boost::initialized<T>{
	typedef boost::initialized<T> base_type;
	initialized_impl() : base_type(){}
	explicit initialized_impl(T const& arg) : base_type(arg){}
};


// Initializer が initializer_empty 以外の場合
template<typename T, typename Initializer>
struct initialized_impl<T, Initializer, 
	typename boost::disable_if<
		boost::is_same<initializer_empty, Initializer> >::type
	>
	: boost::initialized<T>{
	typedef boost::initialized<T> base_type;
	initialized_impl() : 
		base_type(static_cast<T>(Initializer())){}
	explicit initialized_impl(T const& arg) : base_type(arg){}
};


// T::value_type があり、Initializer が initializer_empty の場合
template<typename T>
struct initialized_impl<T, void, typename boost::enable_if<has_value_type<T> >::type >
	: boost::initialized<typename T::value_type>{
	typedef boost::initialized<typename T::value_type> base_type;
	initialized_impl() : 
		base_type(static_cast<typename T::value_type>(T())){}
	explicit initialized_impl(T const& arg) : base_type(arg){}
};

}  // namespace detail


template<typename T, typename Initializer = detail::initializer_empty>
struct initialized : detail::initialized_impl<T, Initializer>{
	typedef detail::initialized_impl<T, Initializer> base_type;
	initialized() : base_type(){}
	explicit initialized(T const& arg) : base_type(arg){}
};


} // namespace kmt

#endif /* KMT_UTILITY_VALUE_INIT_H */
