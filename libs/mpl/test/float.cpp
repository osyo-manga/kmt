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

#define BOOST_RATIO_EXTENSIONS
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/ratio/mpl/plus.hpp>
#include <boost/ratio/mpl/equal_to.hpp>

#include <kmt/mpl/float.hpp>

namespace mpl = boost::mpl;
namespace km  = kmt::mpl;


BOOST_MPL_ASSERT(( mpl::equal_to<
	km::float_<123,456>,
	boost::ratio<123456, 1000>
> ));

BOOST_MPL_ASSERT(( mpl::equal_to<
	km::float_<0,123>,
	boost::ratio<123, 1000>
> ));

BOOST_MPL_ASSERT(( mpl::equal_to<
	km::float_<10,0>,
	mpl::int_<10>
> ));

BOOST_MPL_ASSERT(( mpl::equal_to<
	mpl::plus<km::float_<0,5>, km::float_<0,5> >,
	mpl::int_<1>
> ));


int
test_main(int argc, char* argv[]){
	
	return 0;
}


