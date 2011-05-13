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

#include <kmt/mpl/template_sequence.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/if.hpp>
#include <vector>
#include <utility>


template<typename T>
struct template_args : kmt::mpl::template_sequence<T, boost::mpl::vector<> >{};

namespace mpl = boost::mpl;

template<typename T, typename U>
struct hoge{};

BOOST_MPL_ASSERT(( mpl::equal<
	template_args<hoge<int, float> >,
	mpl::vector<int, float>
> ));

BOOST_MPL_ASSERT(( mpl::equal<
	template_args<std::pair<int, float> >,
	mpl::vector<int, float>
> ));

BOOST_MPL_ASSERT(( mpl::equal<
	template_args<std::pair<int, float> >,
	template_args<hoge<int, float> >
> ));


int
test_main(int argc, char* argv[]){
	
	return 0;
}
