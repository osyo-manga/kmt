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

#include <kmt/mpl/for_each_with_index.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector.hpp>

namespace mpl = boost::mpl;


template<typename Seq>
struct check{
	template<typename T>
	void operator()(T) const{
		BOOST_MPL_ASSERT(( mpl::equal<
			mpl::at<Seq, T::index>, T::type
		> ));
	}
};

int
test_main(int argc, char* argv[]){
	
	typedef mpl::vector<int, float, char, double> seq;
	
	kmt::mpl::for_each_with_index<seq>(check<seq>());
	
	return 0;
}


