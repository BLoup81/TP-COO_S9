#include <cpr/cpr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

using namespace std;
using json = nlohmann::json;

class Ville {
 private:
  int code_postal;
  string nom;
  int prix_m2;

 public:
  Ville(json j);  // Constructeur par donnees json
  Ville(int id);  // Constructeur par id
  Ville() {}      // Constructeur par defaut

  void set(json j);  // Setter

  friend ostream& operator<<(ostream& os, const Ville& ville);
};

class Machine {
 private:
  string nom;
  int prix;
  string n_serie;

 public:
  Machine(json j);  // Constructeur par donnees json
  Machine(int id);  // Constructeur par id
  Machine() {}      // Constructeur par defaut

  void set(json j);  // Setter

  friend ostream& operator<<(ostream& os, const Machine& M);
};

class Ressource {
 private:
  string nom;
  int prix;

 public:
  Ressource(json j);  // Constructeur par donnees json
  Ressource(int id);  // Constructur par id
  Ressource() {}      // Constructeur par defaut

  void set(json j);  // Setter

  friend ostream& operator<<(ostream& os, const Ressource& R);
};

class SiegeSocial {
 private:
  string nom;
  unique_ptr<Ville> ville;
  int surface;

 public:
  SiegeSocial(json j);  // Constructeur par donnees json
  SiegeSocial(int id);  // Constructeur par id
  SiegeSocial() {}      // Constructeur par defaut

  void set(json j);  // Setter

  friend ostream& operator<<(ostream& os, const SiegeSocial& siegesocial);
};

class Stock {
 private:
  unique_ptr<Ressource> ressource;
  int nombre;

 public:
  Stock(json j);  // Constructeur par donnees json
  Stock(int id);  // COnstructeur par id
  Stock() {}      // Constructeur par defaut

  void set(json j);  // Setter

  friend ostream& operator<<(ostream& os, const Stock& S);
};

class QuantiteRessource {
 private:
  unique_ptr<Ressource> ressource;
  int quantite;

 public:
  QuantiteRessource(json j);  // Constructeur par donnees json
  QuantiteRessource(int id);  // COnstructeur par id
  QuantiteRessource() {}      // Constructeur par defaut

  void set(json j);  // Setter

  friend ostream& operator<<(ostream& os, const QuantiteRessource& Q);
};

class Etape {
 private:
  string nom;
  unique_ptr<Machine> M;
  unique_ptr<QuantiteRessource> Q;
  int duree;
  optional<unique_ptr<Etape>>
      etapeSuivante;  // Une etape n'a pas forcement d'etape suivante,
                      // ainsi, un pointeur optionel est utilise
 public:
  Etape(json j);  // Constructeur par donnees json
  Etape(int id);  // Constructeur par id
  Etape() {}      // Constructeur par defaut

  void set(json j);  // Setter

  friend ostream& operator<<(ostream& os, const Etape& E);
};

class Usine {
 private:
  string nom;
  unique_ptr<Ville> ville;
  int surface;
  vector<unique_ptr<Machine>>
      machines;  // Il peut y avoir plusieurs machines/stocks,
  vector<unique_ptr<Stock>> stocks;  // donc un vecteur de pointeur est utilise

 public:
  Usine(json j);  // Constructeur par donnees json
  Usine(int id);  // Constructeur par id
  Usine() {};     // Constructeur par defaut

  void set(json j);  // Setter

  friend ostream& operator<<(ostream& os, const Usine& U);
};

class Produit {
 private:
  string nom;
  int prix;
  unique_ptr<Etape> premiereEtape;

 public:
  Produit(json j);  // Constructeur par donnees json
  Produit(int id);  // Constructeur par id
  Produit() {};     // Constructeur par defaut

  void set(json j);  // Setter

  friend ostream& operator<<(ostream& os, const Produit& P);
};

//////////////////////////////////////////////////////////////
////  DEFINITION DES METHODES   //////////////////////////////
//////////////////////////////////////////////////////////////

//////////////////////////////////////
/// Ville ////////////////////////////
//////////////////////////////////////
Ville::Ville(json j) { set(j); }

Ville::Ville(int id) {
  cpr::Response r =  // Recuperation du lien http avec les donnees json
      cpr::Get(cpr::Url{"http://localhost:8000/ville/" + to_string(id) + "/"});
  r.text;

  auto j = json::parse(r.text);
  set(j);
}

void Ville::set(
    json j) {  // Affectation des donnees json aux nouvelles instances
  nom = j["Nom"];
  code_postal = j["Code postal"];
  prix_m2 = j["Prix/m2"];
}

ostream& operator<<(ostream& os, const Ville& ville) {
  os << "Ville:\n";
  os << "\tNom:" << ville.nom << "\n";
  os << "\tCode postal:" << ville.code_postal << "\n";
  os << "\tPrix m²:" << ville.prix_m2;

  return os;
}

//////////////////////////////////////
/// Ressource ////////////////////////
//////////////////////////////////////
Ressource::Ressource(json j) { set(j); }

Ressource::Ressource(int id) {
  cpr::Response r =
      cpr::Get(  // Recuperation du lien http avec les donnees json
          cpr::Url{"http://localhost:8000/ressource/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  set(j);
}

void Ressource::set(json j) {
  nom = j["Nom"];
  prix = j["Prix"];
}

ostream& operator<<(ostream& os, const Ressource& R) {
  os << "Ressource:" << endl;
  os << "\tNom:" << R.nom << endl;
  os << "\tPrix:" << R.prix;
  return os;
}

//////////////////////////////////////
/// Machine //////////////////////////
//////////////////////////////////////
Machine::Machine(json j) { set(j); }

Machine::Machine(int id) {
  cpr::Response r =
      cpr::Get(  // Recuperation du lien http avec les donnees json
          cpr::Url{"http://localhost:8000/machine/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  set(j);
}

void Machine::set(json j) {
  nom = j["Nom"];
  prix = j["Prix"];
  n_serie = j["Num_serie"];
}

ostream& operator<<(ostream& os, const Machine& M) {
  os << "Machine:" << endl;
  os << "\tNom:" << M.nom << endl;
  os << "\tN serie:" << M.n_serie << endl;
  os << "\tPrix:" << M.prix;
  return os;
}

//////////////////////////////////////
/// Siege Social /////////////////////
//////////////////////////////////////
SiegeSocial::SiegeSocial(json j) { set(j); }

SiegeSocial::SiegeSocial(int id) {
  cpr::Response r =
      cpr::Get(  // Recuperation du lien http avec les donnees json
          cpr::Url{"http://localhost:8000/siegesocial/" + to_string(id) + "/"});

  r.text;

  auto j = json::parse(r.text);
  set(j);
}

void SiegeSocial::set(json j) {
  nom = j["Nom"];
  surface = j["Surface"];
  ville = make_unique<Ville>(
      j["Ville"]);  // Creation d'un pointeur unique sur la ville
}

ostream& operator<<(ostream& os, const SiegeSocial& siegesocial) {
  os << "Siège social:" << endl;
  os << "\tNom:" << siegesocial.nom << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\t" << *siegesocial.ville
     << endl;  // Affiche l'adresse pointee par ville
  os << "\t----------------------------------------------------" << endl;
  os << "\tSurface:" << siegesocial.surface;
  return os;
}

//////////////////////////////////////
/// Stock ////////////////////////////
//////////////////////////////////////
Stock::Stock(json j) { set(j); }

Stock::Stock(int id) {
  cpr::Response r =  // Recuperation du lien http avec les donnees json
      cpr::Get(cpr::Url{"http://localhost:8000/stock/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  set(j);
}

void Stock::set(json j) {
  ressource = make_unique<Ressource>(j["Ressource"]);
  nombre = j["En stock"];
}

ostream& operator<<(ostream& os, const Stock& S) {
  os << "Stock" << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\t" << *S.ressource << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\tNombre: " << S.nombre;
  return os;
}

//////////////////////////////////////
/// QuantiteRessource ////////////////
//////////////////////////////////////
QuantiteRessource::QuantiteRessource(json j) { set(j); }

QuantiteRessource::QuantiteRessource(int id) {
  cpr::Response r = cpr::Get(cpr::Url{
      // Recuperation du lien http avec les donnees json
      "http://localhost:8000/quantiteressource/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  set(j);
}

void QuantiteRessource::set(json j) {
  ressource = make_unique<Ressource>(j["Ressource"]);
  quantite = j["Quantite"];
}

ostream& operator<<(ostream& os, const QuantiteRessource& Q) {
  os << "Quantite de Ressource:" << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\t" << *Q.ressource << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\tQuantite:" << Q.quantite;
  return os;
}

//////////////////////////////////////
/// Etape ////////////////////////////
//////////////////////////////////////
Etape::Etape(json j) { set(j); }

Etape::Etape(int id) {
  cpr::Response r =  // Recuperation du lien http avec les donnees json
      cpr::Get(cpr::Url{"http://localhost:8000/etape/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  set(j);
}

void Etape::set(json j) {
  nom = j["Nom"];
  M = make_unique<Machine>(j["Machine"]);
  Q = make_unique<QuantiteRessource>(j["Quantité de ressources"]);
  duree = j["Durée"];
  if (j["Etape suivante"] != "none") {  // Test si il existe une etape suivante
    etapeSuivante = make_unique<Etape>(
        j["Etape suivante"]);  // Si le test est verifie, creer un pointeur sur
                               // l'etape suivante
  }
}

ostream& operator<<(ostream& os, const Etape& E) {
  os << "Etape:" << endl;
  os << "\tNom:" << E.nom << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\t" << *E.M << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\t" << *E.Q << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\tDuree:" << E.duree;
  if (E.etapeSuivante) {  // Test si une etape suivante existe
    os << "\n\n\tEtape suivante:"
       << endl;  // Si test verifie, affiche l'etape suivante
    os << "\t----------------------------------------------------" << endl;
    os << "\t" << *E.etapeSuivante.value();
  }
  return os;
}

//////////////////////////////////////
/// Usine ////////////////////////////
//////////////////////////////////////
Usine::Usine(json j) { set(j); }

Usine::Usine(int id) {
  cpr::Response r =  // Recuperation du lien http avec les donnees json
      cpr::Get(cpr::Url{"http://localhost:8000/usine/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  set(j);
}

void Usine::set(json j) {
  nom = j["Nom"];
  surface = j["Surface"];
  ville = make_unique<Ville>(j["Ville"]);

  int i = 0;
  // Boucle while: Tant qu'il y a des machines/stocks appartenant a l'usine,
  // ils sont ajout au vecteur de pointeurs
  // Avec i<=100 limitant le nombre de machines/stocks a 100 pour eviter une
  // boucle infinie
  while (to_string(j["Machines"][i]) != "null" && i <= 100) {
    machines.push_back(
        make_unique<Machine>(j["Machines"][i]));  // Ajout des machines a usine
    i++;
  }

  i = 0;
  while (to_string(j["Stocks"][i]) != "null" && i <= 100) {
    stocks.push_back(
        make_unique<Stock>(j["Stocks"][i]));  // Ajout des socks a usine
    i++;
  }
}

ostream& operator<<(ostream& os, const Usine& U) {
  os << "Usine:" << endl;
  os << "\tNom:" << U.nom << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\t" << *U.ville << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\tSurface:" << U.surface;
  for (int i = 0; i < U.machines.size();
       i++) {  // Boucle for parcourant le vecteur machines
    os << "\n\t----------------------------------------------------" << endl;
    os << "\t" << *U.machines[i]
       << endl;  // Affiche la i_eme adresse pointer par machines
    os << "\t----------------------------------------------------";
  }
  for (int i = 0; i < U.stocks.size();
       i++) {  // Boucle for parcourant le vecteur stocks
    os << "\n\t----------------------------------------------------" << endl;
    os << "\t" << *U.stocks[i]
       << endl;  // Affiche la i_eme adresse pointer par stocks
    os << "\t----------------------------------------------------";
  }
  return os;
}

//////////////////////////////////////
/// Produit //////////////////////////
//////////////////////////////////////
Produit::Produit(json j) { set(j); }

Produit::Produit(int id) {
  cpr::Response r =
      cpr::Get(  // Recuperation du lien http avec les donnees json
          cpr::Url{"http://localhost:8000/produit/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  set(j);
}

void Produit::set(json j) {
  nom = j["Nom"];
  prix = j["Prix"];
  premiereEtape = make_unique<Etape>(j["Etape"]);
}

ostream& operator<<(ostream& os, const Produit& P) {
  os << "Produit:" << endl;
  os << "\tNom:" << P.nom << endl;
  os << "\tPrix:" << P.prix << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\t" << *P.premiereEtape;
  return os;
}

//////////////////////////////////////////////
////////// Main //////////////////////////////
//////////////////////////////////////////////

int main() {
  cout << "Impatient de voir ce qu'il y a dans ce code?" << endl;

  return 0;
}
