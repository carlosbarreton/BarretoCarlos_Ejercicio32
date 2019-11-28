wave1.png: wave1.dat wave.py
	python wave.py

wave1.dat: wave.x
	./wave.x

wave.x: wave.cpp
	c++ wave.cpp -o wave.x