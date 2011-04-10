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
#ifndef _KMT_SWITCH_CASE_H_
#define _KMT_SWITCH_CASE_H_

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>

namespace kmt{

namespace switch_case{

namespace detail{

template<typename F>
struct result_type : boost::result_of<F()>{};

template<typename F>
struct result_type<F&> : result_type<F>{};

template<typename F>
struct result_type<F const&> : result_type<F>{};


struct empty_case{
	typedef void result_type;
};

template<typename T, typename U>
bool equal(const T& t, const U& u){
	return t == u;
}

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
	return case_();
}

// 戻り値がない場合は、こちらが呼ばれる
template<typename T, typename C>
typename boost::enable_if<boost::is_same<
	typename C::result_type, void
>, void>::type
call_func(const T& src, C& case_, empty_case&){
	if( case_.equal(src) ) case_();
}

//----------------------------------------------------------
// case_t
template<typename CaseValueT, typename F, typename Next = empty_case>
struct case_t{
	typedef typename result_type<F>::type result_type;
	typedef Next NextT;
	
	explicit case_t(const CaseValueT& s, F func_, const Next& next_ = empty_case())
		: case_value(s), func(func_), next(next_){}
	
	template<typename Next_>
	case_t<CaseValueT, F, Next_>
	operator |=(const Next_& next){
		return case_t<CaseValueT, F, Next_>(case_value, func, next);
	}
	
	result_type
	operator ()(){
		return static_cast<result_type>(func());
	}
	
	template<typename U>
	result_type
	visit(const U& value){
		std::cout << case_value << std::endl;
		return call_func(value, *this, next);
	}
	
	template<typename T>
	bool
	equal(const T& rhs){
		return detail::equal(case_value, rhs);
	}
	
private:
	CaseValueT	case_value;
	F			func;
	Next		next;
};

//----------------------------------------------------------
// case_expression_impl
template<typename caseT, typename expressionT, typename nextT = empty_case>
struct case_expression_impl{
	typedef caseT       case_type;
	typedef expressionT expression_type;
	typedef nextT       next_type;
	typedef typename expression_type::result_type result_type;
	
	explicit case_expression_impl(
		const case_type& case__,
		expression_type expression,
		const next_type& next = empty_case()
	)
	: case_(case__), expression_(expression), next_(next){}
	
	template<typename new_nextT>
	case_expression_impl<case_type, expression_type, new_nextT>
	operator |=(const new_nextT& next) const{
		return case_expression_impl<case_type, expression_type, new_nextT>
			(case_, expression_, next);
	}
	
	result_type
	operator ()(){
		return static_cast<result_type>(expression_());
	}
	
	template<typename U>
	result_type
	visit(const U& value){
		return call_func(value, *this, next_);
	}
	
	template<typename T>
	bool
	equal(const T& t) const{
		return case_.equal(t);;
	}
private:
	case_type case_;
	expression_type expression_;
	next_type next_;
};

template<typename F>
struct expression_impl{
	typedef F func_type;
	typedef typename result_type<func_type>::type result_type;
	
	explicit expression_impl(F f) : func_(f){}
	
	result_type
	operator ()(){
		return func_();
	}
private:
	func_type func_;
};

template<typename T, typename nextT = empty_case>
struct case_impl{
	typedef T     value_type;
	typedef nextT next_type;
	typedef case_impl<T, nextT> case_type;
	typedef typename next_type::result_type result_type;
	
	explicit case_impl(
		const value_type& value,
		const next_type& next = empty_case()
	)
	: value_(value), next_(next){}
	
	template<typename new_nextT>
	case_impl<value_type, new_nextT>
	operator |=(const new_nextT& next) const{
		return case_impl<value_type, new_nextT>(value_, next);
	}
	
	template<typename F>
	case_expression_impl<case_type, expression_impl<F&>, next_type>
	operator |(F& f) const{
		return case_expression_impl<case_type, expression_impl<F&>, next_type>
			(*this, expression_impl<F&>(f), next_);
	}
	template<typename F>
	case_expression_impl<case_type, expression_impl<F const&>, next_type>
	operator |(F const& f) const{
		return case_expression_impl<case_type, expression_impl<F const&>, next_type>
			(*this, expression_impl<F const&>(f), next_);
	}
	
	result_type
	operator ()(){
		return next_();
	}
	
	template<typename U>
	result_type
	visit(const U& value){
		return call_func(value, *this, next_);
	}
	
	template<typename U>
	bool
	equal(const U& t) const{
		return detail::equal(value_, t);
	}
	
private:
	value_type value_;
	next_type  next_;
};

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
std::ostream&
operator <<(std::ostream& os, const true_&){
	os << true;
	return os;
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

static const detail::case_impl<detail::true_> default_(_);

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

#if 0

template<typename T>
detail::switch_t<T>
switch_(const T& t){
	return detail::switch_t<T>(t);
}

template<typename T, typename F>
detail::case_t<T, F&>
case_(const T& t, F& func){
	return detail::case_t<T, F&>(t, func);
}
template<typename T, typename F>
detail::case_t<T, const F&>
case_(const T& t, const F& func){
	return detail::case_t<T, const F&>(t, func);
}

template<typename F>
detail::case_t<detail::true_, F&>
default_(F& func){
	return detail::case_t<detail::true_, F&>(_, func);
}

template<typename F>
detail::case_t<detail::true_, const F&>
default_(const F& func){
	return detail::case_t<detail::true_, const F&>(_, func);
}


// 引数が2個以上の場合は、boost::tuple で保持
template<typename T1, typename T2>
detail::switch_t<boost::tuple<T1, T2> >
switch_(const T1& t1, const T2& t2){
	return detail::switch_t<boost::tuple<T1, T2> >
		(boost::make_tuple(t1, t2));
}

template<typename T1, typename T2, typename F>
detail::case_t<boost::tuple<T1, T2>, F&>
case_(const T1& t1, const T2& t2, F& func){
	return detail::case_t<boost::tuple<T1, T2>, F&>
		(boost::make_tuple(t1, t2), func);
}

template<typename T1, typename T2, typename F>
detail::case_t<boost::tuple<T1, T2>, const F&>
case_(const T1& t1, const T2& t2, const F& func){
	return detail::case_t<boost::tuple<T1, T2>, const F&>
		(boost::make_tuple(t1, t2), func);
}

#else

template<typename T>
detail::switch_t<T>
switch_(const T& t){
	return detail::switch_t<T>(t);
}

template<typename T>
detail::case_impl<T>
case_(const T& t){
	return detail::case_impl<T>(t);
}


// 引数が2個以上の場合は、boost::tuple で保持
template<typename T1, typename T2>
detail::switch_t<boost::tuple<T1, T2> >
switch_(const T1& t1, const T2& t2){
	return detail::switch_t<boost::tuple<T1, T2> >
		(boost::make_tuple(t1, t2));
}

template<typename T1, typename T2>
detail::case_impl<boost::tuple<T1, T2> >
case_(const T1& t1, const T2& t2){
	return case_( boost::make_tuple(t1, t2) );
}

#endif

}  // namespace switch_case
}  // namespace kmt

#endif // #ifdef _KMT_SWITCH_CASE_H_

