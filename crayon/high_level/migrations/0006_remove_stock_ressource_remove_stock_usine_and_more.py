# Generated by Django 5.1.1 on 2024-09-29 17:12

from django.db import migrations, models


class Migration(migrations.Migration):
    dependencies = [
        ("high_level", "0005_alter_machine_n_serie"),
    ]

    operations = [
        migrations.RemoveField(
            model_name="stock",
            name="ressource",
        ),
        migrations.RemoveField(
            model_name="stock",
            name="usine",
        ),
        migrations.AddField(
            model_name="stock",
            name="quantiteRessource",
            field=models.ManyToManyField(to="high_level.quantiteressource"),
        ),
    ]