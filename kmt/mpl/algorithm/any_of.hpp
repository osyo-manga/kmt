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
#ifndef KMT_MPL_ALGORITHM_ANY_OF_H
#define KMT_MPL_ALGORITHM_ANY_OF_H

#include <boost/mpl/count_if.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/or.hpp>

namespace kmt{ namespace mpl{

template<
	typename Seq,
	typename Pred
>
struct any_of :
	boost::mpl::or_<
		boost::mpl::empty<Seq>,
		boost::mpl::less_equal<
			boost::mpl::int_<1>,
			boost::mpl::count_if<Seq, Pred>
		>
	>{};

} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_ALGORITHM_ANY_OF_H */
