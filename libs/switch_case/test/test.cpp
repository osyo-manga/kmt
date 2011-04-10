//
// kmt-library
//
// Copyright (c) 2011 
// syo-manga : http://d.hatena.ne.jp/osyo-manga/
// 
// Readme:
// https://github.com/osyo-manga/kmt/blob/master/README
//
// License:
// Boost Software License - Version 1.0
// <http://www.boost.org/LICENSE_1_0.txt>
//

#include <boost/test/minimal.hpp>

#include <kmt/switch_case.hpp>
#include <string>

namespace sc = kmt::switch_case;

std::string
check1(const std::string& input){
	std::string result = sc::switch_(input)
		|=sc::case_(std::string("yes"))
		|=sc::case_(std::string("y"))
		|=sc::case_(std::string("Y"))|sc::var(std::string("ok"))
		|=sc::default_|sc::var(std::string("error"));
	return result;
}



int
test_main(int argc, char* argv[]){
	
	BOOST_CHECK( check1(std::string("yes") ) == std::string("ok") );
	BOOST_CHECK( check1(std::string("y"))    == std::string("ok") );
	BOOST_CHECK( check1(std::string("Y"))    == std::string("ok") );
	BOOST_CHECK( check1(std::string("hoge")) == std::string("error") );

	return 0;
}


