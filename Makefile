all:
	g++ src/*.cpp -o fasta_ran -g --std=c++11

clean:
	rm fasta_ran
	rm *.fasta
