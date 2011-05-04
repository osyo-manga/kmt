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
#include <kmt/switch_case/include/switch_case.hpp>
#include <kmt/switch_case/include/lambda_adaptor.hpp>

#include <boost/lambda/lambda.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include <iostream>

/*
[output]
-5:is minus
-4:is minus
-3:is minus
-2:is minus
-1:is minus
0:is even
1:is odd
2:is even
3:is odd
4:is even
5:is odd
6:is even
7:is odd
8:is even
9:is odd
*/

int
main(){
	
	namespace sc = kmt::switch_case;
	using boost::lambda::_1;
	
	boost::for_each(boost::irange(-5, 10),
		  sc::case_pred(_1 < 0)     |std::cout << _1 << ":is minus\n"
		|=sc::case_pred(_1 % 2 == 0)|std::cout << _1 << ":is even\n" 
		|=sc::case_pred(_1 % 2 != 0)|std::cout << _1 << ":is odd\n"
		|=sc::default_              |std::cout << _1 << ":is ???\n"
	);
	
	return 0;
}

