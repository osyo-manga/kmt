#include <kmt/switch_case.hpp>

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>

namespace sc = kmt::switch_case;

template<typename T>
void
check(const T& t){
	std::string result;
	result = sc::switch_(t)
		|=sc::case_<std::string>()&std::string("string")
		|=sc::case_<int>()&std::string("int")
		|=sc::default_&std::string("no match");
	std::cout << result << std::endl;
}

void
fizz_buzz(int n){
	using sc::_;
	std::string result
	= sc::switch_(n%3, n%5)
		|=sc::case_(0,0)|sc::var(std::string("fizz_buzz"))
		|=sc::case_(0,_)|sc::var(std::string("fizz"))
		|=sc::case_(_,0)&(std::string("buzz"))
		|=sc::default_&(boost::lexical_cast<std::string>(n));
	std::cout << result << ",";
}

int
main(){
	
	std::string input = "yes";
	std::string result
	= sc::switch_(input)
		|=sc::case_(std::string("yes"))
		|=sc::case_(std::string("y"))
		|=sc::case_(std::string("Y"))|sc::var(std::string("ok"))
		|=sc::default_&std::string("error");
	std::cout << result << std::endl;
	
	// 型によるパターンマッチ
	check(std::string(""));
	check(0);
	check(0.0f);

	// fizz buzz
	for(int i = 1 ; i < 20 ; ++i){
		fizz_buzz(i);
	}
	std::cout << std::endl;
	
	return 0;
}
