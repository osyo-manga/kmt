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
#ifndef KMT_SWITCH_CASE_INCLUDE_CASE_TYPE_H
#define KMT_SWITCH_CASE_INCLUDE_CASE_TYPE_H

#include "case.hpp"

namespace kmt{ namespace switch_case{

namespace detail{

template<typename T>
struct equal_type{
	template<typename U>
	bool operator ()(U const&) const{
		return boost::is_same<T, U>();
	}
};

} // namespace detail

template<typename T>
detail::case_impl<detail::equal_type<T> >
case_type(){
	return case_pred(detail::equal_type<T>());
}

} } // namespace kmt{ namespace switch_case{

#endif /* KMT_SWITCH_CASE_INCLUDE_CASE_TYPE_H */
