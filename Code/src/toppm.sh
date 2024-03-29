#!/bin/bash

# Vérifie si le nombre d'arguments est valide
if [ $# -ne 2 ]; then
    echo "Usage: $0 <input_image> <output_ppm>"
    exit 1
fi

# Vérifie si l'outil convert est installé
if ! command -v convert &> /dev/null; then
    echo "L'outil 'convert' d'ImageMagick est requis mais n'est pas installé."
    exit 1
fi

# Récupère les arguments d'entrée et de sortie
input_image=$1
output_ppm=$2

# Vérifie si le fichier d'entrée existe
if [ ! -f "$input_image" ]; then
    echo "Le fichier d'entrée '$input_image' n'existe pas."
    exit 1
fi

# Obtient l'extension du fichier d'entrée
extension="${input_image##*.}"

# Vérifie si l'extension est valide (png ou jpg/jpeg)
if [ "$extension" != "png" ] && [ "$extension" != "jpg" ] && [ "$extension" != "jpeg" ]; then
    echo "Extension de fichier invalide. Le fichier doit être un PNG ou JPG/JPEG."
    exit 1
fi

# Convertit l'image en ppm
convert "$input_image" "$output_ppm"

# Vérifie si la conversion s'est bien déroulée
if [ $? -ne 0 ]; then
    echo "Erreur lors de la conversion de '$input_image' en '$output_ppm'."
    exit 1
fi

echo "Conversion terminée. L'image '$input_image' a été convertie en '$output_ppm'."

