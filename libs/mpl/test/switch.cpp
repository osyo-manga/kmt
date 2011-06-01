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

#include <kmt/mpl/switch.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits.hpp>

namespace mpl = boost::mpl;
namespace km  = kmt::mpl;
using mpl::_;

typedef mpl::vector<
	km::case_<boost::is_pointer<_>,   boost::remove_pointer<_> >,
	km::case_<boost::is_reference<_>, boost::remove_reference<_> >,
	km::case_<boost::is_const<_>,	  boost::remove_const<_> >,
	km::case_<boost::is_same<_, void>, boost::add_pointer<_> >,
	km::default_<mpl::identity<_> >
> switch_body;

typedef mpl::switch_<switch_body, int*>::type t1;
typedef mpl::switch_<switch_body, char&>::type t2;
typedef mpl::switch_<switch_body, float const>::type t3;
typedef mpl::switch_<switch_body, void>::type t4;
typedef mpl::switch_<switch_body, int>::type t5;

BOOST_MPL_ASSERT(( boost::is_same<t1, int> ));
BOOST_MPL_ASSERT(( boost::is_same<t2, char> ));
BOOST_MPL_ASSERT(( boost::is_same<t3, float> ));
BOOST_MPL_ASSERT(( boost::is_same<t4, void*> ));
BOOST_MPL_ASSERT(( boost::is_same<t5, int> ));


int
test_main(int argc, char* argv[]){
	
	return 0;
}


