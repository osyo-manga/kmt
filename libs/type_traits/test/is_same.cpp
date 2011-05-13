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

#include <kmt/type_traits/is_same.hpp>


#include <vector>
#include <string>
#include <map>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/variant/variant.hpp>
#include <kmt/mpl/algorithm/fill.hpp>


namespace mpl = boost::mpl;
using kmt::is_same;
using kmt::_;
using kmt::mpl::fill;

BOOST_MPL_ASSERT((
	is_same<int, int>
));

BOOST_MPL_ASSERT_NOT((
	is_same<int, int&>
));

BOOST_MPL_ASSERT(( is_same<
	std::vector<_>,
	std::vector<int>
> ));

BOOST_MPL_ASSERT_NOT(( is_same<
	std::vector<_>,
	int
> ));


template<typename T>
struct is_string
	: is_same<std::basic_string<_>, T>{};

BOOST_MPL_ASSERT((
	is_string< std::string >
));

BOOST_MPL_ASSERT((
	is_string< std::wstring >
));

BOOST_MPL_ASSERT_NOT((
	is_string< char const* >
));


template<typename T>
struct is_map_key_int
	: is_same<std::map<int, _>, T>{};

BOOST_MPL_ASSERT((
	is_map_key_int< std::map<int, std::string> >
));

BOOST_MPL_ASSERT_NOT((
	is_map_key_int< std::map<std::string, int> >
));


BOOST_MPL_ASSERT(( is_same<
	std::pair<std::pair<int, _>, std::pair<_, std::string> >,
	std::pair<std::pair<int, std::string>, std::pair<int, std::string> >
> ));

BOOST_MPL_ASSERT_NOT(( is_same<
	std::pair<std::pair<int, _>, std::pair<_, std::string> >,
	std::pair<std::pair<std::string, int>, std::pair<std::string, int> >
> ));

BOOST_MPL_ASSERT(( is_same<
	fill<boost::variant<>, _>::type,
	boost::variant<int, float, char>
> ));

BOOST_MPL_ASSERT(( is_same<
	fill<boost::tuple<>, _>::type,
	boost::tuple<int, float, char>
> ));

template<typename T>
struct is_tuple
	: is_same<fill<boost::tuple<>, _>::type, T>{};

BOOST_MPL_ASSERT(( is_tuple<boost::tuple<int, char, float> > ));

BOOST_MPL_ASSERT(( is_same<
	boost::tuple<int, _, char>,
	boost::tuple<int, float, char>
> ));

BOOST_MPL_ASSERT_NOT(( is_same<
	boost::tuple<int, _, char>,
	boost::tuple<int, float, int>
> ));



int
test_main(int argc, char* argv[]){
	
	return 0;
}


