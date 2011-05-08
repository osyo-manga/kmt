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

#include <boost/mpl/count_if.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/equal_to.hpp>

namespace kmt{ namespace mpl{

template<
	typename Seq,
	typename Pred
>
struct all_of
	: boost::mpl::equal_to<
		boost::mpl::count_if<Seq, Pred>,
		boost::mpl::size<Seq>
	>{};

} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_ALGORITHM_ALL_OF_H */
