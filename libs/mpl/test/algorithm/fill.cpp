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

#include <kmt/mpl/algorithm/fill.hpp>

#include <utility>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace km = kmt::mpl;


BOOST_MPL_ASSERT(( boost::is_same<
	km::fill<std::pair<char, char>, int>::type, std::pair<int, int> 
> ));

BOOST_MPL_ASSERT(( boost::is_same<
	km::fill2<std::pair, int>::type, std::pair<int, int> 
> ));


int
test_main(int argc, char* argv[]){
	
	return 0;
}


