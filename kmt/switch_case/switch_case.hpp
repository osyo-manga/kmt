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
#ifndef KMT_SWITCH_CASE_SWITCH_CASE_H
#define KMT_SWITCH_CASE_SWITCH_CASE_H

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/apply.hpp>
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

template<typename T, typename U>
bool equal(const T& t, const U& u){
	return t == u;
}

template<typename T>
struct equal_value{
	typedef T value_type;
	equal_value(value_type const& value) : value_(value){}
	
	template<typename U>
	bool operator ()(U const& u) const{
		return detail::equal(value_, u);
	}
	T value_;
};

template<typename T>
struct equal_type{
	typedef T value_type;
	
	template<typename U>
	bool operator ()(U const&) const{
		return boost::is_same<value_type, U>();
	}
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

//----------------------------------------------------------
// switch_t
template<typename T>
struct switch_t{
	typedef T value_type;
	
	explicit switch_t(const T& value_)
		: value(value_){}
	
	template<typename case_t>
	typename case_t::result_type
	operator |=(case_t case_) const{
		return case_.visit(value);
	}

private:
	value_type value;
};


// "*" の代わり
struct true_{}_;
template<typename T>
bool operator ==(const true_&, const T&){
	return true;
}

template<typename T>
struct functionable_holder{
	typedef T result_type;
	
	explicit functionable_holder(T t) : value(t){}

	result_type
	operator ()(){
		return value;
	}
	result_type
	operator ()() const{
		return value;
	}
private:
	T value;
};

static const detail::case_impl<equal_value<detail::true_> > default_(_);

}  // namespace detail


using detail::_;
using detail::default_;


template<typename T>
detail::functionable_holder<T&>
var(T& t){
	return detail::functionable_holder<T&>(t);
}

template<typename T>
detail::functionable_holder<T const&>
var(T const& t){
	return detail::functionable_holder<T const&>(t);
}

template<typename T>
detail::switch_t<T>
switch_(const T& t){
	return detail::switch_t<T>(t);
}

template<typename Pred>
detail::case_impl<Pred>
case_pred(Pred const& pred){
	return detail::case_impl<Pred>(pred);
}

template<typename T>
detail::case_impl<detail::equal_type<T> >
case_type(){
	return case_pred(detail::equal_type<T>());
}

template<typename T>
detail::case_impl<detail::equal_value<T> >
case_(T const& t){
	return case_pred(detail::equal_value<T>(t));
}


#if 0
namespace detail{

template<typename T, typename C, typename N>
typename result_type<C>::type
call_func(const T& src, C& case_, N& next){
	return case_.equal(src) ? case_() :  next.visit(src);
}

// 戻り値がある場合は、問答無用で最後の関数が呼ばれる
template<typename T, typename C>
typename boost::lazy_disable_if<boost::is_same<
	typename C::result_type, void
>, result_type<C> >::type
call_func(const T& src, C& case_, empty_case&){
	if( case_.equal(src) ) return case_();
	else throw(no_match("!exception! : no match switch case"));
}

// 戻り値がない場合は、こちらが呼ばれる
template<typename T, typename C>
typename boost::enable_if<boost::is_same<
	typename C::result_type, void
>, void>::type
call_func(const T& src, C& case_, empty_case&){
	if( case_.equal(src) ) case_();
}

template<typename F>
struct eval_impl{
	typedef F func_type;
	typedef typename result_type<func_type>::type result_type;
	
	explicit eval_impl(F f) : func_(f){}
	
	result_type
	operator ()(){
		return static_cast<result_type>(func_());
	}
private:
	func_type func_;
};

template<typename T>
struct value_impl{
	typedef T value_type;
	typedef value_type result_type;
	
	explicit value_impl(value_type value) : value_(value){}
	
	result_type
	operator ()(){
		return static_cast<result_type>(value_);
	}
private:
	value_type value_;
};

template<typename T>
struct case_value{
	typedef T value_type;
	
	case_value(const value_type& value)
		: value_(value){}
	
	template<typename U>
	bool
	equal(const U& t) const{
		return detail::equal(value_, t);
	}
	
private:
	value_type value_;
};

template<typename Pred>
struct case_type{
	template<typename T>
	bool equal(const T&) const{
		return mpl::apply<Pred, T>::type::value;
	}
};

template<typename caseT, typename nextT = empty_case>
struct case_impl{
	typedef caseT case_type;
	typedef nextT next_type;
	typedef case_impl<case_type, next_type> this_type;
	typedef typename next_type::result_type result_type;
	
	explicit case_impl(
		const case_type& case__,
		const next_type& next = empty_case()
	)
	: case_(case__), next_(next){}
	
	template<typename new_nextT>
	case_impl<this_type, new_nextT>
	operator |=(const new_nextT& next) const{
		return case_impl<this_type, new_nextT>(*this, next);
	}
	
	result_type
	operator ()(){
		return get_next()();
	}
	
	template<typename U>
	result_type
	visit(const U& value){
		return call_func(value, *this, next_);
	}
	
	template<typename U>
	bool
	equal(const U& u) const{
		return case_.equal(u);
	}
	
	next_type& get_next(){
		return next_;
	}
	next_type const& get_next() const{
		return next_;
	}
private:
	case_type case_;
	next_type next_;
};

//----------------------------------------------------------
// case_expression_impl
template<typename caseT, typename expressionT>
struct case_expression_impl{
	typedef caseT       case_type;
	typedef expressionT expression_type;
	typedef case_expression_impl<case_type, expression_type> this_type;
	typedef typename expression_type::result_type result_type;
	typedef typename case_type::next_type next_type;
	
	explicit case_expression_impl(
		const case_type& case__,
		expression_type expression
	)
	: case_(case__), expression_(expression){}
	template<typename new_nextT>
	case_expression_impl<case_impl<case_type, new_nextT>, expression_type>
	operator |=(const new_nextT& next) const{
		return case_expression_impl<case_impl<case_type, new_nextT>, expression_type>
			(case_impl<case_type, new_nextT>(case_, next), expression_);
	}
/*
	template<typename new_nextT>
	case_impl<this_type, new_nextT>
	operator |=(const new_nextT& next) const{
		return case_impl<this_type, new_nextT>(*this, next) ;
	}
*/
	result_type
	operator ()(){
		return expression_();
	}
	
	template<typename U>
	result_type
	visit(const U& value){
		return call_func(value, *this, case_.get_next());
	}
	
	template<typename T>
	bool
	equal(const T& t) const{
		return case_.equal(t);
	}
	
private:
	case_type case_;
	expression_type expression_;
};

template<typename T, typename next_type, typename F>
case_expression_impl<case_impl<T, next_type>, eval_impl<F&> >
operator |(case_impl<T, next_type> const& case_, F& f){
	return case_expression_impl<case_impl<T, next_type>, eval_impl<F&> >
		(case_, eval_impl<F&>(f));
}

template<typename T, typename next_type, typename F>
case_expression_impl<case_impl<T, next_type>, eval_impl<F const&> >
operator |(case_impl<T, next_type> const& case_, F const& f){
	return case_expression_impl<case_impl<T, next_type>, eval_impl<F const&> >
		(case_, eval_impl<F const&>(f));
}


template<typename T, typename next_type, typename U>
case_expression_impl<case_impl<T, next_type>, value_impl<U&> >
operator &(case_impl<T, next_type> const& case_, U& value){
	return case_expression_impl<case_impl<T, next_type>, value_impl<U> >
		(case_, value_impl<U>(value));
}

template<typename T, typename next_type, typename U>
case_expression_impl<case_impl<T, next_type>, value_impl<U const&> >
operator &(case_impl<T, next_type> const& case_, U const& value){
	return case_expression_impl<case_impl<T, next_type>, value_impl<U const&> >
		(case_, value_impl<U const&>(value));
}
#endif

#if 0
template<typename T>
detail::case_impl<detail::case_value<T> >
case_(const T& t){
	return detail::case_impl<detail::case_value<T> >(detail::case_value<T>(t));
}

template<typename Pred>
detail::case_impl<detail::case_type<Pred> >
case_type(){
	return detail::case_impl<detail::case_type<Pred> >(detail::case_type<Pred>());
}

template<typename T>
detail::case_impl<detail::case_type<boost::is_same<T, boost::mpl::_1> > >
case_(){
	return case_type<boost::is_same<T, boost::mpl::_1> >();
}



// 引数が2個以上の場合は、boost::tuple で保持
template<typename T1, typename T2>
detail::switch_t<boost::tuple<T1, T2> >
switch_(const T1& t1, const T2& t2){
	return detail::switch_t<boost::tuple<T1, T2> >
		(boost::make_tuple(t1, t2));
}

template<typename T1, typename T2>
detail::case_impl<detail::case_value<boost::tuple<T1, T2> > >
case_(const T1& t1, const T2& t2){
	return case_( boost::make_tuple(t1, t2) );
}
#endif

//----------------------------------------------------------
// expr
#if 0
template<typename T, typename F>
detail::case_expression_impl<
	detail::case_impl<detail::case_value<T> >,
	detail::eval_impl<F&>
>
case_expr(const T& t, F& f){
	return detail::case_expression_impl<
		detail::case_impl<detail::case_value<T> >,
		detail::eval_impl<F&>
	>(detail::case_impl<detail::case_value<T> >(t), detail::eval_impl<F&>(f));
}


template<typename T, typename F>
detail::case_expression_impl<
	detail::case_impl<detail::case_value<T> >,
	detail::eval_impl<F const&>
>
case_expr(const T& t, F const& f){
	return detail::case_expression_impl<
		detail::case_impl<detail::case_value<T> >,
		detail::eval_impl<F const&>
	>(detail::case_impl<detail::case_value<T> >(t), detail::eval_impl<F const&>(f));
}

template<typename F>
detail::case_expression_impl<
	detail::case_impl<detail::case_value<detail::true_> >,
	detail::eval_impl<F&>
>
default_expr(F& f){
	return case_expr(detail::_, f);
}

template<typename F>
detail::case_expression_impl<
	detail::case_impl<detail::case_value<detail::true_> >,
	detail::eval_impl<F const&>
>
default_expr(F const& f){
	return case_expr(detail::_, f);
}

template<typename T1, typename T2, typename F>
detail::case_expression_impl<
	detail::case_impl<detail::case_value<boost::tuple<T1, T2> > >,
	detail::eval_impl<F&>
>
case_expr(const T1& t1, const T2& t2, F& f){
	return case_expr( boost::make_tuple(t1, t2), f);
}

template<typename T1, typename T2, typename F>
detail::case_expression_impl<
	detail::case_impl<detail::case_value<boost::tuple<T1, T2> > >,
	detail::eval_impl<F const&>
>
case_expr(const T1& t1, const T2& t2, F const& f){
	return case_expr( boost::make_tuple(t1, t2), f);
}
#endif

}  // namespace switch_case
}  // namespace kmt

#endif // #ifdef KMT_SWITCH_CASE_SWITCH_CASE_H

