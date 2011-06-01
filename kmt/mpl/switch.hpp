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
#ifndef KMT_MPL_SWITCH_H
#define KMT_MPL_SWITCH_H

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/switch.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/lambda.hpp>

namespace kmt{ namespace mpl{

template<typename F, typename S, typename T = void>
struct case_;

template<typename F, typename S>
struct case_<F, S,
	typename boost::enable_if<boost::mpl::is_lambda_expression<S> >::type>
	: boost::mpl::pair<F, S> {};

template<typename F, typename S>
struct case_<F, S,
	typename boost::disable_if<boost::mpl::is_lambda_expression<S> >::type>
	: boost::mpl::pair<F, boost::mpl::always<S> > {};

template<typename S>
struct default_ : case_<boost::mpl::always<boost::mpl::true_>, S>{};


} } // namespace kmt{ namespace mpl{

#endif /* KMT_MPL_SWITCH_H */
