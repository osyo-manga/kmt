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
#ifndef KMT_SWITCH_CASE_INCLUDE_CASE_VARIANT_H
#define KMT_SWITCH_CASE_INCLUDE_CASE_VARIANT_H

#include <boost/variant/get.hpp>
#include <boost/variant/variant.hpp>
#include <boost/utility/enable_if.hpp>

#include "../../type_traits/is_same.hpp"
#include "../../mpl/algorithm/fill.hpp"
#include "case.hpp"

namespace kmt{ namespace switch_case{

namespace detail{

template<typename T>
struct equal_variant_type{
	
	template<typename U>
	struct is_variant
		: is_same<typename kmt::mpl::fill<boost::variant<>, kmt::_>::type, U>{};
	
	template<typename U>
	typename boost::enable_if<
		is_variant<U>,
		bool
	>::type
	operator ()(U const& u) const{
		return boost::get<T>(&u) ? true : false;
	}
	
	// Boost.Variant だった場合は false を返す
	template<typename U>
	typename boost::disable_if<
		is_variant<U>,
		bool
	>::type
	operator ()(U const& u) const{
		return false;
	}
};

}  // namespace detail

template<typename T>
detail::case_impl<detail::equal_variant_type<T> >
case_variant(){
	return case_pred(detail::equal_variant_type<T>());
}

} } // namespace kmt{ namespace switch_case{

#endif /* KMT_SWITCH_CASE_INCLUDE_CASE_VARIANT_H */
