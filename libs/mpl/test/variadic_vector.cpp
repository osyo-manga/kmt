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

#include <kmt/mpl/variadic_vector.hpp>

typedef kmt::mpl::variadic_vector<int, float, char> seq;


#include <boost/mpl/size.hpp>
#include <boost/mpl/equal.hpp>

namespace mpl = boost::mpl;

int
test_main(int argc, char* argv[]){
	
	BOOST_CHECK(( mpl::equal<
		seq, mpl::vector<int, float, char>
	>::value ));
	
	BOOST_CHECK(( mpl::size<seq>::value == 3 ));
	
	return 0;
}


