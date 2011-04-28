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
#ifndef KMT_SWITCH_CASE_INCLUDE_DEFAULT_H
#define KMT_SWITCH_CASE_INCLUDE_DEFAULT_H

namespace kmt{ namespace switch_case{

namespace detail{

// "*" の代わり
struct true_{}_;
template<typename T>
bool operator ==(const true_&, const T&){
	return true;
}

static const detail::case_impl<equal_value<detail::true_> > default_(_);

}  // namespace detail

using detail::_;
using detail::default_;

} } // namespace kmt{ namespace switch_case{

#endif /* KMT_SWITCH_CASE_INCLUDE_DEFAULT_H */
