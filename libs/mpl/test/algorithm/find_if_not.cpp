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

#include <kmt/mpl/algorithm/find_if_not.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/modulus.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/print.hpp>

namespace km = kmt::mpl;
namespace mpl = boost::mpl;

typedef boost::is_same<int, mpl::_> is_int;
typedef mpl::equal_to<
	mpl::modulus<mpl::_1, mpl::int_<2> >,
	mpl::int_<0>
> is_even;


BOOST_MPL_ASSERT(( boost::is_same<
	mpl::deref<km::find_if_not<mpl::vector<int, int, char, int, float>, is_int>::type>::type,
	char
> ));

BOOST_MPL_ASSERT(( boost::is_same<
	km::find_if_not<mpl::vector<int, int, char, int, float>, is_int>::type,
	mpl::find_if   <mpl::vector<int, int, char, int, float>, mpl::not_<is_int> >::type
> ));

BOOST_MPL_ASSERT(( boost::is_same<
	km::find_if_not<mpl::vector<int, int, int>, is_int>::type,
	mpl::end<mpl::vector<int, int, int> >::type
> ));

BOOST_MPL_ASSERT(( boost::is_same<
	km::find_if_not<mpl::vector<int, int, int>, is_int>::type,
	mpl::end<mpl::vector<int, int, int> >::type
> ));

BOOST_MPL_ASSERT(( mpl::equal_to<
	mpl::deref<km::find_if_not<mpl::vector_c<int, 2, 4, 5, 6>, is_even>::type>::type,
	mpl::int_<5>
> ));

BOOST_MPL_ASSERT(( boost::is_same<
	km::find_if_not<mpl::vector<>, is_int>::type,
	mpl::end<mpl::vector<> >::type
> ));


int
test_main(int argc, char* argv[]){
	
	return 0;
}


