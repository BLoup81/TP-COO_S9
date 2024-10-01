"""
URL configuration for crayon project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""

from django.contrib import admin
from django.urls import path
from high_level import views

# Ville
urlpatterns = [
    path("admin/", admin.site.urls),
    path("ville/<int:pk>/", views.viewVille.as_view(), name="ville"),
]

# Usine
urlpatterns = [
    path("admin/", admin.site.urls),
    path("usine/<int:pk>/", views.viewUsine.as_view(), name="usine"),
]

# Stock
urlpatterns = [
    path("admin/", admin.site.urls),
    path("stock/<int:pk>/", views.viewStock.as_view(), name="stock"),
]

# Machine
urlpatterns = [
    path("admin/", admin.site.urls),
    path("machine/<int:pk>/", views.viewMachine.as_view(), name="machine"),
]

# SiegeSocial
urlpatterns = [
    path("admin/", admin.site.urls),
    path("siegesocial/<int:pk>/", views.viewSiegeSocial.as_view(), name="siege social"),
]

# Ressource
urlpatterns = [
    path("admin/", admin.site.urls),
    path("ressource/<int:pk>/", views.viewRessource.as_view(), name="ressource"),
]

# QuantiteRessource
urlpatterns = [
    path("admin/", admin.site.urls),
    path(
        "quatiteressource/<int:pk>/",
        views.viewQuantiteRessource.as_view(),
        name="quantite ressource",
    ),
]

# Etape
urlpatterns = [
    path("admin/", admin.site.urls),
    path("etape/<int:pk>/", views.viewEtape.as_view(), name="etape"),
]

# Produit
urlpatterns = [
    path("admin/", admin.site.urls),
    path("produit/<int:pk>/", views.viewProduit.as_view(), name="produit"),
]
