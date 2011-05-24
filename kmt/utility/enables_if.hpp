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
#ifndef KMT_UTILITY_ENABLES_IF_H
#define KMT_UTILITY_ENABLES_IF_H

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/count_if.hpp>

namespace kmt{

namespace detail{

namespace mpl = boost::mpl;

template<typename Seq, typename N, typename M>
struct slice :
	mpl::iterator_range<
		typename mpl::advance<typename mpl::begin<Seq>::type, N>::type,
		typename mpl::advance<typename mpl::begin<Seq>::type, M>::type
	>
{};

template<typename Seq, typename Pred>
struct one_of :
	mpl::equal_to<
		mpl::count_if<Seq, Pred>,
		mpl::int_<1>
	>
{};

using mpl::_1;

template<typename Seq, typename T>
struct apply :
	mpl::transform<Seq, mpl::apply1<_1, T> >{};

template<typename Seq, typename N, typename U>
struct enables_if_c_impl :
	boost::enable_if<
		// seq[N] && (count(seq[0, N+1], true) == 1)
		mpl::and_<
			mpl::at<Seq, N>,
			one_of<
				slice<
					Seq,
					mpl::int_<0>,
					mpl::plus<N, mpl::int_<1> >
				>,
				mpl::equal_to<mpl::_1, mpl::true_>
			>
		>,
		U
	>
{};

template<typename Seq, typename N, typename T, typename U>
struct enables_if_impl :
	enables_if_c_impl<typename apply<Seq, T>::type, N, U>{};

}  // namespace detail

template<typename Seq, typename N, typename T, typename U = void>
struct enables_if : detail::enables_if_impl<Seq, N, T, U>{};

template<typename Seq, typename N, typename U = void>
struct enables_if_c : detail::enables_if_c_impl<Seq, N, U>{};

} // namespace kmt

#endif /* KMT_UTILITY_ENABLES_IF_H */
