test: json98.cpp json98.h test.cpp
	$(CXX) -O -std=c++11 json98.cpp test.cpp -o test -fno-rtti -fno-exceptions

clean:
	if [ -e test ]; then rm test; fi

.PHONY: clean
