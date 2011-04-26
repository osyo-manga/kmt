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

#include <kmt/mpl/is_only_one.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/assert.hpp>

namespace kmt { namespace mpl { using namespace boost::mpl; }}
namespace mpl = kmt::mpl;

typedef mpl::vector<int, char, float, int, char> seq;

BOOST_MPL_ASSERT(( 
	mpl::is_only_one<seq, float>::type
));

BOOST_MPL_ASSERT_NOT((
	mpl::is_only_one<seq, int>::type
));

int
test_main(int argc, char* argv[]){
	
	return 0;
}

