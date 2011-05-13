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
#ifndef KMT_TYPE_TRAITH_IS_SAME_H
#define KMT_TYPE_TRAITH_IS_SAME_H

#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>

namespace kmt{

#ifndef KMT_IS_SAME_LIMIT_TYPES
#	define KMT_IS_SAME_LIMIT_TYPES 21
#endif

struct _{};

namespace detail{

template<typename T, typename U>
struct is_same_impl : boost::mpl::false_{};

template<typename T>
struct is_same_impl<T, T> : boost::mpl::true_{};

template<typename T>
struct is_same_impl<T, _> : boost::mpl::true_{};

template<typename T>
struct is_same_impl<_, T> : boost::mpl::true_{};

template<>
struct is_same_impl<_, _> : boost::mpl::true_{};

}  // namespace detail{


template<
	typename T, typename U,
	typename Pred = detail::is_same_impl<boost::mpl::_1, boost::mpl::_2>
>
struct is_same : boost::mpl::apply<Pred, T, U>::type{};

template<
	template <typename> class TT,
	typename TArg0, typename UArg0,
	typename Pred
>
struct is_same<TT<TArg0>, TT<UArg0>, Pred>
	: is_same<TArg0, UArg0, Pred>::type{};


/*
	template<
		template <typename, typename> class TT,
		typename TArg0, typename TArg1,
		typename UArg0, typename UArg1,
		typename Pred
	>
	struct is_same<
			TT<TArg0, TArg1>,
			TT<UArg0, UArg1>,
			Pred
		> :
		boost::mpl::bool_<
			   is_same<TArg0, UArg0, Pred>::value,
			&& is_same<TArg1, UArg1, Pred>::value
		>{};

	template<
		template <typename, typename, typename> class TT,
		typename TArg0, typename TArg1, typename TArg2,
		typename UArg0, typename UArg1, typename UArg2,
		typename Pred
	>
	struct is_same<
			TT<TArg1, TArg2, TArg3>,
			TT<UArg1, UArg2, UArg3>,
			Pred
		> :
		boost::mpl::and_<
			   is_same<TArg0, UArg0, Pred>::value,
			&& is_same<TArg1, UArg1, Pred>::value,
			&& is_same<TArg2, UArg2, Pred>::value
	>{};
*/

#define PP_AND_IS_SAME(z, n, text)	\
	&& is_same<						\
		BOOST_PP_CAT(TArg, n), 		\
		BOOST_PP_CAT(UArg, n),		\
		Pred						\
	>::value

#define PP_IS_SAME_CLASS(z, n, text)			\
template<										\
	template < BOOST_PP_ENUM_PARAMS(n, typename BOOST_PP_INTERCEPT) >	\
		class TT,		\
	BOOST_PP_ENUM_PARAMS(n, typename TArg),		\
	BOOST_PP_ENUM_PARAMS(n, typename UArg),		\
	typename Pred								\
>												\
struct is_same<									\
		TT< BOOST_PP_ENUM_PARAMS(n, TArg) >,	\
		TT< BOOST_PP_ENUM_PARAMS(n, UArg) >,	\
		Pred									\
	> :											\
	boost::mpl::bool_<							\
		is_same<TArg0, UArg0, Pred>::value		\
		BOOST_PP_REPEAT(BOOST_PP_SUB(n, 1), PP_AND_IS_SAME, _)	\
	>{};

BOOST_PP_REPEAT_FROM_TO(2, KMT_IS_SAME_LIMIT_TYPES, PP_IS_SAME_CLASS, _)

#undef PP_AND_IS_SAME
#undef PP_IS_SAME_CLASS


} // namespace kmt

#endif /* KMT_TYPE_TRAITH_IS_SAME_H */
