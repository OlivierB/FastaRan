#ifndef FASTACREATOR_H
#define FASTACREATOR_H

#include <iostream>

#include "../include/genome.hpp"
#include "../include/fasta_format.hpp"

class FastaCreator {
  public:
    // Constructeurs
    FastaCreator(Genome *genome);
    ~FastaCreator();
    
    void generate(int coverage, FastaFormat* my_file);
    
    
  private:
    Genome* genome_;
    
    FastaCreator();
  
};


#endif
