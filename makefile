CC = g++
EXE = Ripple
ARG = climatedata.txt

all: weatherlog.o datalogger.o WeatherNode.o tools.o
	$(CC) weatherlog.o datalogger.o WeatherNode.o tools.o -o $(EXE)
	rm -f *.o

e: weatherlog.o datalogger.o WeatherNode.o tools.o
	$(CC) weatherlog.o datalogger.o WeatherNode.o tools.o -o $(EXE)
	rm -f *.o
	./$(EXE) $(ARG)

weatherlog.o: weatherlog.cpp
	$(CC) -g -c weatherlog.cpp

datalogger.o: datalogger.h datalogger.cpp
	$(CC) -g -c datalogger.cpp

WeatherNode.o: WeatherNode.h WeatherNode.cpp
	$(CC) -g -c WeatherNode.cpp

tools.o: tools.h tools.cpp
	$(CC) -g -c tools.cpp
clean:
	$(info ---------- Whoosh! ----------)
	rm -f *.o 
	rm -f $(EXE)
