# Generated by Django 4.2.16 on 2024-09-26 13:34

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ("high_level", "0001_initial"),
    ]

    operations = [
        migrations.CreateModel(
            name="Machine",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("nom", models.CharField(max_length=100)),
                ("prix", models.IntegerField(max_length=100)),
                ("n_serie", models.IntegerField(max_length=100)),
            ],
        ),
        migrations.CreateModel(
            name="Produit",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("nom", models.CharField(max_length=100)),
                ("prix", models.IntegerField(max_length=100)),
                ("premiere_etape", models.CharField(max_length=1000)),
            ],
            options={
                "abstract": False,
            },
        ),
        migrations.CreateModel(
            name="Ressource",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("nom", models.CharField(max_length=100)),
                ("prix", models.IntegerField(max_length=100)),
            ],
            options={
                "abstract": False,
            },
        ),
        migrations.AlterField(
            model_name="ville",
            name="code_postal",
            field=models.IntegerField(max_length=5),
        ),
        migrations.AlterField(
            model_name="ville",
            name="prix_m2",
            field=models.IntegerField(max_length=100),
        ),
        migrations.CreateModel(
            name="Usine",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("nom", models.CharField(max_length=100)),
                ("surface", models.IntegerField()),
                (
                    "machines",
                    models.ForeignKey(
                        on_delete=django.db.models.deletion.CASCADE,
                        to="high_level.machine",
                    ),
                ),
                (
                    "ville",
                    models.ForeignKey(
                        on_delete=django.db.models.deletion.PROTECT,
                        to="high_level.ville",
                    ),
                ),
            ],
            options={
                "abstract": False,
            },
        ),
        migrations.CreateModel(
            name="SiegeSocial",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("nom", models.CharField(max_length=100)),
                ("surface", models.IntegerField()),
                (
                    "ville",
                    models.ForeignKey(
                        on_delete=django.db.models.deletion.PROTECT,
                        to="high_level.ville",
                    ),
                ),
            ],
            options={
                "abstract": False,
            },
        ),
        migrations.CreateModel(
            name="QuantiteRessource",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("quantite", models.IntegerField(max_length=100)),
                (
                    "ressource",
                    models.ForeignKey(
                        on_delete=django.db.models.deletion.CASCADE,
                        to="high_level.ressource",
                    ),
                ),
            ],
        ),
        migrations.CreateModel(
            name="Etape",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("nom", models.CharField(max_length=100)),
                ("duree", models.IntegerField(max_length=100)),
                (
                    "machine",
                    models.ForeignKey(
                        on_delete=django.db.models.deletion.PROTECT,
                        to="high_level.machine",
                    ),
                ),
                (
                    "quantite_ressource",
                    models.ForeignKey(
                        on_delete=django.db.models.deletion.PROTECT,
                        to="high_level.quantiteressource",
                    ),
                ),
            ],
        ),
    ]
