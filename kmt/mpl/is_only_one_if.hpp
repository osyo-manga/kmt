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

#ifndef KMT_MPL_IS_ONLY_ONE_IF_H
#define KMT_MPL_IS_ONLY_ONE_IF_H

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/int.hpp>

namespace kmt{ namespace mpl{

template<typename Seq, typename Pred>
struct is_only_one_if :
	boost::mpl::equal_to<
		boost::mpl::count_if<Seq, Pred>,
		boost::mpl::int_<1>
	>
{};

} } // namespace kmt { namespace mpl{

#endif /* KMT_MPL_IS_ONLY_ONE_IF_H */
