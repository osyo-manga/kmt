//
// kmt-library
//
// Copyright (c) 2011 
// osyo-manga : http://d.hatena.ne.jp/osyo-manga/
// 
// Readme:
// https://github.com/osyo-manga/kmt/blob/master/README
//
// License:
// Boost Software License - Version 1.0
// <http://www.boost.org/LICENSE_1_0.txt>
//
//#include <kmt/mpl/variadic_sequence.hpp>

#include <kmt/mpl/variadic_vector.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/push_back.hpp>

namespace km  = kmt::mpl;
namespace mpl = boost::mpl;

typedef km::variadic_vector<int, char, double> seq;


BOOST_MPL_ASSERT(( boost::mpl::equal<
	seq,
	boost::mpl::vector<int, char, double>
> ));

BOOST_MPL_ASSERT(( mpl::equal<
	mpl::push_back<seq, float>::type,
	mpl::vector<int, char, double, float>
> ));


// Boost.Fusion
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/push_front.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <utility>

namespace fusion = boost::fusion;


template<typename ...Args>
struct variadic_fusion_vector :
	fusion::result_of::as_vector<
		km::variadic_sequence<
			fusion::vector1<mpl::_1>,
			fusion::result_of::push_front<mpl::_1, mpl::_2>,
			Args...
		>
	>::type{
	
	typedef typename fusion::result_of::as_vector<
		km::variadic_sequence<
			fusion::vector1<mpl::_1>,
			fusion::result_of::push_front<mpl::_1, mpl::_2>,
			Args...
		>
	>::type base_type;
	
	template<typename ...UArgs>
	explicit variadic_fusion_vector(UArgs&&... args)
		: base_type(std::forward<UArgs>(args)...){}
};


#include <iostream>
#include <boost/fusion/include/io.hpp>

int
main(){
//	variadic_fusion_vector<int, char, double> v(1, 'a', 3.14);
//	std::cout << v << std::endl;
	return 0;
}



