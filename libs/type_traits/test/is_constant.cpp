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

#include <kmt/type_traits/is_constant.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>


struct hoge{
	static int const value = 10;
};
struct hoge2{
	typedef boost::integral_constant<int, 3>::type value;
};



int
test_main(int argc, char* argv[]){
	BOOST_CHECK((
		kmt::element_value<hoge>::type::value == 10
	));
	BOOST_CHECK((
		kmt::element_value<hoge2>::type::value == 3
	));
	
	BOOST_CHECK(( KMT_IS_CONSTANT(3)::value ));
	BOOST_CHECK(( KMT_IS_CONSTANT(int)::value == false ));


	return 0;
}


