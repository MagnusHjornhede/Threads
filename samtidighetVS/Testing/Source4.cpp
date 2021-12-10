class MulPrintString { // A functor class
public:
	void operator()(string str, int n) const {
		for (int i = 0; i < n; ++i)
			std::cout << str << '\n';
	}
};