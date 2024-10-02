#include <cpr/cpr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

class Ville {
 private:
  int code_postal;
  string nom;
  int prix_m2;

 public:
  Ville(int _code_postal, string _nom, int _prix_m2);
  auto getName() -> string;
  // ostream& operator<<(ostream& os);
  void __str__();
};

Ville::Ville(int _code_postal, string _nom, int _prix_m2) {
  nom = _nom;
  code_postal = _code_postal;
  prix_m2 = _prix_m2;
}

auto Ville::getName() -> string { return nom; }

void Ville::__str__() {
  cpr::Response r =
      cpr::Get(cpr::Url{"http://localhost:8000/admin/"},
               cpr::Parameters{{"ville", "true"}, {"key", "value"}});
  r.status_code;
  r.header["content-type"];
  r.text;
  cout << r.text << endl;
}

/*
ostream& operator<<(ostream& os, const Date& dt)
{
    os << dt.mo << '/' << dt.da << '/' << dt.yr;
    return os;
}
*/

// CurlContainer<T>::CurlContainer(const std::initializer_list<T>&
// containerList) : containerList_(containerList) {}

int main() {
  Ville V1(31000, "Toulouse", 2000);
  V1.__str__();

  return 0;
}
