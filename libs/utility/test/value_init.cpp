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

#include <kmt/utility/value_init.hpp>

struct test1{
	typedef int value_type;
	operator value_type() const{
		return 10;
	}
};

struct test2{
	typedef float value_type;
	operator value_type(){
		return 0.25f;
	}
};


int
test_main(int argc, char* argv[]){
	
	kmt::initialized<test1> t1;
	kmt::initialized<test2> t2;
	
	BOOST_CHECK(t1 == 10);
	BOOST_CHECK(t2 == 0.25f);
	
	return 0;
}


