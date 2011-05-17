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
#ifndef KMT_MPL_FOR_EACH_WITH_INDEX_H
#define KMT_MPL_FOR_EACH_WITH_INDEX_H

#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/zip_view.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/unpack_args.hpp>

namespace kmt{ namespace mpl{

namespace detail{
template<typename T, typename Index>
struct with_index_impl{
	typedef T type;
	typedef Index index;
};

}  // namespace detail

template<typename T, typename Index>
struct with_index
	: boost::mpl::identity<detail::with_index_impl<T, Index> >{};

template<
	typename Sequence,
	typename TransformOp,
	typename F
>
void for_each_with_index(F f, Sequence* =0, TransformOp* =0){
	namespace mpl = boost::mpl;
	mpl::for_each<
		mpl::transform_view<
			mpl::zip_view<
				mpl::vector<
					Sequence,
					mpl::range_c<int, 0, mpl::size<Sequence>::value>
				>
			>,
			mpl::unpack_args<with_index<mpl::_1, mpl::_2> >
		>,
		TransformOp
	>(f);
}

template<
	typename Sequence,
	typename F
>
void for_each_with_index(F f, Sequence* =0){
	for_each_with_index<Sequence, boost::mpl::identity<> >(f);
}

} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_FOR_EACH_WITH_INDEX_H */
