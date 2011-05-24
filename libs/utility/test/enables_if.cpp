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

#include <kmt/utility/enables_if.hpp>

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/always.hpp>
#include <string>
#include <iostream>


namespace mpl = boost::mpl;

using mpl::_1;

typedef mpl::vector<
	boost::is_same<int, _1>,
	boost::is_integral<_1>,
	boost::is_class<_1>,
	mpl::always<mpl::true_>
> enables;

template<typename T>
std::string
test(T t, typename kmt::enables_if<enables, mpl::int_<0>, T>::type* =0){
	return "int";
}

template<typename T>
std::string
test(T t, typename kmt::enables_if<enables, mpl::int_<1>, T>::type* =0){
	return "long";
}

template<typename T>
std::string
test(T t, typename kmt::enables_if<enables, mpl::int_<2>, T>::type* =0){
	return "class";
}

template<typename T>
std::string
test(T t, typename kmt::enables_if<enables, mpl::int_<3>, T>::type* =0){
	return "other";
}


#include <boost/type_traits/is_pod.hpp>

typedef mpl::vector<
	boost::is_integral<_1>,
	boost::is_pod<_1>
> enables2;

template<typename T>
void
test2(T t, typename kmt::enables_if<enables2, mpl::int_<0>, T>::type* =0){
	
}

template<typename T>
void
test2(T t, typename kmt::enables_if<enables2, mpl::int_<1>, T>::type* =0){
	
}


struct foo{};


int
test_main(int argc, char* argv[]){
	
	BOOST_CHECK(test(0) == "int");
	BOOST_CHECK(test(long(100)) == "long");
	BOOST_CHECK(test(std::string("str")) == "class");
	BOOST_CHECK(test(0.0f) == "other");
	
	test2(10);
	test2(foo());
	return 0;
}


