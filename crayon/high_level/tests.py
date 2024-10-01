# Create your tests here.
from django.test import TestCase
from .models import Machine, Usine, Ressource, QuantiteRessource, Stock, Ville


class MachineModelTests(TestCase):
    def test_machine_creation(self):
        self.assertEqual(Machine.objects.count(), 0)
        Machine.objects.create(nom="scie", prix=1_000, n_serie="1683AI2")
        self.assertEqual(Machine.objects.count(), 1)


class UsineCostTests(TestCase):
    def test_usine_creation(self):
        self.assertEqual(Usine.objects.count(), 0)
        self.ressource1 = Ressource.objects.create(nom="bois", prix=10)
        self.ressource2 = Ressource.objects.create(nom="mine", prix=15)
        self.quantiteR1 = QuantiteRessource.objects.create(quantite=1_000)
        self.quantiteR1.ressource.add(self.ressource1)
        self.quantiteR1 = QuantiteRessource.objects.create(quantite=50)
        self.quantiteR2.ressource.add(self.ressource2)
        self.stock = Stock.objects.create(nombre=2)
        self.stock.add(self.quantiteR1, self.quantiteR2)
        self.ville = Ville.objects.create(
            nom="Toulouse", prix_m2=2_000, code_postal=31_000
        )
        self.machine1 = Machine.objects.create(nom="scie", prix=1_000, n_serie="15655")
        self.machine2 = Machine.objects.create(
            nom="perceuse", prix=2_000, n_serie="654484"
        )
        self.usine = Usine.objects.create(nom="airb", surface=50)
        self.usine.ville.add(self.ville)
        self.usine.stock.add(self.stock)
        self.usine.machine1.add(self.machine1, self.machine2)
        self.assertEqual(Usine.costs(), 113750)
        self.assertEqual(Usine.object.count(), 1)
