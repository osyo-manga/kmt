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

#include <kmt/mpl/is_only_one_if.hpp>

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/assert.hpp>


namespace mpl = boost::mpl;
namespace km  = kmt::mpl;

typedef mpl::vector_c<int, 1, 2, 1, 2, 3> seq;

BOOST_MPL_ASSERT(( 
	km::is_only_one_if<
		seq,
		mpl::equal_to<mpl::_1, mpl::int_<3> >
	>::type
));

BOOST_MPL_ASSERT_NOT(( 
	km::is_only_one_if<
		seq,
		mpl::equal_to<mpl::_1, mpl::int_<1> >
	>::type
));

int
test_main(int argc, char* argv[]){
	
	return 0;
}


