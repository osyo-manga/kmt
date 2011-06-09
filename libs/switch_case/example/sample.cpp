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

#include <iostream>
#include <string>

namespace sc = kmt::switch_case;


/*
[output]
ok
ok
ok
error
*/

/*
	if( input == "yes" || input == "y" || input == "Y" )
		return "ok";
	else
		return "error";
*/
std::string
check(std::string const& input){
	std::string result
	= sc::switch_(input)
		|=sc::case_(std::string("yes"))
		|=sc::case_(std::string("y"))
		|=sc::case_(std::string("Y"))|sc::var(std::string("ok"))
		|=sc::default_|sc::var(std::string("error"));
	return result;
}

int
main(){
	
	std::cout << check("yes") << std::endl;
	std::cout << check("y") << std::endl;
	std::cout << check("Y") << std::endl;
	std::cout << check("NO!") << std::endl;

	return 0;
}
