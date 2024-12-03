# Create your views here.
from django.http.response import HttpResponse as HttpResponse
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
        return JsonResponse(self.object.json_extend(), safe=False)


class viewStock(DetailView):
    model = models.Stock

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json_extend(), safe=False)


class viewMachine(DetailView):
    model = models.Machine

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)


class viewSiegeSocial(DetailView):
    model = models.SiegeSocial

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json_extend(), safe=False)


class viewRessource(DetailView):
    model = models.Ressource

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)


class viewQuantiteRessource(DetailView):
    model = models.QuantiteRessource

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json_extend(), safe=False)


class viewEtape(DetailView):
    model = models.Etape

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json_extend(), safe=False)


class viewProduit(DetailView):
    model = models.Produit

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json_extend(), safe=False)


class ApiView(DetailView):
    model = models.Usine

    def get_context_data(self, **kwargs):
        # Appel à la méthode de la classe parente pour obtenir le contexte par défaut
        context = super().get_context_data(**kwargs)

        # Récupérer toutes les usines et villes
        context["usine"] = models.Usine.objects.all()
        context["villes"] = models.Ville.objects.all()
        context["stocks"] = models.Stock.objects.all()
        context["machines"] = models.Machine.objects.all()
        context["siegeSocials"] = models.SiegeSocial.objects.all()
        context["ressources"] = models.Ressource.objects.all()
        context["quantiteRessources"] = models.QuantiteRessource.objects.all()
        context["etapes"] = models.Etape.objects.all()
        context["produits"] = models.Produit.objects.all()

        # Vous pouvez ajouter d'autres données ici si nécessaire.
        return context

    def setIdTab(self, context, type, **response_kwargs):
        context_data = self.get_context_data(**context)

        d = []
        for i in range(len(context_data[type])):
            d.append(context_data[type][i].id)
        return d

    def render_to_response(self, context, **response_kwargs):
        # Récupérer les données contextuelles via get_context_data()

        response_data = {
            "Usines": self.setIdTab(context, "usine", **response_kwargs),
            "Villes": self.setIdTab(context, "villes", **response_kwargs),
            "Stocks": self.setIdTab(context, "stocks", **response_kwargs),
            "Machines": self.setIdTab(context, "machines", **response_kwargs),
            "Sieges sociaux": self.setIdTab(context, "siegeSocials", **response_kwargs),
            "Ressources": self.setIdTab(context, "ressources", **response_kwargs),
            "Quantités de ressources": self.setIdTab(
                context, "quantiteRessources", **response_kwargs
            ),
            "Etapes": self.setIdTab(context, "etapes", **response_kwargs),
            "Produits": self.setIdTab(context, "produits", **response_kwargs),
        }

        return JsonResponse(response_data, safe=False)
