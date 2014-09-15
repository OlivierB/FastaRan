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
  if (genome_->nucleotides_string() == NULL) {
    cout << "Génération automatique d'un génome de 100 nucléotides" << endl;
    genome_->auto_generation(100, 50);
   }
}

void FastaCreator::generate(int coverage, FastaFormat* my_file) {
  // Vérifier la valeur de recouvrement
  if (coverage < 1) {
    coverage = 1;
    cout << "Ajustement de la valeur de recouvrement à 1" << endl;
  }

  // Gestion des intervalles
  seq = new SequenceCoverage(0, genome_->size());
  
  int rand_pos, rand_size;
  int a = 0;
  int sum = 0;
  // Création d'une séquence
  while (seq->ratio_coverage_percent() < coverage) {
    rand_pos = rand() % (genome_->size() + 1);
    rand_size = rand() % 1000 + 75;
    
    seq->add_sequence(rand_pos - rand_size, rand_pos + rand_size);
    
    if (sum > seq->sum_coverage()) {
      cout << "ERREUR : Mauvaise somme (" << sum << ", " << seq->sum_coverage() << ")." <<  endl;
      break;
    }
    sum = seq->sum_coverage();
    
    a += 1;
  }
  seq->print_stats();
  //seq.print_sequences();
  //seq.print_coverage();
  
  
  // cout << "Ecriture du fichier" << endl;
  // vector<struct intervalle>* tabSeq = seq.sequences_list();
  // for (vector<struct intervalle>::iterator it = tabSeq->begin(); it != tabSeq->end(); ++it)
  //   my_file->write(genome_, &(*it));
}

int FastaCreator::get_coverage(){
  return fc_coverage;
}

int FastaCreator::get_file_size(){
  return ff_file->get_file_size();
}

string FastaCreator::get_chaine(int debut, int longueur){
  if(debut + longueur >= genome_->size())
    longueur = genome_->size() - debut - 1;

  return string(genome_->nucleotides_string() + debut, longueur);
}

std::string FastaCreator::get_coverage_json(){
  std::stringstream ss;  
  ss << "[";
  for (vector<struct intervalle>::iterator it = seq->coverage()->begin(); it != seq->coverage()->end(); ++it)
  {
    ss << "{ \"debut\" : " << (*it).start << ", \"fin\" : " << (*it).end << "}";
    if(it+1 != seq->coverage()->end()){
      ss << ",";
    }
  }
  ss << "]";
  return ss.str();
}
