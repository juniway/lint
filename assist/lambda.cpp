// lambda.cpp

// Anonymous / lambda functions

int main(){
	auto double_n = [](double x){return x*2;}
	std::cout<<double_n(50) << std::endl; //100
}

// double_n is a funciton pointer pointing to an anonymous function.

// if we want to , we can also make some or all variables from the 
// local scope available to the function.

int main(){
	int sum = 0;
	auto running_sum = [&sum](int x){sum += x;}
	running_sum(1);
	running_sum(2);
	running_sum(3); // sum is now 1+2+3 = 6
}

// ambda is a powful tool, for example, we want the sum of the 
// variables in an array or any other container or just print it

int arr[] = {1, 2, 3, 4, 5};
int sum = 0;
std::for_each(std::begin(arr), std::end(arr), [&sum](int x){sum += x;});
std::for_each(std::begin(arr), std::end(arr), [](int x){std::cout<<x<<' ';});



