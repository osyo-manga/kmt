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

#include <kmt/mpl/algorithm/none_of.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/print.hpp>

namespace km = kmt::mpl;
namespace mpl = boost::mpl;

typedef boost::is_same<int, mpl::_> is_int;
typedef mpl::not_<boost::is_same<int, mpl::_> > not_int;
typedef mpl::equal_to<mpl::int_<1>, mpl::_> equal_1;
typedef mpl::not_equal_to<mpl::int_<1>, mpl::_> not_equal_1;

BOOST_MPL_ASSERT((
	km::none_of<mpl::vector<short, char, float>, is_int>
));

BOOST_MPL_ASSERT((
	km::none_of<mpl::vector<int, int, int>, not_int>
));

BOOST_MPL_ASSERT_NOT((
	km::none_of<mpl::vector<int, int, float>, not_int>
));

BOOST_MPL_ASSERT_NOT((
	km::none_of<mpl::vector<int, char, float>, is_int>
));

BOOST_MPL_ASSERT((
	km::none_of<mpl::vector_c<int, 0, 2, 3>, equal_1>
));

BOOST_MPL_ASSERT_NOT((
	km::none_of<mpl::vector_c<int, 1, 2, 3>, not_equal_1>
));

BOOST_MPL_ASSERT((
	km::none_of<mpl::vector<>, not_equal_1>
));



int
test_main(int argc, char* argv[]){
	
	return 0;
}


