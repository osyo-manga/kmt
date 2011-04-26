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

#include <kmt/mpl/slice.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>

namespace kmt{ namespace mpl{
	using namespace boost::mpl;
} }
namespace mpl = kmt::mpl;

typedef mpl::vector<char, int, float, double, void> seq;

BOOST_MPL_ASSERT(( mpl::equal<
	mpl::slice_c<seq, 1, 4>::type,
	mpl::vector<int, float, double>
> ));


int
test_main(int argc, char* argv[]){
	
	return 0;
}

