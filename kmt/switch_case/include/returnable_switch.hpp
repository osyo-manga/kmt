//
// kmt-library
///
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
#ifndef KMT_SWITCH_CASE_INCLUDE_RETURNABLE_SWITCH_H
#define KMT_SWITCH_CASE_INCLUDE_RETURNABLE_SWITCH_H

#include <boost/mpl/has_xxx.hpp>

namespace kmt{ namespace switch_case{

namespace detail{

template<typename R, typename U>
struct returnable_switch_impl{
	
	BOOST_MPL_HAS_XXX_TRAIT_DEF(next_type);
	typedef U value_type;
	typedef R result_type;
	
	explicit returnable_switch_impl(U const& value)
		: value_(value){}
	
	template<typename case_t>
	result_type
	operator |=(case_t case_) const{
		return eval(case_);
	}
	// 次の case の有無で処理を切り分ける
	template<typename case_t>
	result_type
	eval(case_t case_,
		typename boost::disable_if<has_next_type<case_t> >::type* =0
	) const{
		return case_.equal(value_) ? case_.eval(value_) : no_match<result_type>();
	}
	
	template<typename case_t>
	result_type
	eval(case_t case_,
		typename boost::enable_if<has_next_type<case_t> >::type* =0
	) const{
		return (case_.equal(value_)) ? eval_next(case_) : eval(case_.next());
	}
	
private:
	// fall through の有無で処理を切り分ける
	template<typename case_t>
	result_type
	eval_next(case_t case_,
		typename boost::enable_if<is_fall_through<case_t> >::type* =0
	) const{
		return (case_.next().eval(value_));
	}
	
	template<typename case_t>
	result_type
	eval_next(case_t case_,
		typename boost::disable_if<is_fall_through<case_t> >::type* =0
	) const{
		return static_cast<typename case_t::base_type>(case_).eval(value_);
	}
	
	value_type value_;
};

} // namespace detail{

template<typename R, typename T>
detail::returnable_switch_impl<R, T>
returnable_switch(T const& t){
	return detail::returnable_switch_impl<R, T>(t);
}

} } // namespace kmt{ namespace switch_case{ namespace detail{


#endif /* KMT_SWITCH_CASE_INCLUDE_RETURNABLE_SWITCH_H */
