#include "../include/fasta_creator.hpp"
#include "../include/sequence_coverage.hpp"


using namespace std;

FastaCreator::FastaCreator() {
  genome_ = NULL;
}

FastaCreator::~FastaCreator() {

}

FastaCreator::FastaCreator(Genome* genome) {
  genome_ = genome;
  if (genome_->nucleotides_string() == NULL)
    genome_->auto_generation(100, 50);
}

void FastaCreator::generate(int coverage, FastaFormat* my_file) {
  // Vérifier la valeur de recouvrement
  if (coverage < 1) {
    coverage = 1;
    cout << "Ajustement de la valeur de recouvrement à 1" << endl;
  }
  
  // Gestion des intervalles
  SequenceCoverage seq(0, genome_->size());
  
  int rand_pos, rand_size, start, end;

  int a = 0;
  // Création d'une séquence
  while (seq.ratio_coverage_percent() < coverage) {
    rand_pos = rand() % (genome_->size() + 1);
    rand_size = rand() % 1000 + 75;
    
    start = rand_pos - rand_size;
    end = rand_pos + rand_size;
    if (start < 0)
      start = 0;
    if (end > genome_->size())
      end = genome_->size();
    
    seq.add_sequence(start, end);
    a += 1;
  }
  seq.print_stats();
  //seq.print_sequences();
  //seq.print_sequences();
  
  cout << "Ecriture du fichier" << endl;
  vector<struct intervalle>* tabSeq = seq.sequences_list();
  for (vector<struct intervalle>::iterator it = tabSeq->begin(); it != tabSeq->end(); ++it)
    my_file->write(genome_, &(*it));
}

