ALL = src/*
SOU = src/main.cpp src/ColaPedidos.cpp src/PapaNoel.cpp src/Test.cpp
TST = src/ColaPedidos.cpp src/PapaNoel.cpp src/Test.cpp test.cpp
main: $(ALL)
	g++ $(SOU) -g -o Main | head

test: test.cpp $(ALL)
	g++ $(TST) -g -o MiTest | head


