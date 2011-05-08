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

#include <kmt/mpl/algorithm/any_of.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/type_traits/is_same.hpp>

namespace km = kmt::mpl;
namespace mpl = boost::mpl;

typedef boost::is_same<int, mpl::_> is_int;
typedef mpl::equal_to<mpl::int_<1>, mpl::_> equal_1;


BOOST_MPL_ASSERT((
	km::any_of<mpl::vector<int, float, char>, is_int>
));

BOOST_MPL_ASSERT_NOT((
	km::any_of<mpl::vector<short, float, char>, is_int>
));

BOOST_MPL_ASSERT((
	km::any_of<mpl::vector<>, is_int>
));

BOOST_MPL_ASSERT((
	km::any_of<mpl::vector_c<int, 1, 10>, equal_1>
));

BOOST_MPL_ASSERT_NOT((
	km::any_of<mpl::vector_c<int, 2, 10>, equal_1>
));



int
test_main(int argc, char* argv[]){
	
	return 0;
}


