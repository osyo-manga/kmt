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
#ifndef KMT_MPL_SLICE_H
#define KMT_MPL_SLICE_H

#include <boost/mpl/vector.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/advance.hpp>


namespace kmt{ namespace mpl{

template<typename Seq, typename N, typename M>
struct slice :
	boost::mpl::iterator_range<
		typename boost::mpl::advance<typename boost::mpl::begin<Seq>::type, N>::type,
		typename boost::mpl::advance<typename boost::mpl::begin<Seq>::type, M>::type
	>
{};

template<typename Seq, int N, int M>
struct slice_c : slice<Seq, boost::mpl::int_<N>, boost::mpl::int_<M> >{};

} } // namespace kmt { namespace mpl{

#endif /* KMT_MPL_SLICE_H */
