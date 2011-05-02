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
#ifndef KMT_SWITCH_CASE_INCLUDE_SWITCH_H
#define KMT_SWITCH_CASE_INCLUDE_SWITCH_H

namespace kmt{ namespace switch_case{

namespace detail{

template<typename T>
struct switch_impl{
	typedef T value_type;
	
	explicit switch_impl(const T& value)
		: value_(value){}
	
	template<typename case_t>
	typename case_t::result_type
	operator |=(case_t case_) const{
		return case_(value_);
	}
	
private:
	value_type value_;
};

}  // namespace detail

template<typename T>
detail::switch_impl<T>
switch_(T const& t){
	return detail::switch_impl<T>(t);
}


} } // namespace kmt{ namespace switch_case{

#endif /* KMT_SWITCH_CASE_INCLUDE_SWITCH_H */
