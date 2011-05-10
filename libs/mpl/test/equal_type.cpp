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
#include <kmt/mpl/equal_type.hpp>

#include <boost/mpl/assert.hpp>

namespace km  = kmt::mpl;
namespace mpl = boost::mpl;


BOOST_MPL_ASSERT(( km::equal_type<int, int> ));

BOOST_MPL_ASSERT(( km::equal_type<mpl::identity<int>, int> ));
BOOST_MPL_ASSERT(( km::equal_type<int, mpl::identity<int> > ));
BOOST_MPL_ASSERT(( km::equal_type<mpl::identity<int>, mpl::identity<int> > ));

int
test_main(int argc, char* argv[]){
	
	return 0;
}


