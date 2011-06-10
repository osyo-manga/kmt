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
#include <kmt/mpl/c_array.hpp>
#include <kmt/utility/value_init.hpp>

#include <boost/mpl/range_c.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/lambda/lambda.hpp>
#include <vector>

namespace mpl = boost::mpl;
namespace km  = kmt::mpl;


struct hoge{
	// コンストラクタ時に配列の初期化
	hoge() : value(
		km::c_array<mpl::vector_c<int, 2, 4, 1, 3, 0> >::value
	){}
	boost::array<int, 5> value;
};

struct foo{
	// initialized の初期化として使用する。
	kmt::initialized<boost::array<int, 5>,
		km::c_array<mpl::range_c<int, 0, 5> > > value;
};

int
main(){
	// コンパイル定数で、配列の初期化
	boost::array<int, 10> const& array = km::c_array<mpl::range_c<int, 0, 10> >::value;
	boost::for_each(array, std::cout << boost::lambda::_1 << ",");
	std::cout << std::endl;
	
	// 配列型を指定する
	std::vector<int> const& array2
		= km::c_array<mpl::range_c<int, 0, 10>, std::vector<mpl::_> >::value;
	boost::for_each(array2, std::cout << boost::lambda::_1 << ",");
	std::cout << std::endl;
	
	hoge a;
	boost::for_each(a.value, std::cout << boost::lambda::_1 << ",");
	std::cout << std::endl;
	
	foo b;
	boost::for_each(b.value.data(), std::cout << boost::lambda::_1 << ",");
	
	return 0;
}
