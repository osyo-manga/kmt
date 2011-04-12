#include <iostream>
#include <boost/tuple/tuple_io.hpp>
#include <kmt/switch_case.hpp>

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>

#include <boost/mpl/print.hpp>
#include <boost/variant.hpp>

namespace sc = kmt::switch_case;

template<typename T>
void
hoge(T t){
	using boost::mpl::print;
//	typedef typename print<T>::type Ttype;
}

void
test(){
	using sc::var;
	using sc::switch_;
	using sc::case_;
	hoge(case_(0)|=case_(1)|var(1) );
//	switch_(0)|=case_(0)|=case_(1)|=case_(2);
	int n = switch_(0)
		|=case_(0)
		|=case_(1)|var(1);
	std::cout << n << std::endl;
}

template<typename T>
void
test2(const T& t){
	using sc::var;
	using sc::switch_;
	using sc::case_;
	using sc::default_;
	std::string result;
	result = switch_(t)
		|=case_<std::string>()&std::string("string")
		|=case_<int>()&std::string("int")
		|=default_&std::string("no match");
	std::cout << result << std::endl;
}


void
fizz_buzz(int n){
	using sc::_;
	
	std::string result = sc::switch_(n%3, n%5)
		|=sc::case_(0,0)|sc::var(std::string("fizz_buzz"))
		|=sc::case_(0,_)&(std::string("fizz"))
		|=sc::case_(_,0)&(std::string("buzz"))
		|=sc::default_&(boost::lexical_cast<std::string>(n));
	std::cout << result << std::endl;
}


int
main(){
	
	test();
	test2(std::string(""));
	test2(0);
	test2(0.0f);
	std::string hoge;
	test2(hoge);
	
	std::string input = "yes";
	std::string result
	= sc::switch_(input)
		|=sc::case_(std::string("yes"))
		|=sc::case_(std::string("y"))
		|=sc::case_(std::string("Y"))|sc::var(std::string("ok"))
		|=sc::default_|sc::var(std::string("error"));
	std::cout << result << std::endl;
	
	for(int i = 1 ; i < 20 ; ++i){
		fizz_buzz(i);
	}
	
	return 0;
}
