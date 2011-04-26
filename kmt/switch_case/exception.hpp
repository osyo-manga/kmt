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
#ifndef KMT_SWITCH_CASE_EXCEPTION_H
#define KMT_SWITCH_CASE_EXCEPTION_H

#include <exception>

namespace kmt{ namespace switch_case {

struct no_match : std::exception{
	no_match(char const* error) : std::exception(error){}
};

} } // namespace kmt{ namespace switch_case {

#endif /* KMT_SWITCH_CASE_EXCEPTION_H */
