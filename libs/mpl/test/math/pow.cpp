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

#include <kmt/mpl/math/pow.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/int.hpp>

namespace mpl = boost::mpl;
namespace km  = kmt::mpl;

BOOST_MPL_ASSERT(( mpl::equal_to<
	km::pow<mpl::int_<2>, mpl::int_<3> >,
	mpl::int_<8>
> ));

BOOST_MPL_ASSERT(( mpl::equal_to<
	km::pow<mpl::int_<0>, mpl::int_<3> >,
	mpl::int_<0>
> ));

BOOST_MPL_ASSERT(( mpl::equal_to<
	km::pow<mpl::int_<2>, mpl::int_<0> >,
	mpl::int_<1>
> ));

BOOST_MPL_ASSERT(( mpl::equal_to<
	km::pow<mpl::int_<2>, mpl::int_<3> >,
	mpl::int_<8>
> ));

BOOST_MPL_ASSERT(( mpl::equal_to<
	km::pow_c<5, 3>,
	mpl::int_<125>
> ));

BOOST_MPL_ASSERT(( mpl::equal_to<
	km::pow_c<5, 3>,
	mpl::int_<125>
> ));



int
test_main(int argc, char* argv[]){
	
	return 0;
}


