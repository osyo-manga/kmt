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


BOOST_MPL_ASSERT((
	km::all_of<mpl::vector<int, int, int>, int>
));

BOOST_MPL_ASSERT_NOT((
	km::all_of<mpl::vector<int, int, float>, int>
));

BOOST_MPL_ASSERT_NOT((
	km::all_of_if<
		mpl::range_c<int, 1, 10>,
		mpl::equal_to<mpl::_, mpl::int_<1> >
	>
));

BOOST_MPL_ASSERT_NOT((
	km::all_of<
		mpl::vector_c<int, 1, 1, 1>, mpl::int_<1>
	>
));

int
test_main(int argc, char* argv[]){
	
	return 0;
}


