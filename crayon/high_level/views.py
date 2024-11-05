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


# class ApiView(DetailView):
#     model = models.Usine

#     def json(self,**kwargs):
#         context = super().get_context_data(**kwargs)
#         context['Usine'] = models.Usine.objects.all()
#         context['Villes'] = models.Ville.objects.all()
#         return context

#     def render_to_response(self, context, **response_kwargs):
#         return JsonResponse(self.json(), safe=False)


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

    def render_to_response(self, context, **response_kwargs):
        # Récupérer les données contextuelles via get_context_data()
        context_data = self.get_context_data(**context)

        # Sérialisation du contexte en un format approprié pour JsonResponse
        response_data = {
            "Usines": list(
                context_data["usine"].values()
            ),  # Convertit le queryset en une liste de dictionnaires
            "Villes": list(
                context_data["villes"].values()
            ),  # Même chose pour les villes
            "Stocks": list(context_data["stocks"].values()),
            "Machines": list(context_data["machines"].values()),
            "Sieges socials": list(context_data["siegeSocials"].values()),
            "Ressources": list(context_data["ressources"].values()),
            "Quantités de ressources": list(
                context_data["quantiteRessources"].values()
            ),
            "Etapes": list(context_data["etapes"].values()),
            "Produits": list(context_data["produits"].values()),
        }

        # Retourne la réponse JSON
        return JsonResponse(response_data, safe=False)
