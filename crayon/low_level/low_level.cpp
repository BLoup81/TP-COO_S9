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
  Ville(json j);
  Ville(int id);  // Constructeur par id
  Ville() {}      // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Ville& ville);
};

class Machine {
 private:
  string nom;
  int prix;
  string n_serie;

 public:
  Machine(json j);
  Machine(int id);  // Constructeur par id
  Machine() {}      // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Machine& M);
};

class Ressource {
 private:
  string nom;
  int prix;

 public:
  Ressource(json j);
  Ressource(int id);  // Constructur par id
  Ressource() {}      // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Ressource& R);
};

class SiegeSocial {
 private:
  string nom;
  unique_ptr<Ville> ville;
  int surface;

 public:
  SiegeSocial(json j);
  SiegeSocial(int id);  // Constructeur par id
  SiegeSocial() {}      // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const SiegeSocial& siegesocial);
};

class Stock {
 private:
  unique_ptr<Ressource> ressource;
  int nombre;

 public:
  Stock(json j);
  Stock(int id);  // COnstructeur par id
  Stock() {}      // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Stock& S);
};

class QuantiteRessource {
 private:
  unique_ptr<Ressource> R;
  int quantite;

 public:
  QuantiteRessource(json j);
  QuantiteRessource(int id);  // COnstructeur par id
  QuantiteRessource() {}      // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const QuantiteRessource& Q);
};

class Etape {
 private:
  string nom;
  unique_ptr<Machine> M;
  unique_ptr<QuantiteRessource> Q;
  int duree;
  optional<unique_ptr<Etape>> etapeSuivante;

 public:
  Etape(json j);
  Etape(int id);  // Constructeur par id
  Etape() {}      // Constructeur par defaut

  void getEtapeSuivante(int id);

  friend ostream& operator<<(ostream& os, const Etape& E);
};

class Usine {
 private:
  string nom;
  unique_ptr<Ville> ville;
  int surface;
  vector<unique_ptr<Machine>> machines;
  vector<unique_ptr<Stock>> stocks;

 public:
  Usine(json j);
  Usine(int id);  // Constructeur par id
  Usine() {};     // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Usine& U);
};

class Produit {
 private:
  string nom;
  int prix;
  unique_ptr<Etape> premiereEtape;

 public:
  Produit(json j);
  Produit(int id);  // Constructeur par id
  Produit() {};     // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Produit& P);
};

//////////////////////////////////////////////////////////////
////  DEFINITION DES METHODES   //////////////////////////////
//////////////////////////////////////////////////////////////

//////////////////////////////////////
/// Ville ////////////////////////////
//////////////////////////////////////
Ville::Ville(json j) {
  nom = j["Nom"];
  code_postal = j["Code postal"];
  prix_m2 = j["Prix/m2"];
}

Ville::Ville(int id) {
  cpr::Response r =
      cpr::Get(cpr::Url{"http://localhost:8000/ville/" + to_string(id) + "/"});
  r.text;

  auto j = json::parse(r.text);
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
Ressource::Ressource(json j) {
  nom = j["Nom"];
  prix = j["Prix"];
}

Ressource::Ressource(int id) {
  cpr::Response r = cpr::Get(
      cpr::Url{"http://localhost:8000/ressource/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
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
Machine::Machine(json j) {
  nom = j["Nom"];
  prix = j["Prix"];
  n_serie = j["Num_serie"];
}

Machine::Machine(int id) {
  cpr::Response r = cpr::Get(
      cpr::Url{"http://localhost:8000/machine/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
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
/// Machine //////////////////////////
//////////////////////////////////////
SiegeSocial::SiegeSocial(json j) {
  nom = j["Nom"];
  ville = make_unique<Ville>(j["Ville"]);
  surface = j["Surface"];
}

SiegeSocial::SiegeSocial(int id) {
  cpr::Response r = cpr::Get(
      cpr::Url{"http://localhost:8000/siegesocial/" + to_string(id) + "/"});

  r.text;

  auto j = json::parse(r.text);
  nom = j["Nom"];
  ville = make_unique<Ville>(int(j["ville_id"]));
  surface = j["Surface"];
}

ostream& operator<<(ostream& os, const SiegeSocial& siegesocial) {
  os << "Siège social:" << endl;
  os << "\tNom:" << siegesocial.nom << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\t" << *siegesocial.ville << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\tSurface:" << siegesocial.surface;
  return os;
}

//////////////////////////////////////
/// Stock ////////////////////////////
//////////////////////////////////////
Stock::Stock(json j) {
  ressource = make_unique<Ressource>(j["Ressource"]);
  nombre = j["En stock"];
}

Stock::Stock(int id) {
  cpr::Response r =
      cpr::Get(cpr::Url{"http://localhost:8000/stock/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  ressource = make_unique<Ressource>(int(j["ressource_id"]));
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
QuantiteRessource::QuantiteRessource(json j) {
  R = make_unique<Ressource>(j["Ressource"]);
  quantite = j["Quantite"];
}

QuantiteRessource::QuantiteRessource(int id) {
  cpr::Response r = cpr::Get(cpr::Url{
      "http://localhost:8000/quantiteressource/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  R = make_unique<Ressource>(int(j["ressource_id"]));
  quantite = j["Quantite"];
}

ostream& operator<<(ostream& os, const QuantiteRessource& Q) {
  os << "Quantite de Ressource:" << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\t" << *Q.R << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\tQuantite:" << Q.quantite;
  return os;
}

//////////////////////////////////////
/// Etape ////////////////////////////
//////////////////////////////////////
Etape::Etape(json j) {
  nom = j["Nom"];
  M = make_unique<Machine>(j["Machine"]);
  Q = make_unique<QuantiteRessource>(j["Quantité de ressources"]);
  duree = j["Durée"];
  if (j["Etape suivante"] != "none") {
    etapeSuivante = make_unique<Etape>(j["Etape suivante"]);
  }
}

Etape::Etape(int id) {
  cpr::Response r =
      cpr::Get(cpr::Url{"http://localhost:8000/etape/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  nom = j["Nom"];
  M = make_unique<Machine>(int(j["machine_id"]));
  Q = make_unique<QuantiteRessource>(int(j["quantite_ressource_id"]));
  duree = j["Durée"];
  if (j["etape_suivante_id"] != "none") {
    etapeSuivante = make_unique<Etape>(int(j["etape_suivante_id"]));
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
  if (E.etapeSuivante) {
    os << "\n\n\tEtape suivante:" << endl;
    os << "\t----------------------------------------------------" << endl;
    os << "\t" << *E.etapeSuivante.value();
  }
  return os;
}

//////////////////////////////////////
/// Usine ////////////////////////////
//////////////////////////////////////
Usine::Usine(json j) {
  nom = j["Nom"];
  surface = j["Surface"];
  ville = make_unique<Ville>(j["Ville"]);

  cout << j["Machines"][2] << endl;

  int i = 0;
  while (to_string(j["Machines"][i]) != "null" && i <= 100) {
    machines.push_back(
        make_unique<Machine>(j["Machines"][i]));  // Ajout des machines a usine
    i++;
  }

  i = 0;
  while (to_string(j["Stocks"][i]) != "null" && i <= 100) {
    stocks.push_back(
        make_unique<Stock>(j["Stocks"][i]));  // Ajout des machines a usine
    i++;
  }
}

Usine::Usine(int id) {
  cpr::Response r =
      cpr::Get(cpr::Url{"http://localhost:8000/usine/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  nom = j["Nom"];
  surface = j["Surface"];
  ville = make_unique<Ville>(int(j["ville_id"]));
  vector<int> myMachines = j["machines_id"].get<vector<int>>();

  for (int i = 0; i < myMachines.size(); i++) {
    machines.push_back(
        make_unique<Machine>(myMachines[i]));  // Ajout des machines a usine
  }

  vector<int> myStocks = j["stocks_id"].get<vector<int>>();
  for (int i = 0; i < myStocks.size(); i++) {
    stocks.push_back(
        make_unique<Stock>(myStocks[i]));  // Ajout des stocks a usine
  }
}

ostream& operator<<(ostream& os, const Usine& U) {
  os << "Usine:" << endl;
  os << "\tNom:" << U.nom << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\t" << *U.ville << endl;
  os << "\t----------------------------------------------------" << endl;
  os << "\tSurface:" << U.surface;
  for (int i = 0; i < U.machines.size(); i++) {
    os << "\n\t----------------------------------------------------" << endl;
    os << "\t" << *U.machines[i] << endl;
    os << "\t----------------------------------------------------";
  }
  for (int i = 0; i < U.stocks.size(); i++) {
    os << "\n\t----------------------------------------------------" << endl;
    os << "\t" << *U.stocks[i] << endl;
    os << "\t----------------------------------------------------";
  }
  return os;
}

//////////////////////////////////////
/// Produit //////////////////////////
//////////////////////////////////////
Produit::Produit(json j) {
  nom = j["Nom"];
  prix = j["Prix"];
  premiereEtape = make_unique<Etape>(j["Etape"]);
}

Produit::Produit(int id) {
  cpr::Response r = cpr::Get(
      cpr::Url{"http://localhost:8000/produit/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  nom = j["Nom"];
  prix = j["Prix"];
  premiereEtape = make_unique<Etape>(int(j["premiere_etape_id"]));
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
  json j = json::parse(
      "{\"Nom\":\"Crayon "
      "B3\",\"Prix\":1,\"premiere_etape_id\":2,\"Etape\":{\"Nom\":\"Couper le "
      "bois\",\"machine_id\":1,\"Machine\":{\"Nom\":\"Scie\",\"Prix\":1000,"
      "\"Num_serie\":\"N1-85\"},\"quantite_ressource_id\":1,\"Quantité de "
      "ressources\":{\"ressource_id\":1,\"Ressource\":{\"Nom\":\"Bois\","
      "\"Prix\":10},\"Quantite\":3},\"Durée\":2,\"etape_suivante_id\":1,"
      "\"Etape suivante\":{\"Nom\":\"Percer le "
      "bois\",\"machine_id\":2,\"Machine\":{\"Nom\":\"Perceuse\",\"Prix\":2000,"
      "\"Num_serie\":\"M8-96\"},\"quantite_ressource_id\":1,\"Quantité de "
      "ressources\":{\"ressource_id\":1,\"Ressource\":{\"Nom\":\"Bois\","
      "\"Prix\":10},\"Quantite\":3},\"Durée\":1,\"etape_suivante_id\":\"none\","
      "\"Etape suivante\":\"none\"}}}");

  Produit P(j);
  cout << P << endl;
  return 0;
}
