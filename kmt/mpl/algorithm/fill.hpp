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
#ifndef KMT_MPL_ALGORITHM_FILL_H
#define KMT_MPL_ALGORITHM_FILL_H

#include <boost/mpl/identity.hpp>

#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>

#include <boost/type_traits/conditional.hpp>

namespace kmt{ namespace mpl{


template<typename T, typename Tag>
struct fill;

#if defined BOOST_NO_VARIADIC_TEMPLATES

#ifndef KMT_MPL_FILL_LIMIT_TYPES
#	define KMT_MPL_FILL_LIMIT_TYPES 21
#endif

#define PP_TYPENAMES(n)			BOOST_PP_ENUM_PARAMS(n, typename BOOST_PP_INTERCEPT)
#define PP_TYPENAMES_ARGS(n)	BOOST_PP_ENUM_PARAMS(n, typename Arg)
#define PP_ARGS(n)				BOOST_PP_ENUM_PARAMS(n, Arg)

/*
	template<
		template<typename> class T,
		typename Arg0,
		typename Tag
	>
	struct fill< T<Arg0>, Tag >
		: boost::mpl::identity<T<Tag> >{};

	template<
		template<typename, typename> class T,
		typename Arg0, typename Arg1
		typename Tag
	>
	struct fill< T<Arg0, Arg1>, Tag >
		: boost::mpl::identity<T<Tag, Tag> >{};
*/


#ifndef PP_FILL_TEMPLAETS_CLASS
#define PP_FILL_TEMPLAETS_CLASS(z, n, text)		\
	template<										\
		template< PP_TYPENAMES(n) > class T,		\
		PP_TYPENAMES_ARGS(n),						\
		typename Tag								\
	>												\
	struct fill< T<PP_ARGS(n)>, Tag> : 				\
		boost::mpl::identity<						\
			T< BOOST_PP_ENUM_PARAMS(n, Tag BOOST_PP_INTERCEPT) >	\
		>{};
#endif

BOOST_PP_REPEAT_FROM_TO(1, KMT_MPL_FILL_LIMIT_TYPES, PP_FILL_TEMPLAETS_CLASS, _)
#undef PP_FILL_TEMPLAETS_CLASS

/*
	template<
		template<typename> class T,
		typename Tag
	>
	struct fill1 : boost::mpl::identity< T<Tag> >{};

	template<
		template<typename, typename> class T,
		typename Tag
	>
	struct fill2 : boost::mpl::identity< T<Tag, Tag> >{};
*/

#ifndef PP_FILL_N_TEMPLATES_CLASS
#define PP_FILL_N_TEMPLATES_CLASS(z, n, m)		\
	template<									\
		template < PP_TYPENAMES(n) > class T,	\
		typename Tag							\
	>											\
	struct BOOST_PP_CAT(fill, n) : 				\
		boost::mpl::identity<					\
			T< BOOST_PP_ENUM_PARAMS(n, Tag BOOST_PP_INTERCEPT) >	\
		>{};
#endif

BOOST_PP_REPEAT_FROM_TO(1, KMT_MPL_FILL_LIMIT_TYPES, PP_FILL_N_TEMPLATES_CLASS, _)
#undef PP_FILL_N_TEMPLATES_CLASS

#undef PP_TYPENAMES
#undef PP_TYPENAMES_ARGS
#undef PP_ARGS


// Variadic Templates 版
#else

template<
	template<typename...> class T,
	typename ...Args,
	typename Tag
>
struct fill<T<Args...>, Tag> :
	boost::mpl:: identity<
		T<typename boost::conditional<true, Tag, Args>::type...>
	>{};

#ifndef KMT_MPL_FILL_LIMIT_TYPES
#	define KMT_MPL_FILL_LIMIT_TYPES 21
#endif

#ifndef PP_FILL_N_TEMPLATES_CLASS
#define PP_FILL_N_TEMPLATES_CLASS(z, n, text)	\
	template<										\
		template <typename...> class T,		\
		typename Tag							\
	>												\
	struct BOOST_PP_CAT(fill, n) : 					\
		boost::mpl::identity<						\
			T< BOOST_PP_ENUM_PARAMS(n, Tag BOOST_PP_INTERCEPT) >	\
		>{};
#endif

BOOST_PP_REPEAT_FROM_TO(1, KMT_MPL_FILL_LIMIT_TYPES, PP_FILL_N_TEMPLATES_CLASS, _)
#undef PP_FILL_N_TEMPLATES_CLASS

#endif


} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_ALGORITHM_FILL_H */
