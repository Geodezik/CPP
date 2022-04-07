#output: Bubbles_vs_Balloons
CXX = $(shell fltk-config --cxx)

CXXFLAGS = $(shell fltk-config --cxxflags) -Wall -O3 -I/other/include/paths...

LINKFLTK = $(shell fltk-config --ldstaticflags)
LINKFLTK_GL = $(shell fltk-config --use-gl --ldstaticflags)
LINKFLTK_IMG = $(shell fltk-config --use-images --ldstaticflags)

STRIP      = strip
POSTBUILD  = fltk-config --post

all: Bubbles_vs_Balloons

directions.o: directions.cxx directions.hpp
	$(CXX) -c $< $(CXXFLAGS)

settings.o: settings.cxx settings.hpp
	$(CXX) -c $< $(CXXFLAGS)

cell.o: cell.cxx cell.hpp
	$(CXX) -c $< $(CXXFLAGS)

stage.o: stage.cxx stage.hpp
	$(CXX) -c $< $(CXXFLAGS)

some_callbacks.o: some_callbacks.cxx some_callbacks.hpp
	$(CXX) -c $< $(CXXFLAGS)

app.o: app.cxx app.hpp
	$(CXX) -c $< $(CXXFLAGS)

main.o: main.cxx directions.cxx directions.hpp settings.cxx settings.hpp cell.cxx cell.hpp stage.cxx stage.hpp some_callbacks.cxx some_callbacks.hpp app.cxx app.hpp
	$(CXX) -c $< $(CXXFLAGS)

Bubbles_vs_Balloons: main.o directions.o settings.o cell.o stage.o some_callbacks.o app.o
	$(CXX) -o $@ main.o directions.o settings.o cell.o stage.o some_callbacks.o app.o $(LINKFLTK) $(LINKFLTK_IMG) #$(LINKFLTK_GL)
	$(STRIP) $@
	$(POSTBUILD) $@
 
clean:
	rm *.o Bubbles_vs_Balloons