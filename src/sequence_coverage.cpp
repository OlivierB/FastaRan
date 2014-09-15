#include "../include/sequence_coverage.hpp"


using namespace std;

SequenceCoverage::SequenceCoverage() {
  start_ = 0;
  end_ = 0;
  sum_coverage_ = 0;
}

SequenceCoverage::SequenceCoverage(int start, int end) {
  start_ = start;
  end_ = end;
  sum_coverage_ = 0;
}

SequenceCoverage::~SequenceCoverage() {

}

int SequenceCoverage::ratio_coverage_percent() {
  int inter = end_ - start_;
  return (sum_coverage_/(float)inter) * 100.0;
}

void SequenceCoverage::add_sequence(int start, int end) {
  // structure de travail
  struct intervalle inter;
  inter.start = start;
  inter.end = end;
  // Vérifier l'intégrité
  if (inter.start < start_)
    inter.start = start_;
  if (inter.end > end_)
    inter.end = end_;
  if (inter.end  - inter.start < 0) {
    cout << "ERREURR : Intervalle négatif." << endl;
    return;
  }
  
  // ajout dans la liste des actions effectués
  sequences_list_.push_back(inter);
  
  // calcul du nouveau recouvrement
  if (coverage_.empty()) {
    coverage_.push_back(inter);
    sum_coverage_ += (inter.end - inter.start);
  } else if (coverage_[coverage_.size() - 1].start <= inter.start) { 
    //cout << "dernier" << endl;
    int position = coverage_.size();
    if (coverage_[position-1].end  >= inter.end) {
      // absorbé
      //cout << "absorbé" << endl;
    } else if (coverage_[position-1].end >= inter.start) {
      // fin continue
      //cout << "continue" << endl;
      sum_coverage_ += ((inter.end - inter.start) - (coverage_[position-1].end - inter.start));
      coverage_[position-1].end = inter.end;
    } else {
      // fin discontinue
      //cout << "discontinue" << endl;
      sum_coverage_ += (inter.end - inter.start);
      coverage_.push_back(inter);
    }
  } else {
    //récupération de la position dans le tableau
    int position = 0;
    while (position < coverage_.size()) {
      if (coverage_[position].start > inter.start) {
        break;
      } else {
        position += 1;
      }
    }
    
    // Récupérer les intervalles concernés
    int pos_end = position;
    while (pos_end < coverage_.size() && coverage_[pos_end].start <= inter.end) {
      pos_end += 1;
    }
    
    //cout << "Nb elem : " << coverage_.size() << " pos S : " << position << " pos E : " << pos_end << endl;
    
    
    if (position == pos_end) {
      //cout << "0 intermediaire" << endl;
      // pas d'intervalles concernés
      if (position > 0 && coverage_[position-1].end >= inter.start) {
        if (coverage_[position-1].end < inter.end) {
          //cout << "etendu précédent" << endl;
          // possibilité d'étendre l'intervalle précédent
          sum_coverage_ += ((inter.end - inter.start) - (coverage_[position-1].end - inter.start));
          coverage_[position-1].end = inter.end;
        } else {
          // sinon absorbé
          //cout << "absorbé" << endl;
        }
      } else {
        //cout << "nouveau" << endl;
        //ajout de l'intervalle
        sum_coverage_ += inter.end - inter.start;
        coverage_.insert(coverage_.begin()+position, inter);
      }
    } else {
      //cout << pos_end - position << " intermediaire" << endl;
      // etendre la fin de l'intervalle si nécessaire
      if (coverage_[pos_end-1].end > inter.end) {
        inter.end = coverage_[pos_end-1].end;
      }
      
      // Gestion des intermédiares
      bool remove_first = false;
      if (position > 0 && coverage_[position-1].end >= inter.start) {
        //cout << "first remove" << endl;
        // Gestion de l'intervalle précédent
        remove_first = true;
        sum_coverage_ -= coverage_[position-1].end - coverage_[position-1].start;
        inter.start = coverage_[position-1].start;
      }
      
      // suppression des intermédiaires sauf le premier
      for (int cpt = position+1; cpt < pos_end; cpt++) {
        //cout << "remove num " << cpt << endl;
        sum_coverage_ -= coverage_[position+1].end - coverage_[position+1].start;
        coverage_.erase(coverage_.begin()+position+1);
      }
      
      // Décompter l'intervalle oublié
      sum_coverage_ -= (coverage_[position].end - coverage_[position].start);
      // Ajout de l'intervalle
      sum_coverage_ += inter.end - inter.start;
      // Modification de l'élément intermédiaire laissé de coté
      coverage_[position].start = inter.start;
      coverage_[position].end = inter.end;
      
      // Suppression premier élément inutile
      if (remove_first)
        coverage_.erase(coverage_.begin() + position-1);
    } 
  }
  //cout << "sum_coverage_ : " << sum_coverage_ << endl;
  //cout << "coverage_ : " << coverage_.size() << endl;
}

void SequenceCoverage::print_coverage() {
  cout << "Intervalles de recouvrement" << endl;
  for(int cpt = 0; cpt < coverage_.size(); cpt++) {
    cout << coverage_[cpt].start << " - " << coverage_[cpt].end << endl;
  }
}

void SequenceCoverage::print_sequences() {
  cout << "Liste des séquences" << endl;
  for(int cpt = 0; cpt < sequences_list_.size(); cpt++) {
    cout << sequences_list_[cpt].start << " - " << sequences_list_[cpt].end << endl;
  }
}

void SequenceCoverage::print_stats() {
  cout << "---Stats séquences ---" << endl;
  cout << "Nombre de Séquence : " << sequences_list_.size() << endl;
  cout << "Nombre d'éléments complétés : " << sum_coverage_ << "/" << end_ - start_ << endl;
  cout << "Ratio recouvrement : " << ratio_coverage_percent() << endl;
  cout << "Taille table de recouvrement : " << coverage_.size() << endl;
}
