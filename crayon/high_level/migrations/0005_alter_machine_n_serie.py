# Generated by Django 5.1.1 on 2024-09-29 15:21

from django.db import migrations, models


class Migration(migrations.Migration):
    dependencies = [
        ("high_level", "0004_stock_usine_remove_stock_ressource_stock_ressource"),
    ]

    operations = [
        migrations.AlterField(
            model_name="machine",
            name="n_serie",
            field=models.CharField(max_length=100),
        ),
    ]
