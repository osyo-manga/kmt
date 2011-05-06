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
#ifndef KMT_SWITCH_CASE_INCLUDE_LAMBDA_ADAPTOR_H
#define KMT_SWITCH_CASE_INCLUDE_LAMBDA_ADAPTOR_H

#include <boost/lambda/lambda.hpp>
#include "case.hpp"

namespace kmt{ namespace switch_case {

namespace detail{

template<typename Pred, typename Arg>
case_expr<case_impl<Pred>, boost::lambda::lambda_functor<Arg> const&>
operator |(
	case_impl<Pred> const& case_,
	boost::lambda::lambda_functor<Arg> const& expr
){
	return case_expr<
		case_impl<Pred>,
		boost::lambda::lambda_functor<Arg> const&
	>(case_, expr);
}


template<typename caseT, typename exprT, typename Arg>
case_expr<case_expr<caseT, exprT>, boost::lambda::lambda_functor<Arg> const&>
operator |(
	case_expr<caseT, exprT> const& case_,
	boost::lambda::lambda_functor<Arg> const& expr
){
	return case_expr<
		case_expr<caseT, exprT>,
		boost::lambda::lambda_functor<Arg> const&
	>(case_, expr);
}


}  // namespace detail

} } // namespace kmt{ namespace switch_case {

namespace boost { namespace lambda{

template<typename Pred, typename U>
struct return_type_2<bitwise_action<or_action>,
	kmt::switch_case::detail::case_impl<Pred> const&, U const&>
{
	typedef kmt::switch_case::detail::case_expr<
		kmt::switch_case::detail::case_impl<Pred>,
		U const&
	> type;
};

template<typename caseT, typename exprT, typename U>
struct return_type_2<bitwise_action<or_action>,
	kmt::switch_case::detail::case_expr<caseT, exprT> const&, U const&>{
	typedef kmt::switch_case::detail::case_expr<
		kmt::switch_case::detail::case_expr<caseT, exprT>,
		U const&
	> type;
};

} }  // namespace boost{ namespace lambda {



#endif /* KMT_SWITCH_CASE_INCLUDE_LAMBDA_ADAPTOR_H */
