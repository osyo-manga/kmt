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
#ifndef KMT_MPL_ALGORITHM_ALL_OF_IF_H
#define KMT_MPL_ALGORITHM_ALL_OF_IF_H

#include <boost/mpl/count_if.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/equal_to.hpp>

namespace kmt{ namespace mpl{

namespace detail{

namespace mpl = boost::mpl;

template<
	typename Seq,
	typename Pred
>
struct all_of_if_impl
	: mpl::equal_to<
		mpl::count_if<Seq, Pred>,
		mpl::size<Seq>
	>{};

}  // namespace detail

template<
	typename Seq,
	typename Pred
>
struct all_of_if : detail::all_of_if_impl<Seq, Pred>{};

} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_ALGORITHM_ALL_OF_IF_H */
