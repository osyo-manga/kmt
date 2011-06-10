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
#ifndef KMT_MPL_C_ARRAY_H
#define KMT_MPL_C_ARRAY_H

#include <boost/mpl/size.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/at.hpp>
#include <boost/array.hpp>

#include <kmt/utility/value_init.hpp>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>


#ifndef KMT_MPL_C_ARRAY_LIMIT_SIZE
#    define KMT_MPL_C_ARRAY_LIMIT_SIZE 100
#endif


#if defined BOOST_NO_INITIALIZER_LISTS
	// initializer_list が実装されていない場合は、Boost.Assign を使用して、初期化を行う
	#include <boost/assign.hpp>
	#define PP_C_ARRAY_AC_C(z, n, text) \
		(boost::mpl::at_c<Seq, n>::type::value)
	
	#define PP_C_ARRYA_AC_C_INITIALIZER(n)	\
		boost::assign::list_of BOOST_PP_REPEAT_FROM_TO(0, n, PP_C_ARRAY_AC_C, _)
#else
	// initializer_list が実装されている場合は、initializer_list を使用する
	#define PP_C_ARRAY_AC_C(z, n, text) \
		boost::mpl::at_c<Seq, n>::type::value
	
	#define PP_C_ARRYA_AC_C_INITIALIZER(n)	\
		{ { BOOST_PP_ENUM(n, PP_C_ARRAY_AC_C, _)  } }
#endif


namespace kmt{ namespace mpl{


namespace detail{

template<typename T, typename Size>
struct array_type
	: boost::mpl::identity<boost::array<T, Size::value> >{};

template<
	typename Seq, long Size,
	typename ArrayType
>
struct c_array_impl;

#define PP_C_ARRAY(z, n, text)                              \
template<                                                   \
	typename Seq,                                           \
	typename ArrayType                                      \
>                                                           \
struct c_array_impl<Seq, n, ArrayType>{                     \
	typedef c_array_impl<Seq, n, ArrayType> type;           \
	                                                        \
	typedef typename boost::mpl::apply<                     \
		ArrayType,                                          \
		typename Seq::value_type, boost::mpl::size<Seq>     \
	>::type value_type;                                     \
	                                                        \
	static value_type const value;                          \
	                                                        \
	operator value_type const&() const{                     \
		return value;                                       \
	}                                                       \
};                                                          \
                                                            \
template<typename Seq, typename ArrayType>                  \
typename c_array_impl<Seq, n, ArrayType>::value_type const  \
c_array_impl<Seq, n, ArrayType>::value = PP_C_ARRYA_AC_C_INITIALIZER(n);


BOOST_PP_REPEAT_FROM_TO(1, KMT_MPL_C_ARRAY_LIMIT_SIZE, PP_C_ARRAY, _)

#undef PP_C_ARRAY
#undef PP_C_ARRAY_AC_C
#undef PP_C_ARRYA_AC_C_INITIALIZER

}  // namespace detail

template<
	typename Seq,
	typename ArrayType = detail::array_type<boost::mpl::_1, boost::mpl::_2>
>
struct c_array
	: detail::c_array_impl<Seq, boost::mpl::size<Seq>::value, ArrayType>{};


} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_C_ARRAY_H */
