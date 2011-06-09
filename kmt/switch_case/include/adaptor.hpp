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
#ifndef KMT_SWITCH_CASE_INCLUDE_ADAPTOR_H
#define KMT_SWITCH_CASE_INCLUDE_ADAPTOR_H

#include "case.hpp"

namespace kmt{ namespace switch_case{

namespace detail{

template<typename caseT, typename nextT>
typename boost::enable_if_c<
	boost::is_base_of<case_impl<typename caseT::pred_type>, caseT>::value,
	case_next<caseT, nextT>
>::type
operator |=(caseT const& case_, nextT const& next){
	return case_next<caseT, nextT>(case_, next);
}


template<typename Pred, typename exprT>
case_expr<case_impl<Pred>, exprT&>
operator |(case_impl<Pred> const& case_, exprT& expr){
	return case_expr<case_impl<Pred>, exprT&>(case_, expr);
}

template<typename Pred, typename exprT>
case_expr<case_impl<Pred>, exprT const&>
operator |(case_impl<Pred> const& case_, exprT const& expr){
	return case_expr<case_impl<Pred>, exprT const&>(case_, expr);
}

template<typename caseT, typename exprT, typename T>
case_expr<case_expr<caseT, exprT>, T&>
operator |(case_expr<caseT, exprT> const& case_, T& expr){
	return case_expr<case_expr<caseT, exprT>, T&>(case_, expr);
}

template<typename caseT, typename exprT, typename T>
case_expr<case_expr<caseT, exprT>, T const&>
operator |(case_expr<caseT, exprT> const& case_, T const& expr){
	return case_expr<case_expr<caseT, exprT>, T const&>(case_, expr);
}
 

}  // namespace detail

} } // namespace kmt{ namespace switch_case{

#endif /* KMT_SWITCH_CASE_INCLUDE_ADAPTOR_H */
