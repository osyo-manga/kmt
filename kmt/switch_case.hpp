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

#if 0

namespace mpl = boost::mpl;

template<typename T>
struct is_func{
private:
	template<typename F>
	static auto check(F f)->decltype( f() );
	// boost::result_of は、戻り値の特定に失敗した場合、void を返すので、SFINAE 出来ない
	// 例）boost::result_of<int()>::type は、void 型
//	static void check(F f, typename boost::result_of<F()>::type* =0);
	struct false_{};
	static false_ check(...);
public:
	static const bool value = !boost::is_same<
		decltype( check(boost::declval<T>()) ),
		false_
	>::value;
};

template<typename T>
struct result_type{
	template<typename U>
	struct result_of{
		typedef decltype(boost::declval<U>()()) type;
//		typedef typename boost::result_of<T()>::type type;
	};
	typedef typename mpl::if_<
		is_func<T>,
		result_of<T>,
//		boost::result_of<T()>
		mpl::identity<T>
	>::type::type type;
};

template<typename T>
typename result_type<T>::type
call_func(T t, typename boost::disable_if<is_func<T> >::type* =0){
	return t;
}

template<typename F>
typename result_type<F>::type
call_func(F f, typename boost::enable_if<is_func<F> >::type* =0){
	return f();
}
#else

template<typename F>
struct result_type : boost::result_of<F()>{};

template<typename F>
struct result_type<F&> : result_type<F>{};

template<typename F>
struct result_type<F const&> : result_type<F>{};

#endif


struct empty_case{};


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
	visit(const U& src){
		return call_func(src, *this, next);
	}
	template<typename T>
	bool
	equal(const T& rhs){
		return case_value == rhs;
	}
	
private:
	CaseValueT	case_value;
	F			func;
	Next		next;
};

template<typename T>
struct switche_t{
	typedef T value_type;
	
	explicit switche_t(const T& value_)
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


}  // namespace detail

using detail::_;

#if 0

template<typename T>
detail::functionable_holder<T>
var(T t){
	return detail::functionable_holder<T>(t);
}

#else

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

#endif


template<typename T>
detail::switche_t<T>
switch_(const T& t){
	return detail::switche_t<T>(t);
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
detail::switche_t<boost::tuple<T1, T2> >
switch_(const T1& t1, const T2& t2){
	return detail::switche_t<boost::tuple<T1, T2> >
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

}  // namespace switch_case
}  // namespace kmt

#endif // #ifdef _KMT_SWITCH_CASE_H_

