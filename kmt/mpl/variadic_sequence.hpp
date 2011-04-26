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
#ifndef KMT_MPL_VARIADIC_SEQUENCE_H
#define KMT_MPL_VARIADIC_SEQUENCE_H

#include <boost/config.hpp>


#if !defined BOOST_NO_VARIADIC_TEMPLATES

#include <boost/mpl/apply.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_front.hpp>

namespace kmt{ namespace mpl{

namespace detail{

template<typename Seq, typename Inserter, typename ...Args>
struct variadic_sequence_impl;

template<typename Seq, typename Inserter, typename T, typename ...Args>
struct variadic_sequence_impl<Seq, Inserter, T, Args...>
	:  boost::mpl::apply<
		Inserter, variadic_sequence_impl<Seq, Inserter, Args...>, T
	>::type{};

template<typename Seq, typename Inserter, typename T>
struct variadic_sequence_impl<Seq, Inserter, T>
	: boost::mpl::apply<Seq, T>::type{};

template<typename Seq, typename Inserter>
struct variadic_sequence_impl<Seq, Inserter>
	: boost::mpl::vector<>{};

} // namespace detail{


template<typename Seq, typename Inserter, typename ...Args>
struct variadic_sequence : detail::variadic_sequence_impl<Seq, Inserter, Args...>{};

} } // namespace kmt{ namespace mpl{


#else


#include <boost/static_assert.hpp>
BOOST_STATIC_ASSERT(false && "No Supported Variadic Templates");


#endif



#endif /* KMT_MPL_VARIADIC_SEQUENCE_H */
