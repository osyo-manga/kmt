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

#include <kmt/mpl/c_array.hpp>

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/range/algorithm/equal.hpp>

#include <vector>


namespace mpl = boost::mpl;
namespace km  = kmt::mpl;

typedef mpl::vector_c<int, 3, 5, 2, 1, 4> seq;

BOOST_MPL_ASSERT(( boost::is_same<
	km::c_array<seq>::value_type,
	boost::array<int, 5>
> ));

BOOST_MPL_ASSERT(( boost::is_same<
	km::c_array<seq, std::vector<mpl::_1> >::value_type,
	std::vector<int>
> ));


int
test_main(int argc, char* argv[]){
	
	BOOST_CHECK(( boost::equal(
		km::c_array<mpl::vector_c<int, 0, 1, 2, 3, 4> >::value,
		km::c_array<mpl::range_c<int, 0, 5> >::value
	) ));
	\
	boost::array<int, 5> array = {{ 3, 5, 2, 1, 4 }};
	BOOST_CHECK(( boost::equal(
		array, km::c_array<seq>::value
	) ));
	
	return 0;
}

