# Create your views here.
from django.views.generic import DetailView
from django.http import JsonResponse
from . import models


class viewVille(DetailView):
    model = models.Ville

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)


class viewUsine(DetailView):
    model = models.Usine

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)


class viewStock(DetailView):
    model = models.Stock

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)


class viewMachine(DetailView):
    model = models.Machine

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)


class viewSiegeSocial(DetailView):
    model = models.SiegeSocial

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)


class viewRessource(DetailView):
    model = models.Ressource

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)


class viewQuantiteRessource(DetailView):
    model = models.QuantiteRessource

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)


class viewEtape(DetailView):
    model = models.Etape

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)


class viewProduit(DetailView):
    model = models.Produit

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)
