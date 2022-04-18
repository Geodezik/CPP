all: ConsoleWitchery

AnimatedObjects.o: AnimatedObjects.cpp AnimatedObjects.hpp
	$(CXX) -c $< $(CXXFLAGS)

Animation.o: Animation.cpp Animation.hpp
	$(CXX) -c $< $(CXXFLAGS)

Stage.o: Stage.cpp Stage.hpp
	$(CXX) -c $< $(CXXFLAGS)

UserObjects.o: UserObjects.cpp UserObjects.hpp
	$(CXX) -c $< $(CXXFLAGS)

main.o: main.cpp AnimatedObjects.cpp AnimatedObjects.hpp Animation.cpp Animation.hpp Stage.cpp Stage.hpp UserObjects.cpp UserObjects.hpp
	$(CXX) -c $< $(CXXFLAGS)

ConsoleWitchery: main.o AnimatedObjects.o Animation.o Stage.o UserObjects.o
	$(CXX) -o $@ main.o AnimatedObjects.o Animation.o Stage.o UserObjects.o
 
clean:
	rm *.o ConsoleWitchery