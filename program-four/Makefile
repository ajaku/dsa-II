merge.exe: merge.o hash.o
	g++ -o merge.exe merge.o hash.o

merge.o: merge.cpp
	g++ -c merge.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o mergeDebug.exe hash.cpp merge.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
