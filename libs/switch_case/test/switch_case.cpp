#include <iostream>
#include <boost/tuple/tuple_io.hpp>
#include <kmt/switch_case.hpp>

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>

#include <boost/mpl/print.hpp>
#include <boost/variant.hpp>

#include <boost/mpl/print.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/remove.hpp>
#include <boost/mpl/vector.hpp>


namespace sc = kmt::switch_case;

/*
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

template<typename T>
void
hoge(T t){
	using boost::mpl::print;
///	typedef typename print<T>::type Ttype;
}

struct disp{
	typedef void result_type;
	disp(std::string str) : str_(str){}
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
		|=sc::case_type<int>()|disp("int")
		|=sc::case_type<std::string>()|disp("string")
		|=sc::case_type<float>()|disp("float")
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
test(){
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
/*
	int n = switch_(0)
		|=case_(0)
		|=case_(1)|var(1)
		|=case_(2)
		|=case_(3)&0;
	std::cout << n << std::endl;
*/
	std::cout << test3("yes") << std::endl;
	std::cout << test3("no") << std::endl;
	test2(10);
	test2(3.14f);
	test2(std::string("hoge"));
	test2(long(10));
}

#if 0
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
	
	std::string result
	= sc::switch_(n%3, n%5)
		|=sc::case_(0,0)|sc::var(std::string("fizz_buzz"))
		|=sc::case_(0,_)|sc::var(std::string("fizz"))
		|=sc::case_(_,0)&(std::string("buzz"))
		|=sc::default_&(boost::lexical_cast<std::string>(n));
	std::cout << result << std::endl;
}


#include <boost/lambda/lambda.hpp>

void
fizz_buzz_disp(int n){
	using boost::lambda::constant;
	using sc::_;

	sc::switch_(n%3, n%5)
		|=sc::case_expr(0,0, std::cout << constant(std::string("fizz_buzz")) << "\n")
		|=sc::case_expr(0,_, std::cout << constant(std::string("fizz")) << "\n")
		|=sc::case_expr(_,0, std::cout << constant(std::string("buzz")) << "\n")
		|=sc::default_expr(std::cout << constant(boost::lexical_cast<std::string>(n)) << "\n");
}

void
run(){
		test();
	test2(std::string(""));
	test2(0);
	test2(0.0f);
	std::string hoge;
	test2(hoge);
	tese3();
	
	for(int i = 1 ; i < 20 ; ++i){
		fizz_buzz(i);
		fizz_buzz_disp(i);
	}
	try{
		sc::switch_(0)
			|=sc::case_(1)&10;
	}
	catch(std::exception& exp){
		std::cout << exp.what() << std::endl;
	}
}
#endif

int
main(){
	test();
//	run();
	
	return 0;
}
