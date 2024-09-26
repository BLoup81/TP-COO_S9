# Create your models here.
from django.db import models


class Ville(models.Model):
    nom = models.CharField(max_length=100)
    code_postal = models.IntegerField(max_length=5)
    prix_m2 = models.IntegerField(max_length=100)

    def __str__(self):
        return self.nom


class Local(models.Model):
    nom = models.CharField(max_length=100)
    ville = models.ForeignKey(Ville, on_delete=models.PROTECT)
    surface = models.IntegerField()

    class Meta:
        abstract = True


class SiegeSocial(models.Local):
    pass


class Machine(models.Model):
    nom = models.CharField(max_length=100)
    prix = models.IntegerField(max_length=100)
    n_serie = models.IntegerField(max_length=100)

    def __str__(self):
        return self.nom


class Usine(models.Local):
    machines = models.ForeignKey(Machine, on_delete=models.CASCADE)

    def __str__(self):
        return self.ville.nom


class Objet(models.Model):
    nom = models.CharField(max_length=100)
    prix = models.IntegerField(max_length=100)

    def __str__(self):
        return self.nom

    class Meta:
        abstract = True


class Stock(models.Model):
    objet = models.ForeignKey(Objet, on_delete=models.CASCADE)
    nombre = models.IntegerField(max_length=100)

    def __str__(self):
        return self.nombre


class Ressource(models.Oblect):
    pass


class QuantiteRessource(models.Model):
    ressource = models.ForeignKey(Ressource, on_delete=models.CASCADE)
    quantite = models.IntegerField(max_length=100)

    def __str__(self):
        return self.quantite


class Etape(models.Model):
    nom = models.CharField(max_length=100)
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    quantite_ressource = models.ForeignKey(QuantiteRessource, on_delete=models.PROTECT)
    duree = models.IntegerField(max_length=100)
    # mettre etape suivante et fonction str


class Produit(models.Objet):
    premiere_etape = models.CharField(max_length=1000)

    def __str__(self):
        return self.premiere_etape
