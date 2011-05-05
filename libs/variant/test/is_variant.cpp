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

#include <kmt/variant/is_variant.hpp>

#include <boost/mpl/assert.hpp>

BOOST_MPL_ASSERT((
	kmt::is_variant<boost::variant<int, float, char> >
));

BOOST_MPL_ASSERT((
	kmt::is_variant<boost::variant<int, boost::variant<int, float> > >
));

BOOST_MPL_ASSERT_NOT((
	kmt::is_variant<void*>
));

BOOST_MPL_ASSERT_NOT((
	kmt::is_variant<int>
));


int
test_main(int argc, char* argv[]){
	
	return 0;
}


