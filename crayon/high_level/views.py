# Create your views here.
from django.views.generic import DetailView
from . import models

class viewVille(DetailView):
    v = models.Ville

    def render_to_response(self, context, **response_kwargs):
        return v.json()
