#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int distance(int x, int y)
{
  return abs(x - y);
}

class Creature
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/

  // << ", niveau: "
  // << ", points de vie: "
  // << ", force: "
  // << ", points d'attaque: "
  // << ", position: "

  // << " n'est plus !"

protected:
  string const nom_;
  int niveau_;
  int points_de_vie_;
  int force_;
  int position_;

  bool isInRange(Creature &bete, int x) {
    int min = position_ - x;
    int max = position_ + x;
    int pos = bete.position();
    return pos >= min && pos <= max;
  }

public:
  Creature(string const &nom, int niveau, int points_de_vie, int force, int position=0) :
    nom_(nom), niveau_(niveau), points_de_vie_(points_de_vie), force_(force), position_(position) {

  }

  string nom() const {return nom_;}
  int niveau() const {return niveau_;}
  int points_de_vie() const {return points_de_vie_;}
  int force() const {return force_;}
  int position() const {return position_;}

  bool vivant() const {return points_de_vie_ > 0;}

  int points_attaque() const { return vivant() ? niveau_ * force_ : 0;}

  void deplacer(int d) { position_ += d;}

  void adieux() const { cout << nom_ << " n'est plus !";}

  void faiblir(int a) {
    points_de_vie_ -= a;

    if (!vivant()) {
      points_de_vie_ = 0;
      adieux();
    }
  }

  void afficher() {
    cout << nom_<<", niveau: "<<niveau_<<", points de vie: "<<points_de_vie_<<", force: "<<force_<<", points d’attaque: "<<points_attaque()<<", position: "<<position_ << endl;
  }
};

class Dragon : public Creature {
private:
  int portee_flamme_;

  bool isInRange(Creature &bete) {
    return Creature::isInRange(bete, portee_flamme_);
  }

public:
  Dragon(string const &nom, int niveau, int points_de_vie, int force, int portee_flamme, int position=0) :
    Creature(nom,niveau,points_de_vie,force,position), portee_flamme_(portee_flamme)
    {}

  void voler(int pos) {
    position_ = pos;
  }

  void souffle_sur(Creature &bete) {
    if (vivant() && bete.vivant() && isInRange(bete)) {
      bete.faiblir(points_attaque());
      faiblir(distance(position_,bete.position()));

      if (vivant() && bete.vivant()) {
        niveau_++;
      }
    }
  }
};

class Hydre : public Creature {
private:
  int longeur_cou_;
  int dose_poison_;

  bool isInRange(Creature &bete) {
    return Creature::isInRange(bete, longeur_cou_);
  }

public:
  Hydre(string const &nom, int niveau, int points_de_vie, int force, int longeur_cou, int dose_poison, int position=0) :
    Creature(nom,niveau,points_de_vie,force,position),
    longeur_cou_(longeur_cou),
    dose_poison_(dose_poison)
    {

    }

  void empoisonne(Creature &bete) {
    if (vivant() && bete.vivant() && isInRange(bete)) {
      bete.faiblir(points_attaque() + dose_poison_);

      if (!bete.vivant()) {
        niveau_++;
      }
    }
  }
};

void combat(Dragon &d, Hydre &h) {
  h.empoisonne(d);
  d.souffle_sur(h);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  Dragon dragon("Dragon rouge"   , 2, 10, 3, 20         );
  Hydre  hydre ("Hydre maléfique", 2, 10, 1, 10, 1,  42 );

  dragon.afficher();
  cout << "se prépare au combat avec :" << endl;
  hydre.afficher();

  cout << endl;
  cout << "1er combat :" << endl;
  cout << "    les créatures ne sont pas à portée, donc ne peuvent pas s'attaquer."
       << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon vole à proximité de l'hydre :" << endl;
  dragon.voler(hydre.position() - 1);
  dragon.afficher();

  cout << endl;
  cout << "L'hydre recule d'un pas :" << endl;
  hydre.deplacer(1);
  hydre.afficher();

  cout << endl;
  cout << "2e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 2 points de vie supplémentaires\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 41 = 2 ].\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon avance d'un pas :" << endl;
  dragon.deplacer(1);
  dragon.afficher();

  cout << endl;
  cout << "3e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 1 point de vie supplémentaire\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 42 = 1 ] ;\n\
  + l'hydre est vaincue et le dragon monte au niveau 3.\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "4e Combat :" << endl;
  cout << "    quand une créature est vaincue, rien ne se passe." << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  return 0;
}
