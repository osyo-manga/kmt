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
#include <kmt/switch_case/include/var.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <iostream>


namespace sc = kmt::switch_case;


std::string
fizz_buzz(int n){
	using sc::_;
	using boost::make_tuple;
	return sc::switch_(make_tuple(n%3, n%5))
		|=sc::case_(make_tuple(0, 0))|sc::var(std::string("fizz_buzz"))
		|=sc::case_(make_tuple(0, _))|sc::var(std::string("fizz"))
		|=sc::case_(make_tuple(_, 0))|sc::var(std::string("buzz"))
		|=sc::default_               |sc::var(boost::lexical_cast<std::string>(n));
}


int
main(){
	for(int i = 1 ; i < 50 ; i++){
		std::cout << i << ":" << fizz_buzz(i) << std::endl;
	}
	return 0;
}

/*
[output]
1:1
2:2
3:fizz
4:4
5:buzz
6:fizz
7:7
8:8
9:fizz
10:buzz
11:11
12:fizz
13:13
14:14
15:fizz_buzz
16:16
17:17
18:fizz
19:19
20:buzz
21:fizz
22:22
23:23
24:fizz
25:buzz
26:26
27:fizz
28:28
29:29
30:fizz_buzz
31:31
32:32
33:fizz
34:34
35:buzz
36:fizz
37:37
38:38
39:fizz
40:buzz
41:41
42:fizz
43:43
44:44
45:fizz_buzz
46:46
47:47
48:fizz
49:49
*/
