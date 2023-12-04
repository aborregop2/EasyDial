OPTIONS = -std=c++11 -g -Wextra -Wno-sign-compare -O0 -Wall -Wno-deprecated  #-I $(CPLUS_INCLUDE_PATH) #-g?
#-Werror
driver_easydial.exe: driver_easydial.o dialog.o easy_dial.o call_registry.o phone.o 
	g++ $(OPTIONS) -o driver_easydial.exe driver_easydial.o call_registry.o phone.o dialog.o easy_dial.o -lesin
	
driver_easydial.o: driver_easydial.cpp  call_registry.hpp phone.hpp dialog.hpp easy_dial.hpp
	g++ $(OPTIONS) -c driver_easydial.cpp
	
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

test:
	./driver_easydial.exe < jp_public_call_registry.in | diff - jp_public_call_registry.res
#	./program.e < sample2.inp | diff - sample2.cor
#	./program.e < sample3.inp | diff - sample3.cor
