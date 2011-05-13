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
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include "exception.hpp"

namespace kmt{ namespace switch_case{

namespace detail{

namespace mpl = boost::mpl;

template<typename F, typename Arg>
struct result_of : boost::result_of<F(Arg)>{};

template<typename F, typename Arg>
struct result_of<F&, Arg> : result_of<F, Arg>{};

template<typename F, typename Arg>
struct result_of<F const&, Arg> : result_of<F, Arg>{};

// 戻り値型が void 以外の場合のみ例外を飛ばす
template<typename T>
T
no_match(typename boost::disable_if<boost::is_void<T> >::type* =0){
	throw(switch_case::no_match("!exception! : no match switch case"));
}
template<typename T>
T
no_match(typename boost::enable_if<boost::is_void<T> >::type* =0){}


BOOST_MPL_HAS_XXX_TRAIT_DEF(expr_type);
template<typename T>
struct is_fall_through : boost::mpl::not_<has_expr_type<T> >{};


template<typename Pred>
struct case_impl{
	typedef Pred pred_type;
	
	template<typename T>
	struct result{
		typedef void type;
	};
	
	case_impl(pred_type const& pred)
		: pred_(pred){}
	
	template<typename T>
	bool equal(T const& t) const{
		return pred_(t);
	}
	
	template<typename T>
	void
	eval(T const&) const{}
	
	template<typename T>
	void
	operator ()(T const& src) const{}
	
	template<typename T>
	void
	operator ()(T const& src){}
private:
	pred_type pred_;
};


template<typename caseT, typename ExprT>
struct case_expr : caseT{
	typedef case_expr this_type;
	typedef caseT     case_type;
	typedef case_type base_type;
	typedef ExprT     expr_type;
	
	template<typename T>
	struct result{
		typedef typename result_of<expr_type, T>::type type;
	};
	
	case_expr(case_type const& case_, expr_type expr)
		: base_type(case_), expr_(expr){}
	
	template<typename T>
	typename result_of<this_type, T>::type
	eval(T const& src){
		static_cast<base_type>(*this).eval(src);
		return static_cast<typename result_of<this_type, T>::type>(expr_(src));
	}
	
	template<typename T>
	typename result_of<this_type, T>::type
	operator ()(T const& src){
		return ( base_type::equal(src) ) ? eval(src) : no_match<typename result<T>::type>();
	}
	
private:
	expr_type expr_;
};


template<typename caseT, typename nextT>
struct case_next
	: caseT{
	typedef caseT     case_type;
	typedef case_type base_type;
	typedef case_next this_type;
	typedef nextT     next_type;
	
	// fall through の有無で戻り値型を変える
	template<typename T>
	struct result{
		typedef typename
			mpl::eval_if<
				is_fall_through<case_type>,
				result_of<next_type, T>,
				result_of<base_type, T>
			>::type
		type;
	};
	
	case_next(case_type const& case_, next_type next)
		: base_type(case_), next_(next){}
	
	template<typename T>
	typename result_of<this_type, T>::type
	eval(T const& src){
		return apply<T, case_type>(src);
	}
	
	template<typename T>
	typename result_of<this_type, T>::type
	operator ()(T const& src){
		return ( base_type::equal(src) ) ? eval(src) : next_(src);
	}
	
	next_type next(){
		return next_;
	}
	
private:
	template<typename T, typename U>
	typename result_of<this_type, T>::type
	apply(T const& src, typename boost::enable_if<is_fall_through<U> >::type* =0){
		return next_.eval(src);
	}
	
	template<typename T, typename U>
	typename result_of<this_type, T>::type
	apply(T const& src, typename boost::disable_if<is_fall_through<U> >::type* =0){
		return base_type::eval(src);
	}
	
	next_type next_;
};


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
