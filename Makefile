all:
	g++ src/*.cpp -o fasta_ran -g --std=c++11 -lboost_system  -pthread -I ./lib/websocketpp/

clean:
	rm fasta_ran
	rm *.fasta
