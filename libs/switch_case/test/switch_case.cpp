#include <kmt/switch_case/include/switch_case.hpp>
#include <kmt/switch_case/include/case_fused.hpp>
#include <kmt/switch_case/include/case_type.hpp>
#include <kmt/switch_case/include/var.hpp>
#include <kmt/switch_case/include/case_variant.hpp>
#include <kmt/switch_case/include/returnable_switch.hpp>

#include <iostream>
#include <string>

#include <boost/variant/variant.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/make_fused.hpp>

namespace sc = kmt::switch_case;

/*
#include <boost/mpl/print.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/print.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/remove.hpp>
#include <boost/mpl/vector.hpp>

template<typename T, typename Seq = boost::mpl::vector<> >
struct result{
	typedef typename boost::mpl::push_back<
		typename result<typename T::next_type, Seq>::type0,
		typename T::result_type
	>::type type0;
	typedef typename boost::mpl::unique<
		type0, 
		boost::is_same<boost::mpl::_1, boost::mpl::_2>
	>::type type1;
	typedef typename boost::mpl::remove<type1, void>::type type;
};

template<typename Seq>
struct result<sc::detail::empty_case, Seq>{
	typedef Seq type0;
};
*/

struct disp{
	typedef void result_type;
	disp(std::string const& str) : str_(str){}
	void operator()() const{
		std::cout << str_ << std::endl;
	}
private:
	std::string str_;
};

template<typename T>
void
test2(T t){
	sc::switch_(t)
		|=sc::case_type<int>()        |disp("int")
		|=sc::case_type<std::string>()|disp("string")
		|=sc::case_type<float>()      |disp("float")
		|=sc::default_|disp("other type");
}

std::string
test3(std::string input){
	std::string result
	= sc::switch_(input)
		|=sc::case_(std::string("yes"))
		|=sc::case_(std::string("y"))
		|=sc::case_(std::string("Y"))|sc::var(std::string("ok"))
		|=sc::default_|sc::var(std::string("error"));
	return result;
}


void
fizz_buzz(int n){
	using sc::_;
	using boost::fusion::make_vector;
	using boost::lambda::_1;
	using boost::lambda::_2;
	
	boost::variant<int, std::string> result
	= sc::returnable_switch<boost::variant<int, std::string>>(make_vector(n%3, n%5))
		|=sc::case_fused(_1 == 0 && _2 == 0)|sc::var(std::string("fizz_buzz"))
		|=sc::case_fused(_1 == 0)           |sc::var(std::string("fizz"))
		|=sc::case_fused(_2 == 0)           |sc::var(std::string("buzz"))
		|=sc::default_|sc::var(n);
//		|=sc::default_|sc::var(boost::lexical_cast<std::string>(n));
	std::cout << result << std::endl;
}

void
test4(boost::variant<int, float, char, std::string> var){
	sc::switch_(var)
		|=sc::case_variant<int>()  |disp("int")
		|=sc::case_variant<float>()|disp("float")
		|=sc::default_|disp("other type");
}

void
test5(){
	auto v = sc::returnable_switch<boost::variant<int, std::string> >(20)
		|=sc::case_(10)|sc::var(10)
		|=sc::case_(20)|sc::var(std::string("hoge"));
	std::cout << v << std::endl;
}

void
run(){
	using sc::case_;
	sc::switch_(1)
		|=case_(0)
		|=case_(1)|disp("test")|disp("hogehoge")
		|=case_(2)|disp("test2");
	sc::switch_(0)|=case_(0);
	sc::switch_(0)|=case_(0)|disp("test");
	
	try{
		sc::switch_(1)|=case_(0)|disp("no exp");
		sc::switch_(1)|=case_(0)|sc::var(std::string("hoge"));
	}
	catch(std::exception& exp){
		std::cout << "exp :" << exp.what() << std::endl;
	}

	std::cout << test3("yes") << std::endl;
	std::cout << test3("no") << std::endl;
	test2(10);
	test2(3.14f);
	test2(std::string("hoge"));
	test2(long(10));
	
	for(int i = 1 ; i < 20 ; ++i){
		fizz_buzz(i);
	}
	
	test4('c');
	test4(10);
	test4(3.14f);
	test4(std::string("hogehoge"));
	
	test5();

}

int
main(){
	run();
	
	return 0;
}
