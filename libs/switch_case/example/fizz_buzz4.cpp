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
#include <kmt/switch_case/include/switch_case.hpp>
#include <kmt/switch_case/include/returnable_switch.hpp>
#include <kmt/switch_case/include/var.hpp>

#include <boost/variant/variant.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <string>
#include <iostream>


namespace sc = kmt::switch_case;

void
fizz_buzz_disp(int n){
	using sc::_;
	using boost::make_tuple;
	typedef boost::variant<int, std::string> result_type;
	result_type result
	= sc::returnable_switch<result_type>(make_tuple(n%3, n%5))
		|=sc::case_(make_tuple(0, 0))|sc::var("fizz_buzz")
		|=sc::case_(make_tuple(0, _))|sc::var("fizz")
		|=sc::case_(make_tuple(_, 0))|sc::var("buzz")
		|=sc::default_|sc::var(n);
	std::cout << result << ",";
}


int
main(){
	for(int i = 1 ; i < 50 ; i++){
		fizz_buzz_disp(i);
	}
	return 0;
}

