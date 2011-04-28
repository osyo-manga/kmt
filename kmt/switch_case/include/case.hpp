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
#ifndef KMT_SWITCH_CASE_INCLUDE_CASE_H
#define KMT_SWITCH_CASE_INCLUDE_CASE_H

#include <boost/utility/enable_if.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include "exception.hpp"

namespace kmt{ namespace switch_case{

namespace detail{

namespace mpl = boost::mpl;

template<typename F>
struct result_of : boost::result_of<F()>{};

template<typename F>
struct result_of<F&> : result_of<F>{};

template<typename F>
struct result_of<F const&> : result_of<F>{};

template<typename T>
struct equal_value{
	typedef T value_type;
	equal_value(value_type const& value) : value_(value){}
	
	template<typename U>
	bool operator ()(U const& u) const{
		return value_ == u;
	}
private:
	T value_;
};

BOOST_MPL_HAS_XXX_TRAIT_DEF(expr_type);
template<typename T>
struct is_fall_through : boost::mpl::not_<has_expr_type<T> >{};

template<typename Pred>
struct case_impl{
	typedef Pred pred_type;
	typedef void result_type;
	
	case_impl(pred_type const& pred)
		: pred_(pred){}
	
	template<typename T>
	bool equal(T const& t) const{
		return pred_(t);
	}
	
	result_type
	operator ()() const{};
	
	template<typename T>
	result_type
	visit(T const& src){}
private:
	pred_type pred_;
};

template<typename caseT, typename ExprT>
struct case_expr : caseT{
	typedef caseT case_type;
	typedef case_type base_type;
	typedef ExprT expr_type;
	typedef typename result_of<expr_type>::type result_type;
	
	case_expr(case_type const& case_, expr_type expr)
		: base_type(case_), expr_(expr){}
	
	result_type
	operator ()(){
		static_cast<base_type>(*this)();
		return expr_();
	}
	
	template<typename T>
	result_type
	visit(T const& src){
		return eval(src);
	}
	
private:
	template<typename T>
	result_type
	eval(T const& src){
		return ( base_type::equal(src) ) ? (*this)() : no_match<result_type>();
	}
	
	// 戻り値型が void 以外の場合のみ例外を飛ばす
	template<typename T>
	result_type
	no_match(typename boost::disable_if<boost::is_void<T> >::type* =0){
		throw(switch_case::no_match("!exception! : no match switch case"));
	}
	template<typename T>
	result_type
	no_match(typename boost::enable_if<boost::is_void<T> >::type* =0){}
	
	expr_type expr_;
};

template<typename caseT, typename exprT>
case_expr<caseT, exprT&>
operator |(caseT const& case_, exprT& expr){
	return case_expr<caseT, exprT&>(case_, expr);
}

template<typename caseT, typename exprT>
case_expr<caseT, exprT const&>
operator |(caseT const& case_, exprT const& expr){
	return case_expr<caseT, exprT const&>(case_, expr);
}


template<typename caseT, typename nextT>
struct case_next
	: caseT{
	typedef caseT case_type;
	typedef case_type base_type;
	typedef nextT next_type;
	typedef typename next_type::result_type result_type;
	
	case_next(case_type const& case_, next_type next)
		: base_type(case_), next_(next){}
	
	result_type
	operator ()(){
		return eval<case_type>();
	}
	
	template<typename T>
	result_type
	visit(T const& src){
		return ( base_type::equal(src) ) ? (*this)() : next_.visit(src);
	}
	
private:
	template<typename U>
	result_type
	eval(typename boost::enable_if<is_fall_through<U> >::type* =0){
		return next_();
	}
	
	template<typename U>
	result_type
	eval(typename boost::disable_if<is_fall_through<U> >::type* =0){
		return static_cast<base_type&>(*this)();
	}
	
	next_type next_;
};

template<typename caseT, typename nextT>
typename boost::enable_if_c<
	boost::is_base_of<case_impl<typename caseT::pred_type>, caseT>::value,
	case_next<caseT, nextT>
>::type
operator |=(caseT const& case_, nextT const& next){
	return case_next<caseT, nextT>(case_, next);
}

}  // namespace detail{

template<typename Pred>
detail::case_impl<Pred>
case_pred(Pred const& pred){
	return detail::case_impl<Pred>(pred);
}

template<typename T>
detail::case_impl<detail::equal_value<T> >
case_(T const& t){
	return case_pred(detail::equal_value<T>(t));
}

} } // namespace kmt{ namespace switch_case{

#endif /* KMT_SWITCH_CASE_INCLUDE_CASE_H */
