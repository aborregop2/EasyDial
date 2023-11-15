OPTIONS = -std=c++11 -Wextra -Werror -Wno-sign-compare -O0 -ansi -Wall -I $(CPLUS_INCLUDE_PATH)

program.exe: program.o dialog.o easy_dial.o call_registry.o phone.o
	g++ $(OPCIONS) -o programa.exe -L $(LIBRARY_PATH) -lesin
	
programa.o: programa.cpp dialog.hpp easy_dial.hpp call_registry.hpp phone.hpp
	g++ $(OPCIONS) -c programa.cpp
	
dialog.o: dialog.cpp dialog.hpp easy_dial.hpp call_registry.hpp phone.hpp
	g++ $(OPCIONS) -c dialog.cpp 	

easy_dial.o: easy_dial.cpp easy_dial.hpp call_registry.hpp phone.hpp
	g++ $(OPCIONS) -c easy_dial.cpp 
	
call_registry.o: call_registry.cpp call_registry.hpp phone.hpp
	g++ $(OPCIONS) -c call_registry.cpp
		
phone.o: phone.cpp phone.hpp
	g++ $(OPCIONS) -c phone.cpp 

clean:
	rm *.o
	rm *.exe
	rm *.ghc
