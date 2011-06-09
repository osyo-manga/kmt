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

#include <iostream>
#include <string>

namespace sc = kmt::switch_case;

int
main(){
	std::string input = "yes";
	
	// 戻り値型（var の引数）を std::string で保持する
	std::string result
	= sc::returnable_switch<std::string>(input)
		|=sc::case_(std::string("yes"))
		|=sc::case_(std::string("y"))
		|=sc::case_(std::string("Y"))|sc::var("ok")
		|=sc::default_|sc::var("error");
	
	std::cout << result << std::endl;
	
	return 0;
}

/*
[output]
ok
*/
