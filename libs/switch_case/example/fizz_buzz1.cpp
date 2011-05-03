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
#include <kmt/switch_case/include/var.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <iostream>


namespace sc = kmt::switch_case;


std::string
fizz_buzz(int n){
	using sc::_;
	using boost::make_tuple;
	return sc::switch_(make_tuple(n%3, n%5))
		|=sc::case_(make_tuple(0, 0))|sc::var(std::string("fizz_buzz"))
		|=sc::case_(make_tuple(0, _))|sc::var(std::string("fizz"))
		|=sc::case_(make_tuple(_, 0))|sc::var(std::string("buzz"))
		|=sc::default_|sc::var(boost::lexical_cast<std::string>(n));
}


int
main(){
	for(int i = 1 ; i < 50 ; i++){
		std::cout << fizz_buzz(i) << ",";
	}
	return 0;
}

