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
#ifndef KMT_MPL_TEMPLATE_SEQUENCE_H
#define KMT_MPL_TEMPLATE_SEQUENCE_H

#include <boost/mpl/apply.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/copy.hpp>

#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/enum_params.hpp>

namespace kmt{ namespace mpl{

namespace detail{

/*
template<
	template<typename> class T,
	typename Arg1,
	typename Seq, typename Inserter
>
struct template_sequence_impl<T<Arg1>, Seq, Inserter> :
	mpl::copy<Seq,
		typename mpl::apply1<Inserter, mpl::vector<Arg1> >::type
	>::type
{};

template<
	template<typename, typename> class T,
	typename Arg1, typename Arg2,
	typename Seq, typename Inserter
>
struct template_sequence_impl<T<Arg1, Arg2>, Seq, Inserter> :
	mpl::copy<Seq,
		typename mpl::apply1<Inserter, mpl::vector<Arg1, Arg2> >::type
	>::type
{};
*/

#ifndef KMT_MPL_TEMPLATE_SEQUENCE_LIMIT_TYPES
#	define KMT_MPL_TEMPLATE_SEQUENCE_LIMIT_TYPES 11
#endif

template<typename T, typename Seq, typename Inserter>
struct template_sequence_impl : Seq{};

#define KMT_PP_TYPENAMES(n)			BOOST_PP_ENUM_PARAMS(n, typename BOOST_PP_INTERCEPT)
#define KMT_PP_TYPENAMES_ARGS(n)	BOOST_PP_ENUM_PARAMS(n, typename Arg)
#define KMT_PP_ARGS(n)				BOOST_PP_ENUM_PARAMS(n, Arg)

#ifndef KMT_PP_TEMPLAET_SEQUENCE_CLASS
#define KMT_PP_TEMPLAET_SEQUENCE_CLASS(z, n, text)	\
	template<										\
		template< KMT_PP_TYPENAMES(n) > class T,	\
		KMT_PP_TYPENAMES_ARGS(n),					\
		typename Seq, typename Inserter				\
	>												\
	struct template_sequence_impl< T< KMT_PP_ARGS(n) >, Seq, Inserter> :	\
	boost::mpl::copy<Seq,													\
		typename boost::mpl::apply1<Inserter, 								\
			 boost::mpl::vector< KMT_PP_ARGS(n) >						\
		>::type																\
	>::type																	\
	{};
#endif

BOOST_PP_REPEAT_FROM_TO(1, KMT_MPL_TEMPLATE_SEQUENCE_LIMIT_TYPES, KMT_PP_TEMPLAET_SEQUENCE_CLASS, _)

#undef KMT_PP_TEMPLAET_SEQUENCE_CLASS
#undef KMT_PP_TYPENAMES
#undef KMT_PP_TYPENAMES_ARGS
#undef KMT_PP_ARGS

}  // namespace detial{

template<typename T, typename Seq,
	typename Inserter = boost::mpl::back_inserter<boost::mpl::_1>
>
struct template_sequence : detail::template_sequence_impl<T, Seq, Inserter>{};

} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_TEMPLATE_SEQUENCE_H */
