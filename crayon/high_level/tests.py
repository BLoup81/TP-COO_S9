# Create your tests here.
from django.test import TestCase
from .models import Machine, Usine, Ressource, QuantiteRessource, Stock, Ville


class MachineModelTests(TestCase):
    def test_machine_creation(self):
        self.assertEqual(Machine.objects.count(), 0)
        Machine.objects.create(nom="scie", prix=1_000, n_serie="1683AI2")
        self.assertEqual(Machine.objects.count(), 1)


class QuantiteRessourceModelTests(TestCase):
    def test_quantite_ressource_creation(self):
        self.assertEqual(QuantiteRessource.objects.count(), 0)
        ressource1 = Ressource.objects.create(nom="bois", prix=100)
        QuantiteRessource.objects.create(quantite=20, ressource=ressource1)
        self.assertEqual(QuantiteRessource.objects.count(), 1)


class UsineCostTests(TestCase):
    def test_usine_creation(self):
        self.assertEqual(Usine.objects.count(), 0)  # Verification nombre usine = 0
        self.assertEqual(
            Ressource.objects.count(), 0
        )  # Verification nombre ressource = 0
        self.assertEqual(Stock.objects.count(), 0)  # Verification nombre stock = 0
        self.assertEqual(Ville.objects.count(), 0)  # Verification nombre ville = 0
        self.assertEqual(Machine.objects.count(), 0)  # Verification nombre machine = 0
        self.ressource1 = Ressource.objects.create(
            nom="bois", prix=10
        )  # Creation de la ressource bois
        self.ressource2 = Ressource.objects.create(
            nom="mine", prix=15
        )  # Creation de la ressource mine
        self.stock1 = Stock.objects.create(
            nombre=1_000, ressource=self.ressource1
        )  # Creation stock de bois
        self.stock2 = Stock.objects.create(
            nombre=50, ressource=self.ressource2
        )  # Creation stock de mine
        self.ville = Ville.objects.create(
            nom="Toulouse", prix_m2=2_000, code_postal=31_000
        )  # Creation de la ville
        self.machine1 = Machine.objects.create(
            nom="scie", prix=1_000, n_serie="15655"
        )  # Creation de la machine 1
        self.machine2 = Machine.objects.create(
            nom="perceuse", prix=2_000, n_serie="654484"
        )  # Creation de la machine 2
        self.usine = Usine.objects.create(
            nom="airb", surface=50, ville=self.ville
        )  # Creation de l'usine
        self.usine.machines.add(
            self.machine1, self.machine2
        )  # Ajout des machines a l'usine
        self.usine.stock.add(self.stock1, self.stock2)  # Ajout des stocks a l'usine
        self.assertEqual(self.usine.costs(), 113750)  # Verification du cout de l'usine
        self.assertEqual(
            Usine.objects.count(), 1
        )  # Verification du nombre d'usine creee
