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
#include <kmt/switch_case/include/case_type.hpp>
#include <kmt/switch_case/include/var.hpp>

#include <iostream>
#include <string>

namespace sc = kmt::switch_case;

template<typename T>
std::string
check(T t){
	return sc::switch_(t)
		|=sc::case_type<int>()  |sc::var(std::string("int"))
		|=sc::case_type<float>()|sc::var(std::string("float"))
		|=sc::default_          |sc::var(std::string("other type"));
}

int
main(){
	std::cout << check(10) << std::endl;
	std::cout << check(3.14f) << std::endl;
	std::cout << check('c') << std::endl;
	std::cout << check(std::string("hoge")) << std::endl;
	return 0;
}
