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
#ifndef _KMT_MPL_VARIADIC_VECTOR_H_
#define _KMT_MPL_VARIADIC_VECTOR_H_

#include <boost/config.hpp>

#if !defined BOOST_NO_VARIADIC_TEMPLATES


#include "variadic_sequence.hpp"

namespace kmt{ namespace mpl{

template<typename ...Args>
struct variadic_vector :
	variadic_sequence<
		boost::mpl::vector1<boost::mpl::_1>,
		boost::mpl::push_front<boost::mpl::_1, boost::mpl::_2>,
		Args...
	>
{};

} } // namespace kmt{  namespace mpl{


#else

#include <boost/static_assert.hpp>
BOOST_STATIC_ASSERT(false && "No Supported Variadic Templates");

#endif


#endif /* _KMT_MPL_VARIADIC_VECTOR_H_ */
