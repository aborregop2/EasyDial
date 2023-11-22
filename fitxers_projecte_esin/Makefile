OPTIONS = -std=c++14 -Wextra -Werror -Wno-sign-compare -O0 -ansi -Wall -Wno-deprecated  #-I $(CPLUS_INCLUDE_PATH) #-g?

program.exe: program.o dialog.o easy_dial.o call_registry.o phone.o
	g++ $(OPTIONS) -o programa.exe -L $(LIBRARY_PATH) -lesin
	
programa.o: programa.cpp dialog.hpp easy_dial.hpp call_registry.hpp phone.hpp
	g++ $(OPTIONS) -c programa.cpp
	
dialog.o: dialog.cpp dialog.hpp easy_dial.hpp call_registry.hpp phone.hpp
	g++ $(OPTIONS) -c dialog.cpp 	

easy_dial.o: easy_dial.cpp easy_dial.hpp call_registry.hpp phone.hpp
	g++ $(OPTIONS) -c easy_dial.cpp 
	
call_registry.o: call_registry.cpp call_registry.hpp phone.hpp
	g++ $(OPTIONS) -c call_registry.cpp
		
phone.o: phone.cpp phone.hpp
	g++ $(OPTIONS) -c phone.cpp 

clean:
	rm *.o
	rm *.exe
	rm *.ghc

#test:
#	./program.e < sample1.inp | diff - sample1.cor
#	./program.e < sample2.inp | diff - sample2.cor
#	./program.e < sample3.inp | diff - sample3.cor
