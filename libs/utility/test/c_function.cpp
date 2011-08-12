
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
#include <kmt/utility/c_function.hpp>

#include <boost/function.hpp>
#include <boost/bind.hpp>
static int const ok = 10;

typedef int(*int_void)();
typedef int(*int_int)(int);

int
func(){
	return ok;
}

int
func2(int n){
	return n;
}

struct obj{
	typedef int result_type;
	int operator ()() const{
		return ok;
	}
	int func(int n) const{
		return n;
	}
};

int
test_main(int argc, char* argv[]){
	int_void f1 = kmt::make_c_function<struct unique_id_0, int_void>(&func);
	BOOST_CHECK(f1() == ok);
	
	int_int f2 = kmt::make_c_function<struct unique_id_1, int_int>(&func2);
	BOOST_CHECK(f2(ok) == ok);

	int_void f3 = kmt::make_c_function<struct unique_id_2, int_void>(obj());
	BOOST_CHECK(f3() == ok);
	
	int_void f4 = kmt::make_c_function<struct unique_id_3, int_void>(
		boost::function<int()>(boost::bind(&func2, ok))
	);
	BOOST_CHECK(f4() == ok);
	
	obj o;
	int_void f5 = kmt::make_c_function<struct unique_id_4, int_void>(
		boost::function<int()>(boost::bind(&obj::func, &o, ok))
	);
	BOOST_CHECK(f5() == ok);

	return 0;
}

