PROGS=testlisten oobrecv oobsend serv daytime


testlisten:	testlisten.o
	g++ -g -Wall testlisten.cpp -o testlisten

oobsend:	oobsend.o
	g++ -g -Wall oobsend.cpp -o oobsend

oobrecv:	oobrecv.o
	g++ -g -Wall oobrecv.cpp -o oobrecv

serv:		serv.o
	g++ -g -Wall serv.cpp -o serv

daytime:	daytime.o
	g++ -g -Wall daytime.cpp -o daytime

clean:
	rm *.o ${PROGS}