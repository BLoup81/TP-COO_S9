# Create your views here.
from django.views.generic import DetailView
from django.http import JsonResponse
from . import models

class viewVille(DetailView):
    model = models.Ville

    def render_to_response(self, context, **response_kwargs):
        return JsonResponse(self.object.json(), safe=False)
