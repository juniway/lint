template<typename T>
class StackWithMin{
public:
	StackWithMin(){}
	virtual ~StackWithMin(){}

	T& top();
	const T& top() const;

	void push(const T& value);
	void pop();

	const T& min() const;

	bool empty() const;
	size_t size() const;
private:
	std::stack<T> m_st_main;
	std::stack<T> m_st_helper;
};



template<typename T>
void StackWithMin<T>::push(const T& value){
	m_st_main.push(value);

	if(m_st_helper.size() == 0 || value < m_st_helper.top()){
		m_st_helper.push(value);
	}
	else{
		m_st_helper.push(m_st_helper.top());
	}
}

template<typename T>
void StackWithMin<T>::pop(){
	if((m_st_main.size() > 0 && m_st_helper.size() > 0)){
		m_st_main.pop();
		m_st_helper.pop();
	}
}


template<typename T>
const T& StackWithMin<T>::min() const{
	if(m_st_main.size() > 0 && m_st_helper.size() > 0);
	return m_st_helper.top();
}

template<typename T>
T& StackWithMin<T>::top(){
	return m_st_main.top();
}

template<typename T>
const T& StackWithMin<T>::top(){
	return m_st_main.top();
}

template<typename T>
bool StackWithMin<T>::empty(){
	return m_st_main.empty();
}

template<typename T>
size_t StackWithMin<T>::size() const{
	return m_st_main.size();
}