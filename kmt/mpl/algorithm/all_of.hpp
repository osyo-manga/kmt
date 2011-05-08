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
#ifndef KMT_MPL_ALGORITHM_ALL_OF_H
#define KMT_MPL_ALGORITHM_ALL_OF_H

#include "all_of_if.hpp"
#include <boost/type_traits/is_same.hpp>

namespace kmt{ namespace mpl{

template<
	typename Seq,
	typename T
>
struct all_of : all_of_if<Seq, boost::is_same<boost::mpl::_, T> >{};

} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_ALGORITHM_ALL_OF_H */
