#include <cpr/cpr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class Ville {
 private:
  int code_postal;
  string nom;
  int prix_m2;

 public:
  Ville(int _code_postal, string _nom, int _prix_m2);
  Ville(int id);
  auto getName() -> string;
  auto jsonVille();  // Communication entre python et C++
};

Ville::Ville(int _code_postal, string _nom, int _prix_m2) {
  nom = _nom;
  code_postal = _code_postal;
  prix_m2 = _prix_m2;
}

auto Ville::getName() -> string { return nom; }

Ville::Ville(int id) {
  cpr::Response r = cpr::Get(
      cpr::Url{"http://localhost:8000/ville/" + to_string(id) +
               "/"});  //,
                       // cpr::Parameters{{"ville", "true"}, {"key", "value"}});
  // r.status_code;
  // r.header["content-type"];
  r.text;
  // cout << r.text << endl;
}

auto jsonVille() {
  json j;
  j["Nom"] = nom;
  j["Code postal"] = code_postal;
  j["Prix/m2"] = prix_m2;
}

int main() {
  Ville V1(3100, "Toulouse", 2000);
  Ville V2(1);

  return 0;
}
