# Create your models here.
from django.db import models


class Ville(models.Model):
    nom = models.CharField(max_length=100)
    code_postal = models.IntegerField(max_length=5)
    prix_m2 = models.IntegerField(max_length=100)

    def __str__(self):
        return self.nom

    def json(self):
        d = {"Nom": self.nom, "Code postal": self.code_postal, "Prix/m2": self.prix_m2}
        return d


class Local(models.Model):
    nom = models.CharField(max_length=100)
    ville = models.ForeignKey(Ville, on_delete=models.PROTECT)
    surface = models.IntegerField()

    class Meta:
        abstract = True


class SiegeSocial(Local):
    def __str__(self):
        return self.nom

    def json(self):
        d = {"Nom": self.nom, "Ville": self.ville, "Surface": self.surface}
        return d


class Machine(models.Model):
    nom = models.CharField(max_length=100)
    prix = models.IntegerField(max_length=100)
    n_serie = models.CharField(max_length=100)

    def __str__(self):
        return self.nom

    def costs(self):
        return self.prix

    def json(self):
        d = {"Nom": self.nom, "Prix": self.prix, "Num_serie": self.n_serie}
        return d


class Objet(models.Model):
    nom = models.CharField(max_length=100)
    prix = models.IntegerField(max_length=100)

    def __str__(self):
        return self.nom

    class Meta:
        abstract = True


class Ressource(Objet):
    def __str__(self):
        return self.nom

    def json(self):
        d = {"Nom": self.nom, "Prix": self.prix}
        return d


class QuantiteRessource(models.Model):
    ressource = models.ForeignKey(Ressource, on_delete=models.CASCADE)
    quantite = models.IntegerField(max_length=100)

    def __str__(self):
        return self.ressource.nom + " : " + str(self.quantite)

    def json(self):
        d = {"Nom": self.ressource.nom, "Quantite": self.quantite}
        return d

    def costs(self):
        return self.quantite * self.ressource.prix


class Etape(models.Model):
    nom = models.CharField(max_length=100)
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    quantite_ressource = models.ForeignKey(QuantiteRessource, on_delete=models.PROTECT)
    duree = models.IntegerField(max_length=100)
    etape_suivante = models.ForeignKey(
        "self", blank=True, null=True, on_delete=models.CASCADE
    )

    def __str__(self):
        return self.nom

    def json(self):
        d = {
            "Nom": self.nom,
            "Machine": self.machine.nom,
            "Qantite ressource": self.quantite_ressource.json(),
            "duree": self.duree,
            "Etape suivante": self.etape_suivante.nom,
        }
        return d


class Stock(models.Model):
    ressource = models.ForeignKey(Ressource, null=True, on_delete=models.CASCADE)
    nombre = models.IntegerField(max_length=100)  # Nombre de ressources différentes

    def __str__(self):
        return self.ressource.nom + " (" + str(self.nombre) + ")"

    def costs(self):
        return self.ressource.prix * self.nombre

    def json(self):
        d = {
            "Ressource": self.ressource.nom,
            "Nombre": self.nombre,
            "Usine": self.usine.json(),
        }
        return d


class Produit(Objet):
    premiere_etape = models.CharField(max_length=1000)

    def __str__(self):
        return self.nom

    def json(self):
        d = {"Premiere Etape": self.premiere_etape.nom}
        return d


class Usine(Local):
    machines = models.ManyToManyField(Machine)
    stock = models.ManyToManyField(Stock)

    def costs(self):
        cout = self.surface * self.ville.prix_m2

        stockage = self.stock.all()
        for i in range(len(stockage)):
            cout += stockage[i].costs()

        machi = self.machines.all()
        for i in range(len(machi)):
            cout += machi[i].costs()

        return cout

    def __str__(self):
        return self.nom
