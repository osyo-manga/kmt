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
#include <boost/mpl/print.hpp>
#include <kmt/switch_case/include/case_variant.hpp>
#include <kmt/switch_case/include/var.hpp>
#include <kmt/switch_case/include/switch_case.hpp>

#include <boost/variant/variant.hpp>
#include <iostream>
#include <string>

namespace sc = kmt::switch_case;


std::string
check(boost::variant<int, float, char, std::string> var){
	return sc::switch_(var)
		|=sc::case_variant<int>()  |sc::var(std::string("int"))
		|=sc::case_variant<float>()|sc::var(std::string("float"))
		|=sc::default_|sc::var(std::string("other type"));
}

int
main(){
	std::cout << check(10) << std::endl;
	std::cout << check(3.14f) << std::endl;
	std::cout << check(std::string("hoge")) << std::endl;
	std::cout << check('c') << std::endl;
	return 0;
}

/*
[output]
int
float
other type
other type
*/
