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
#ifndef KMT_SWITCH_CASE_INCLUDE_CASE_FUSED_H
#define KMT_SWITCH_CASE_INCLUDE_CASE_FUSED_H

#include "case.hpp"
#include <boost/fusion/include/fused.hpp>

namespace kmt{ namespace switch_case{

template<typename Func>
detail::case_impl<boost::fusion::fused<Func> >
case_fused(Func const& func){
	return detail::case_impl<boost::fusion::fused<Func> >
		(boost::fusion::fused<Func>(func));
}

} } // namespace kmt{ namespace switch_case{

#endif /* KMT_SWITCH_CASE_INCLUDE_CASE_FUSED_H */
