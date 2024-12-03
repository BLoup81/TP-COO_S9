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
  Ville(int _code_postal, string _nom,
        int _prix_m2);  // Constructeur en renseignant toutes les infos de la
                        // ville
  Ville(int id);        // Constructeur par id
  Ville() {}            // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Ville& ville);
};

class SiegeSocial {
 private:
  string nom;
  Ville ville;
  int surface;

 public:
  SiegeSocial(const string _nom, const Ville& _ville,
              int _surface);  // Constructeur
  SiegeSocial(int id);        // Constructeur par id
  SiegeSocial() {}            // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const SiegeSocial& siegesocial);
};

class Machine {
 private:
  string nom;
  int prix;
  string n_serie;

 public:
  Machine(const string _nom, int _prix, const string _n_serie);  // Constructeur
  Machine(int id);  // Constructeur par id
  Machine() {}      // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Machine& M);
};

class Ressource {
 private:
  string nom;
  int prix;

 public:
  Ressource(const string _nom, int _prix);  // Constructeur
  Ressource(int id);                        // Constructur par id
  Ressource() {}                            // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Ressource& R);
};

class Stock {
 private:
  Ressource R;
  int nombre;

 public:
  Stock(const Ressource& _R, int _nombre);  // Constructeur
  Stock(int id);                            // COnstructeur par id
  Stock() {}                                // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Stock& S);
};

class QuantiteRessource {
 private:
  Ressource R;
  int quantite;

 public:
  QuantiteRessource(const Ressource& _R, int _quantite);  // Constructeur
  QuantiteRessource(int id);                              // COnstructeur par id
  QuantiteRessource() {}  // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const QuantiteRessource& Q);
};

class Etape {
 private:
  string nom;
  Machine M;
  QuantiteRessource Q;
  int duree;
  Etape* etapeSuivante = nullptr;

 public:
  Etape(const string _nom, const Machine& _M, const QuantiteRessource& _Q,
        int _duree);  // Constructeur
  Etape(int id);      // Constructeur par id
  Etape() {}          // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Etape& E);
};

class Produit {
 private:
  string nom;
  int prix;
  Etape premiereEtape;

 public:
  Produit(const string _nom, int _prix,
          const Etape& _premiereEtape);  // Constructeur
  Produit(int id);                       // Constructeur par id
  Produit() {};                          // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Produit& P);
};

class Usine {
 private:
  string nom;
  Ville ville;
  int surface;
  vector<Machine> machines;
  vector<Stock> stocks;

 public:
  Usine(const string _nom, const Ville& _ville, int _surface);  // Constructeur
  Usine(int id);                      // Constructeur par id
  Usine() {};                         // Constructeur par defaut
  void addMachine(const Machine& M);  // Ajoute une machine
  void addStock(const Stock& S);      // Ajoute un stock

  friend ostream& operator<<(ostream& os, const Usine& U);
};

auto newVille(string nom, int code_postal, int prix_m2) -> Ville;
auto newVille(int id) -> Ville;

auto newSiegeSocial(const string _nom, const Ville& _ville, int _surface)
    -> SiegeSocial;
auto newSiegeSocial(int id) -> SiegeSocial;

auto newMachine(const string _nom, int _prix, const string _n_serie) -> Machine;
auto newMachine(int id) -> Machine;

auto newRessource(const string& nom, int prix) -> Ressource;
auto newRessource(int id) -> Ressource;

auto newStock(const Ressource& R, int nombre) -> Stock;
auto newStock(int id) -> Stock;

auto newQuantiteRessource(const Ressource& R, int quantite)
    -> QuantiteRessource;
auto newQuantiteRessource(int id) -> QuantiteRessource;

auto newEtape(int id) -> Etape;

auto newProduit(int id) -> Produit;

auto newUsine(int id) -> Usine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SiegeSocial2 {
 private:
  string nom;
  unique_ptr<Ville> ville;
  int surface;

 public:
  SiegeSocial2(const string _nom, const Ville& _ville,
               int _surface);  // Constructeur
  SiegeSocial2(int id);        // Constructeur par id
  SiegeSocial2() {}            // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const SiegeSocial2& siegesocial);
};

SiegeSocial2::SiegeSocial2(const string _nom, const Ville& _ville,
                           int _surface) {
  nom = _nom;
  ville = make_unique<Ville>(_ville);
  surface = _surface;
}

SiegeSocial2::SiegeSocial2(int id) {
  cpr::Response r = cpr::Get(
      cpr::Url{"http://localhost:8000/siegesocial/" + to_string(id) + "/"});

  r.text;

  auto j = json::parse(r.text);
  nom = j["Nom"];
  ville = make_unique<Ville>(newVille(j["ville_id"]));
  surface = j["Surface"];
}

ostream& operator<<(ostream& os, const SiegeSocial2& siegesocial) {
  os << "Siège social:" << endl;
  os << "\tNom:" << siegesocial.nom << endl;
  os << "\t" << *siegesocial.ville;
  os << "\tSurface:" << siegesocial.surface << endl;
  return os;
}

auto newSiegeSocial2(const string _nom, const Ville& _ville, int _surface)
    -> SiegeSocial2;
auto newSiegeSocial2(int id) -> SiegeSocial2;

auto newSiegeSocial2(const string _nom, const Ville& _ville, int _surface)
    -> SiegeSocial2 {
  SiegeSocial2 siege(_nom, _ville, _surface);
  cout << siege << endl;
  return siege;
}

auto newSiegeSocial2(int id) -> SiegeSocial2 {
  SiegeSocial2 S(id);
  return S;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Stock2 {
 private:
  unique_ptr<Ressource> ressource;
  int nombre;

 public:
  Stock2(const Ressource& _R, int _nombre);  // Constructeur
  Stock2(int id);                            // COnstructeur par id
  Stock2() {}                                // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const Stock2& S);
};

Stock2::Stock2(const Ressource& _R, int _nombre) {
  ressource = make_unique<Ressource>(_R);
  nombre = _nombre;
}

Stock2::Stock2(int id) {
  cpr::Response r =
      cpr::Get(cpr::Url{"http://localhost:8000/stock/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  ressource = make_unique<Ressource>(newRessource(j["ressource_id"]));
  nombre = j["En stock"];
}

ostream& operator<<(ostream& os, const Stock2& S) {
  os << "Stock" << endl;
  os << "\t" << *S.ressource;
  os << "\tNombre: " << S.nombre << endl;
  return os;
}

auto newStock2(const Ressource& R, int nombre) -> Stock2;
auto newStock2(int id) -> Stock2;

auto newStock2(const Ressource& R, int nombre) -> Stock2 {
  Stock2 S(R, nombre);
  cout << S << endl;
  return S;
}

auto newStock2(int id) -> Stock2 {
  Stock2 S(id);
  return S;
}

///////////////////////////////////////////////////////////////////////////////////
class QuantiteRessource2 {
 private:
  unique_ptr<Ressource> R;
  int quantite;

 public:
  QuantiteRessource2(const Ressource& _R, int _quantite);  // Constructeur
  QuantiteRessource2(int id);  // COnstructeur par id
  QuantiteRessource2() {}      // Constructeur par defaut

  friend ostream& operator<<(ostream& os, const QuantiteRessource2& Q);
};

auto newQuantiteRessource2(const Ressource& R, int quantite)
    -> QuantiteRessource2;
auto newQuantiteRessource2(int id) -> QuantiteRessource2;

QuantiteRessource2::QuantiteRessource2(const Ressource& _R, int _quantite) {
  R = make_unique<Ressource>(_R);
  quantite = _quantite;
}

QuantiteRessource2::QuantiteRessource2(int id) {
  cpr::Response r = cpr::Get(cpr::Url{
      "http://localhost:8000/quantiteressource/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  R = make_unique<Ressource>(newRessource(j["ressource_id"]));
  quantite = j["Quantite"];
}

ostream& operator<<(ostream& os, const QuantiteRessource2& Q) {
  os << "Quantite de Ressource:" << endl;
  os << "\t" << *Q.R;
  os << "\tQuantite:" << Q.quantite << endl;
  return os;
}

auto newQuantiteRessource2(const Ressource& R, int quantite)
    -> QuantiteRessource2 {
  QuantiteRessource2 Q(R, quantite);
  return Q;
}

auto newQuantiteRessource2(int id) -> QuantiteRessource2 {
  QuantiteRessource2 Q(id);
  return Q;
}

////////////////////////////////////////////////////////////////////////////////
class Etape2 {
 private:
  string nom;
  unique_ptr<Machine> M;
  unique_ptr<QuantiteRessource2> Q;
  int duree;
  optional<unique_ptr<Etape2>> etapeSuivante;

 public:
  Etape2(const string _nom, const Machine& _M, const QuantiteRessource2& _Q,
         int _duree);  // Constructeur
  Etape2(int id);      // Constructeur par id
  Etape2() {}          // Constructeur par defaut

  void getEtapeSuivante(int id);

  friend ostream& operator<<(ostream& os, const Etape2& E);
};

auto newEtape2(int id) -> Etape2;

// Etape2::Etape2(const string _nom, const Machine& _M, const
// QuantiteRessource2& _Q, int _duree) {
//   nom = _nom;
//   M = make_unique<Machine>(_M);
//   Q = make_unique<QuantiteRessource2>(1); // Mettre les paramètres du
//   constructeurs duree = _duree;
// }

Etape2::Etape2(int id) {
  cpr::Response r =
      cpr::Get(cpr::Url{"http://localhost:8000/etape/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  nom = j["Nom"];
  M = make_unique<Machine>(j["machine_id"]);
  Q = make_unique<QuantiteRessource2>(j["quantite_ressource_id"]);
  duree = j["Durée"];
  if (j["etape_suivante_id"] != "none") {
    etapeSuivante = make_unique<Etape2>(j["etape_suivante_id"]);
  }
}

ostream& operator<<(ostream& os, const Etape2& E) {
  os << "Etape:" << endl;
  os << "\tNom:" << E.nom << endl;
  os << "\t" << *E.M << endl;
  os << "\t" << *E.Q << endl;
  os << "\tDuree:" << E.duree << endl;
  if (E.etapeSuivante) {
    os << "\t" << E.etapeSuivante << endl;
  }
  return os;
}

auto newEtape2(int id) -> Etape2 {
  // Etape2 E(id);
  Etape2 E;
  return E;
}

//////////////////////////////////////////////
// Main

int main() {
  Etape2 E(1);

  cout << E << endl;

  return 0;
}

////////////////////////////////////////////////
// Definitions des fonctions/methodes

///////////////////
/// Ville

Ville::Ville(int _code_postal, string _nom, int _prix_m2) {
  nom = _nom;
  code_postal = _code_postal;
  prix_m2 = _prix_m2;
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
  os << "\tPrix m²:" << ville.prix_m2 << "\n";

  return os;
}

auto newVille(string nom, int code_postal, int prix_m2) -> Ville {
  Ville V(code_postal, nom, prix_m2);
  cout << V << endl;
  return V;
}

auto newVille(int id) -> Ville {
  Ville V(id);
  return V;
}

///////////////////
/// Siege social

SiegeSocial::SiegeSocial(const string _nom, const Ville& _ville, int _surface) {
  nom = _nom;
  ville = _ville;
  surface = _surface;
}

SiegeSocial::SiegeSocial(int id) {
  cpr::Response r = cpr::Get(
      cpr::Url{"http://localhost:8000/siegesocial/" + to_string(id) + "/"});

  r.text;

  auto j = json::parse(r.text);
  nom = j["Nom"];
  ville = newVille(j["ville_id"]);
  surface = j["Surface"];
}

ostream& operator<<(ostream& os, const SiegeSocial& siegesocial) {
  os << "Siege social:\n";
  os << "\tNom:" << siegesocial.nom << endl;
  os << "\t" << siegesocial.ville << endl;
  os << "\tSurface:" << siegesocial.surface << endl;

  return os;
}

auto newSiegeSocial(const string _nom, const Ville& _ville, int _surface)
    -> SiegeSocial {
  SiegeSocial siege(_nom, _ville, _surface);
  cout << siege << endl;
  return siege;
}

auto newSiegeSocial(int id) -> SiegeSocial {
  SiegeSocial S(id);
  return S;
}

///////////////////
/// Machine
Machine::Machine(int id) {
  cpr::Response r = cpr::Get(
      cpr::Url{"http://localhost:8000/machine/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  nom = j["Nom"];
  prix = j["Prix"];
  n_serie = j["Num_serie"];
}

Machine::Machine(const string _nom, int _prix, const string _n_serie) {
  nom = _nom;
  prix = _prix;
  n_serie = _n_serie;
}

ostream& operator<<(ostream& os, const Machine& M) {
  os << "Machine:" << endl;
  os << "\tNom:" << M.nom << endl;
  os << "\tN serie:" << M.n_serie << endl;
  os << "\tPrix:" << M.prix << endl;
  return os;
}

auto newMachine(const string _nom, int _prix, const string _n_serie)
    -> Machine {
  Machine M(_nom, _prix, _n_serie);
  cout << M << endl;
  return M;
}

auto newMachine(int id) -> Machine {
  Machine M(id);
  return M;
}

///////////////////
/// Ressource
Ressource::Ressource(const string _nom, int _prix) {
  nom = _nom;
  prix = _prix;
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
  os << "\tPrix:" << R.prix << endl;
  return os;
}

auto newRessource(const string& nom, int prix) -> Ressource {
  Ressource R(nom, prix);
  cout << R << endl;
  return R;
}

auto newRessource(int id) -> Ressource {
  Ressource R(id);
  return R;
}

///////////////////
/// Stock
Stock::Stock(const Ressource& _R, int _nombre) {
  R = _R;
  nombre = _nombre;
}

Stock::Stock(int id) {
  cpr::Response r =
      cpr::Get(cpr::Url{"http://localhost:8000/stock/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  R = newRessource(j["ressource_id"]);
  nombre = j["En stock"];
}

ostream& operator<<(ostream& os, const Stock& S) {
  os << "Stock:" << endl;
  os << "\t" << S.R << endl;
  os << "\tNombre:" << S.nombre;
  return os;
}

auto newStock(const Ressource& R, int nombre) -> Stock {
  Stock S(R, nombre);
  cout << S << endl;
  return S;
}

auto newStock(int id) -> Stock {
  Stock S(id);
  return S;
}

///////////////////
/// Quantite de ressource
QuantiteRessource::QuantiteRessource(const Ressource& _R, int _quantite) {
  R = _R;
  quantite = _quantite;
}

QuantiteRessource::QuantiteRessource(int id) {
  cpr::Response r = cpr::Get(cpr::Url{
      "http://localhost:8000/quantiteressource/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  R = newRessource(j["ressource_id"]);
  quantite = j["Quantite"];
}

ostream& operator<<(ostream& os, const QuantiteRessource& Q) {
  os << "Quantite de Ressource:" << endl;
  os << "\t" << Q.R << endl;
  os << "\tQuantite:" << Q.quantite << endl;
  return os;
}

auto newQuantiteRessource(const Ressource& R, int quantite)
    -> QuantiteRessource {
  QuantiteRessource Q(R, quantite);
  return Q;
}

auto newQuantiteRessource(int id) -> QuantiteRessource {
  QuantiteRessource Q(id);
  return Q;
}

///////////////////
/// Etape
Etape::Etape(const string _nom, const Machine& _M, const QuantiteRessource& _Q,
             int _duree) {
  nom = _nom;
  M = _M;
  Q = _Q;
  duree = _duree;
}

Etape::Etape(int id) {
  cpr::Response r =
      cpr::Get(cpr::Url{"http://localhost:8000/etape/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  nom = j["Nom"];
  M = newMachine(j["machine_id"]);
  Q = newQuantiteRessource(j["quantite_ressource_id"]);
  duree = j["Durée"];
  if (j["etape_suivante_id"] != "none") {
    etapeSuivante = new Etape;
    *etapeSuivante = newEtape(j["etape_suivante_id"]);
  }
}

ostream& operator<<(ostream& os, const Etape& E) {
  os << "Etape:" << endl;
  os << "\tNom:" << E.nom << endl;
  os << "\t" << E.M << endl;
  os << "\t" << E.Q << endl;
  os << "\tDuree:" << E.duree << endl;
  if (E.etapeSuivante != nullptr) {
    os << "\t" << *(E.etapeSuivante) << endl;
  }
  return os;
}

auto newEtape(int id) -> Etape {
  Etape E(id);
  return E;
}

///////////////////
/// Produit
Produit::Produit(const string _nom, int _prix, const Etape& _premiereEtape) {
  nom = _nom;
  prix = _prix;
  premiereEtape = _premiereEtape;
}

Produit::Produit(int id) {
  cpr::Response r = cpr::Get(
      cpr::Url{"http://localhost:8000/produit/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  nom = j["Nom"];
  prix = j["Prix"];
  premiereEtape = newEtape(j["premiere_etape_id"]);
}

ostream& operator<<(ostream& os, const Produit& P) {
  os << "Produit:" << endl;
  os << "\tNom:" << P.nom << endl;
  os << "\tPrix:" << P.prix << endl;
  os << "\t" << P.premiereEtape << endl;
  return os;
}

auto newProduit(int id) -> Produit {
  Produit P(id);
  return P;
}

//////////////////
/// Usine
Usine::Usine(const string _nom, const Ville& _ville, int _surface) {
  nom = _nom;
  ville = _ville;
  surface = _surface;
}

Usine::Usine(int id) {
  cpr::Response r =
      cpr::Get(cpr::Url{"http://localhost:8000/usine/" + to_string(id) + "/"});

  r.text;
  auto j = json::parse(r.text);
  nom = j["Nom"];
  surface = j["Surface"];
  ville = newVille(j["ville_id"]);
  vector<int> myMachines = j["machines_id"].get<vector<int>>();
  for (int i = 0; i < myMachines.size(); i++) {
    machines.push_back(
        newMachine(myMachines[i]));  // Ajout des machines a usine
  }
  vector<int> myStocks = j["stocks_id"].get<vector<int>>();
  for (int i = 0; i < myStocks.size(); i++) {
    stocks.push_back(newStock(myStocks[i]));  // Ajout des stocks a usine
  }
}

ostream& operator<<(ostream& os, const Usine& U) {
  os << "Usine:" << endl;
  os << "\tNom:" << U.nom << endl;
  os << "\t" << U.ville << endl;
  os << "\tSurface:" << U.surface << endl;
  for (int i = 0; i < U.machines.size(); i++) {
    os << "\t" << U.machines[i] << endl;
  }
  for (int i = 0; i < U.stocks.size(); i++) {
    os << "\t" << U.stocks[i] << endl;
  }
  return os;
}

void Usine::addMachine(const Machine& M) { machines.push_back(M); }

void Usine::addStock(const Stock& S) { stocks.push_back(S); }

auto newUsine(int id) -> Usine {
  Usine U(id);
  return U;
}
