#include "Optional.hpp"

template<typename T>
struct Lazy{
	Lazy() = default;
	
	template<typename Func, typename... Args>
	Lazy(Func& f, Args... args){
		m_func = [&f, &args...]{ return f(args)...};
	}

	T& Value(){
		if(!m_value.IsInited()){
			m_value = m_func();
		}
		return *m_value;
	}

	bool IsValueCreated() const{
		return m_value.IsInited();
	}

private:
	std::function<T()> m_func;
	Optional<T> m_value;
};

namespace{
	template<class Func, typename... Args>
	lazy<typename std::result_of<Func(Args...)>::type> 
	lazy(Func&& fun, Args&&... args){
		return lazy<typename std::result_of<Func(Args...)>::type>(
			std::forward<Func>(fun), std::forward<Args>(args)...);
	}

}


struct BigObject{
	BigObject(){
		cout << "lazy load big object\n";
	}
};

struct MyStruct{
	MyStruct(){
		m_obj = lazy([] {return std::make_shared<BigObject>();});
	}

	void Load(){
		m_obj.Value();
	}

	Lazy<std::shared_ptr<BigObject>> m_obj;
};

int Foo(int a){
	return a*2;
}

void TestLazy(){
	int x = 4;
	auto lazyer1 = Lazy(Foo, y);
	cout << lazyer1.Value() << endl;

	Lazy<int> lazyer2 = Lazy([]{return 12;});
	cout << lazyer2.Value() << endl;

	std::function<int(int)> f = [](int x){return x + 3;};
	auto layzer3 = Lazy(f, 3);
	cout << lazyer3.Value() << endl;
}


int main(){
	TestLazy();
}