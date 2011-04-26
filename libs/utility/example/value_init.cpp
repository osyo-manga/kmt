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
#include <kmt/utility/value_init.hpp>

#include <iostream>
#include <string>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/string.hpp>

namespace mpl = boost::mpl;

template<typename T1, typename T2>
struct divides : mpl::divides<T1, T2>{
	template<typename T>
	operator T() const{
		return static_cast<T>(static_cast<T>(T1::value) / static_cast<T>(T2::value));
	}
};
typedef divides<mpl::int_<355>, mpl::int_<113> > PI;

// struct PI{
// 	operator float() const{
// 		return 3.14f;
// 	}
// };
 
template<typename Seq>
struct c_str : mpl::c_str<Seq>{
	typedef typename Seq::value_type const* value_type;
	operator value_type() const{
		return mpl::c_str<Seq>::value;
	};
};

struct init_hello_world{
	typedef std::string value_type;
	operator value_type() const{
		return "hello world";
	}
};


struct check{
	kmt::initialized<int>              value1;
	kmt::initialized<mpl::int_<10> >   value2;
	kmt::initialized<mpl::true_>       value3;
	kmt::initialized<float, PI>        value4;
	kmt::initialized<init_hello_world> value5;
	kmt::initialized<
		std::string, c_str<mpl::string<'piyo'> > 
	> value6;
};


int
main(){
	check c;
	
	std::cout << c.value1 << std::endl;
	std::cout << c.value2 << std::endl;
	std::cout << c.value3 << std::endl;
	std::cout << c.value4 << std::endl;
	std::cout << c.value5.data() << std::endl;
	std::cout << c.value6.data() << std::endl;
	
	
	return 0;
}
