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

#include <kmt/mpl/algorithm/all_of.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/placeholders.hpp>

namespace km = kmt::mpl;
namespace mpl = boost::mpl;

typedef boost::is_same<mpl::_1, int> is_int;

BOOST_MPL_ASSERT((
	km::all_of<mpl::vector<int, int, int>, is_int>
));

BOOST_MPL_ASSERT_NOT((
	km::all_of<mpl::vector<char, double, float>, is_int>
));

BOOST_MPL_ASSERT_NOT((
	km::all_of<mpl::vector<int, int, float>, is_int>
));

BOOST_MPL_ASSERT_NOT((
	km::all_of<
		mpl::range_c<int, 1, 10>,
		mpl::equal_to<mpl::_, mpl::int_<1> >
	>
));

BOOST_MPL_ASSERT((
	km::all_of<
		mpl::vector<>, is_int
	>
));


int
test_main(int argc, char* argv[]){
	
	return 0;
}


