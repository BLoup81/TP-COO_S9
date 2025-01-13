# Create your models here.
from django.db import models


class Ville(models.Model):
    nom = models.CharField(max_length=100)  # Affectation d'une chaine de caracteres
    code_postal = models.IntegerField(max_length=5)  # Affectation d'un entier
    prix_m2 = models.IntegerField(max_length=100)  # Affectation d'un entier

    def __str__(self):  # Fonction d'affichage pour Django (dans ce cas)
        return self.nom  # Affiche uniquement le nom

    def json(self):  # Fonction de serialisation par json
        d = {  # Creation d'un dictionnaire
            "Nom": self.nom,
            "Code postal": self.code_postal,
            "Prix/m2": self.prix_m2,
        }
        return d


class Local(models.Model):
    nom = models.CharField(max_length=100)
    ville = models.ForeignKey(
        Ville, on_delete=models.PROTECT
    )  # Affection d'une instance d'une autre classe
    surface = models.IntegerField()

    class Meta:  # Local est une classe abstraite
        abstract = True


class SiegeSocial(Local):
    def __str__(self):
        return self.nom

    def json(self):
        d = {"Nom": self.nom, "Ville": self.ville.nom, "Surface": self.surface}
        return d

    def json_extend(self):
        d = {
            "Nom": self.nom,
            "ville_id": self.ville.id,  # Serialise l'identifiant de la ville de la base de donnees
            "Ville": self.ville.json(),  # Srialise la ville et ses attribut
            "Surface": self.surface,
        }
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

    def costs(self):  # Retourne la valeur monetaire de la quantite de ressource
        return self.quantite * self.ressource.prix

    def json_extend(self):
        d = {
            "ressource_id": self.ressource.id,
            "Ressource": self.ressource.json(),
            "Quantite": self.quantite,
        }
        return d


class Etape(models.Model):
    nom = models.CharField(max_length=100)
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    quantite_ressource = models.ForeignKey(QuantiteRessource, on_delete=models.PROTECT)
    duree = models.IntegerField(max_length=100)
    etape_suivante = models.ForeignKey(
        "Etape",
        blank=True,
        null=True,
        on_delete=models.CASCADE,  # L'etape suivante peut etre null (pas d'etape suivante)
    )

    def __str__(self):
        return self.nom

    def json(self):
        d = {
            "Nom": self.nom,
            "Machine": self.machine.nom,
            "Ressource": self.quantite_ressource.ressource.nom,
            "Durée": self.duree,
        }
        return d

    def json_extend(self):
        d = {
            "Nom": self.nom,
            "machine_id": self.machine.id,
            "Machine": self.machine.json(),
            "quantite_ressource_id": self.quantite_ressource.id,
            "Quantité de ressources": self.quantite_ressource.json_extend(),
            "Durée": self.duree,
        }
        if self.etape_suivante is not None:  # Test si l'etape suivante existe
            d["etape_suivante_id"] = (
                self.etape_suivante.id
            )  # Si elle existe, la serialise avec son identifiant
            d["Etape suivante"] = self.etape_suivante.json_extend()
        else:
            d["etape_suivante_id"] = (
                "none"  # Sinon, print none dans le json pour informer le code C++ de sa non-existence
            )
            d["Etape suivante"] = "none"

        return d


class Stock(models.Model):
    ressource = models.ForeignKey(Ressource, null=True, on_delete=models.CASCADE)
    nombre = models.IntegerField(max_length=100)

    def __str__(self):  # Affiche le nom de la ressource en stock et la quantité
        return self.ressource.nom + " (" + str(self.nombre) + ")"

    def costs(self):  # Calcul la valeur monetaire du stock
        return self.ressource.prix * self.nombre

    def json(self):
        d = {"Ressource": self.ressource.nom, "Nombre": self.nombre}
        return d

    def json_extend(self):
        d = {
            "ressource_id": self.ressource.id,
            "Ressource": self.ressource.json(),
            "En stock": self.nombre,
        }
        return d


class Produit(Objet):
    premiere_etape = models.ForeignKey(Etape, null=True, on_delete=models.CASCADE)

    def __str__(self):
        return self.nom

    def json(self):
        d = {"Nom": self.nom, "Prix": self.prix}
        return d

    def json_extend(self):
        d = {
            "Nom": self.nom,
            "Prix": self.prix,
            "premiere_etape_id": self.premiere_etape.id,
            "Etape": self.premiere_etape.json_extend(),
        }
        return d


class Usine(Local):
    machines = models.ManyToManyField(Machine)
    stock = models.ManyToManyField(Stock)

    def costs(self):
        cout = self.surface * self.ville.prix_m2  # Calcul du cout d'achat des locaux

        stockage = self.stock.all()  # Affectation de tous les stocks a une variable
        for i in range(len(stockage)):
            cout += stockage[i].costs()  # Ajout des couts des stocks au cout total

        machi = self.machines.all()  # Affectation de toutes les machines a une variable
        for i in range(len(machi)):
            cout += machi[i].costs()  # Ajout des couts des machines au cout total

        return cout  # Retourne le cout total

    def __str__(self):
        return self.nom

    def json(self):
        d = {"Nom": self.nom, "Ville": self.ville.json(), "Surface": self.surface}
        return d

    def infoStockId(self):
        # Le nombre de stocks etant variable, cette methode creer
        # un tableau de serialisation des stocks pour les identifiants
        myStocks = self.stock.all()
        d = []
        for i in range(len(myStocks)):
            d.append(myStocks[i].id)  # Ajoute le i_eme identifiant au tableau
        return d

    def InfoStock(self):
        # Creer un tableau de serialisation pour les informations des stocks
        myStocks = self.stock.all()
        d = []
        for i in range(len(myStocks)):
            d.append(myStocks[i].json_extend())
        return d

    def infoMachineId(self):
        # Le nombre de machines etant variable, cette methode creer
        # un tableau de serialisation des machines pour les identifiants
        myMachines = self.machines.all()
        d = []
        for j in range(len(myMachines)):
            d.append(myMachines[j].id)
        return d

    def infoMachine(self):
        # Creer un tableau de serialisation pour les informations des machines
        myMachines = self.machines.all()
        d = []
        for j in range(len(myMachines)):
            d.append(myMachines[j].json())
        return d

    def json_extend(self):
        d = {
            "Nom": self.nom,
            "ville_id": self.ville.id,
            "Ville": self.ville.json(),
            "Surface": self.surface,
            "machines_id": self.infoMachineId(),
            "Machines": self.infoMachine(),
            "stocks_id": self.infoStockId(),
            "Stocks": self.InfoStock(),
        }
        return d

    def achatStock(self, produit, recette):
        nbProduit = recette / produit.prix  # Calcul du nombre de produit a realiser

        etape = produit.premiere_etape
        while etape is not None:  # Tant qu'il y a une etape pour realiser le produit
            sameRessource = False  # Drapeau pour savoir si il existe un stock correspondant a la ressource de l'etape
            qt = etape.quantite_ressource
            stocks = self.stock.all()  # Recupere les stocks de l'usine

            for i in range(len(stocks)):  # Parcours les stocks de l'usine
                if (
                    stocks[i].ressource.nom == qt.ressource.nom
                ):  # Si il existe un stock correspondant a la ressource de l'etape
                    nombreRessource = (
                        nbProduit * qt.quantite - stocks[i].nombre
                    )  # Calcul de la difference de quantite
                    sameRessource = True  # Leve de drapeau car il existe un stock correspondant a la ressource
                    if (
                        nombreRessource > 0
                    ):  # Si il n'y a pas assez de ressource dans le stock
                        print(
                            nombreRessource,
                            "de",
                            qt.ressource.nom,
                            "ont ete achete pour",
                            produit.prix,
                            "euros l'unite.",
                        )
                        stocks[
                            i
                        ].nombre += nombreRessource  # Completion du stock pour realiser les produits necessaire
                        stocks[i].save()  # Sauvegarde dans la base de donnees

            if (
                sameRessource is False
            ):  # Si il n'existe pas de stock correspondant a la ressource de l'etape
                nombreRessource = (
                    nbProduit * qt.quantite
                )  # Quantite de ressource a acheter
                print("Creation d'un stock de", nombreRessource, "de", qt.ressource.nom)
                nouveau_stock = Stock.objects.create(
                    ressource=qt.ressource, nombre=nombreRessource
                )  # Creation d'un nouveau stock
                self.stock.add(
                    nouveau_stock
                )  # Ajout du nouveau stock a la base de donnees

            etape = etape.etape_suivante
