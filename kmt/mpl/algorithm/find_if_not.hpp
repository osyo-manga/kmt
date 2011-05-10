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
#ifndef KMT_ALGORITHM_FIND_IF_NOT_H
#define KMT_ALGORITHM_FIND_IF_NOT_H

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/not.hpp>

namespace kmt{ namespace mpl{

template<
	typename Seq,
	typename Pred
>
struct find_if_not : boost::mpl::find_if<Seq, boost::mpl::not_<Pred> >{};

} } // namespace kmt{ namespace mpl{

#endif /* KMT_ALGORITHM_FIND_IF_NOT_H */
