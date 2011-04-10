#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/lambda/lambda.hpp>
#include <kmt/switch_case.hpp>

namespace sc = kmt::switch_case;


std::string
check(int n){
	return sc::switch_(n%2==0)
		|=sc::case_(true , sc::var(std::string("偶数")))
		|=sc::case_(false, sc::var(std::string("奇数")));
}

void
fizz_buzz(int n){
	using boost::lambda::constant;
	using sc::_;
	
	sc::switch_(n%3, n%5)
		|=sc::case_(0,0, std::cout << constant("fizz_buzz") << ",")
		|=sc::case_(0,_, std::cout << constant("fizz") << ",")
		|=sc::case_(_,0, std::cout << constant("buzz") << ",")
		|=sc::default_(std::cout << constant(boost::lexical_cast<std::string>(n)) << ",");
}

void
dog(){
	std::cout << "わんわんお！" << std::endl;
}
void
cat(){
	std::cout << "にゃーにゃー。" << std::endl;
}
void
qb(){
	std::cout << "僕と契約して魔法少女になってよ！！" << std::endl;
}

void
say(std::string s){
	sc::switch_(s)
		|=sc::case_(std::string("Dog"), &dog)
		|=sc::case_(std::string("Cat"), &cat)
		|=sc::case_(std::string("QB"),  &qb);
}

#include <assert.h>

int
main(){
	say("Dog");
	say("Cat");
	say("QB");

	for( int i = 0 ; i < 10 ; i++ ){
		std::cout << check(i);
	}
	std::cout << std::endl;
	for( int i = 1 ; i < 20 ; i++ ){
		fizz_buzz(i);
	}
	
	using namespace sc;
	std::string result = switch_(std::string("Cat"))
		|=case_(std::string("Dog"), var(std::string("わんわんお！")))
		|=case_(std::string("Cat"), var(std::string("にゃーにゃー")))
		|=case_(std::string("QB"), var(std::string("僕と契約してry")));
	assert( result == "にゃーにゃー" );
	
	
	return 0;
}


#if 0
using namespace switch_case;

void
func(int n){
	std::string result;
	result =
	switch_(n%2==0)
		|=case_(true , var(std::string("偶数")))
		|=case_(false, var(std::string("奇数")));
//		|=case_(true , boost::lambda::constant(std::string("偶数")))
//		|=case_(false, boost::lambda::constant(std::string("奇数")));
	std::cout << result << std::endl;
}

/*
std::string
fizz_buzz(int n){
	std::string str = boost::lexical_cast<std::string>(n);
	return switch_(n%3, n%5)
		|=case_(0,0, std::string("fizz_buzz"))
		|=case_(0,_, std::string("fizz"))
		|=case_(_,0, std::string("buzz"))
		|=default_(boost::lexical_cast<std::string>(n));
}
*/

void
disp_fizz_buzz(int n){
	using boost::lambda::var;
	using boost::lambda::constant;
	
	switch_(n%3, n%5)
		|=case_(0,0, std::cout << constant("fizz_buzz"))
		|=case_(0,_, std::cout << constant("fizz"))
		|=case_(_,0, std::cout << constant("buzz"))
		|=default_(std::cout << constant(boost::lexical_cast<std::string>(n)));
/*
	switch_(n%3, n%5)
		|=case_(0,0, []{ std::cout << "fizz_buzz" << std::endl; })
		|=case_(0,_, []{ std::cout << "fizz" << std::endl; })
		|=case_(_,0, []{ std::cout << "buzz" << std::endl; })
		|=default_([&]{  std::cout << n << std::endl; });
*/
}


struct hoge{
	typedef void result_type;
	void operator()(){
		value = 10;
	}
	hoge() : value(0){}
	int value;
};


int
main(){
	
	hoge h;
	switch_(10)
		|=case_(10, h);
	std::cout << h.value << std::endl;
	

	int n1 = 0;
	int n2 = 0;
	(switch_(2)
		|=case_(1, var(n1))
		|=case_(2, var(n2))) = 10;
	
	std::cout << n1 << std::endl;
	std::cout << n2 << std::endl;


	
	func(0);
	func(1);
	
	for( int i = 1 ; i < 20 ; i++ ){
//		std::cout << fizz_buzz(i) << ",";
	}
	for( int i = 1 ; i < 20 ; i++ ){
		disp_fizz_buzz(i);
	}
	
	return 0;
}

#endif


