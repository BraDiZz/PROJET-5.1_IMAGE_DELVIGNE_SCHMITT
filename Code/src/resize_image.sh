#!/bin/bash

# Vérifier si le nombre d'arguments est correct
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <chemin_de_l_image>"
    exit 1
fi

# Vérifier si le fichier existe
if [ ! -f "$1" ]; then
    echo "Fichier '$1' introuvable."
    exit 1
fi

# Redimensionner l'image en 500x500 pixels
echo "Redimensionnement de l'image : $1"
convert "$1" -resize 500x500\> "$1"

echo "Redimensionnement terminé."
