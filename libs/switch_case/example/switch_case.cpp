#include <kmt/switch_case.hpp>

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>


namespace sc = kmt::switch_case;

void
fizz_buzz(int n){
	using sc::_;
	
	std::string result = sc::switch_(n%3, n%5)
		|=sc::case_(0,0, sc::var(std::string("fizz_buzz")))
		|=sc::case_(0,_, sc::var(std::string("fizz")))
		|=sc::case_(_,0, sc::var(std::string("buzz")))
		|=sc::default_(sc::var(boost::lexical_cast<std::string>(n)));
	
	std::cout << result << std::endl;
}
<F12><F11>



int
main(){
	
	
	
	return 0;
}
