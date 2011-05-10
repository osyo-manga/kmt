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
#ifndef KMT_MPL_ALGORITHM_NONE_OF_H
#define KMT_MPL_ALGORITHM_NONE_OF_H

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/equal_to.hpp>
#include "../equal_type.hpp"

namespace kmt{ namespace mpl{

template<
	typename Seq,
	typename Pred
>
struct none_of: 
	equal_type<
		boost::mpl::find_if<Seq, Pred>,
		boost::mpl::end<Seq>
	>{};

} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_ALGORITHM_NONE_OF_H */
