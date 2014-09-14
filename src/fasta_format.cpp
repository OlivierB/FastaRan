#include "../include/fasta_format.hpp"


#include "../include/sequence_coverage.hpp"

using namespace std;

void FastaFormat::open() {
  if (!file_is_open_) {
    file_stream_.open(file_name_);
    file_is_open_ = true;
  }
}

void FastaFormat::close() {
  file_stream_.close();
  file_is_open_ = false;
}


void FastaFormatUn::write(Genome* genome, struct intervalle* inter) {
  open();

  int size = genome->size();
  char* s_genome = genome->nucleotides_string();
  char* gen_part = s_genome + inter->start;
  
  // Sauvegarde du caractère de fin
  char tmp = ' ';
  if (inter->end < size) {
    tmp = s_genome[inter->end];
    s_genome[inter->end] = '\0';
  }
  
  file_stream_ << ">len " << inter->end - inter->start + 1 << endl << gen_part << endl;
  
  // restauration du caractère de fin
  if (inter->end < size) {
    s_genome[inter->end] = tmp;
  }
}


