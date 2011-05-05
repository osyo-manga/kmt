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
#ifndef KMT_VARIANT_IS_VARIANT_H
#define KMT_VARIANT_IS_VARIANT_H

#include <boost/variant/variant.hpp>
#include <boost/mpl/bool.hpp>

namespace kmt{

template<typename T>
struct is_variant : boost::mpl::false_{};

template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct is_variant<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
	: boost::mpl::true_{};

} // namespace kmt

#endif /* KMT_VARIANT_IS_VARIANT_H */
