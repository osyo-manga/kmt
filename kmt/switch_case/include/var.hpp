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
#ifndef KMT_SWITCH_CASE_INCLUDE_VAR_H
#define KMT_SWITCH_CASE_INCLUDE_VAR_H

namespace kmt{ namespace switch_case{

namespace detail{

template<typename T>
struct functionable_holder{
	typedef T result_type;
	
	explicit functionable_holder(T const& t) : value(t){}
	
	template<typename U>
	T operator ()(U const&){
		return value;
	}
	
	template<typename U>
	T operator ()(U const&) const{
		return value;
	}
private:
	T value;
};

}  // namespace detail

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

} } // namespace kmt{ namespace switch_case{

#endif /* KMT_SWITCH_CASE_INCLUDE_VAR_H */
