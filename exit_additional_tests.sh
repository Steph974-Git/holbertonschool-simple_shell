#!/bin/bash

echo -e "\n=== TESTS SUPPLÉMENTAIRES POUR EXIT ==="

# Test du nom du programme dans les messages d'erreur
echo -e "\n--- Test 7: Vérification du nom dans les messages d'erreur ---"
cp ./hsh ./test_shell
echo "exit abc" > temp_script.sh
./test_shell < temp_script.sh 2> error_output.txt
cat error_output.txt
echo -n "Format attendu: "
echo "test_shell: 1: exit: Illegal number: abc"
rm ./test_shell

# Test d'un nombre hexadécimal
echo -e "\n--- Test 8: Exit avec nombre hexadécimal ---"
echo "exit 0x10" > temp_script.sh
./hsh < temp_script.sh 2> error_output.txt
cat error_output.txt
echo "Return code: $?"

# Test avec des espaces supplémentaires
echo -e "\n--- Test 9: Exit avec espaces supplémentaires ---"
echo "exit   98" > temp_script.sh
./hsh < temp_script.sh
echo "Return code: $?"

# Test avec une valeur maximale (255)
echo -e "\n--- Test 10: Exit avec valeur maximale (255) ---"
echo "exit 255" > temp_script.sh
./hsh < temp_script.sh
echo "Return code: $?"

# Test avec une valeur juste au-dessus de la limite (257)
echo -e "\n--- Test 11: Exit avec valeur 257 ---"
echo "exit 257" > temp_script.sh
./hsh < temp_script.sh
echo "Return code: $?"

# Test avec une valeur très large
echo -e "\n--- Test 12: Exit avec valeur très grande ---"
echo "exit 9999999" > temp_script.sh
./hsh < temp_script.sh
echo "Return code: $?"

# Test avec un zéro précédé de signe plus
echo -e "\n--- Test 13: Exit avec +0 ---"
echo "exit +0" > temp_script.sh
./hsh < temp_script.sh 2> error_output.txt
cat error_output.txt
echo "Return code: $?"

# Test vérifiant le prompt (doit être "$ " et non "($) ")
echo -e "\n--- Test 14: Vérification du format du prompt ---"
echo "" | ./hsh > prompt_output.txt
if grep -q "($)" prompt_output.txt; then
  echo "Prompt contient '($)' - Format différent du demandé"
elif grep -q "\$ " prompt_output.txt; then
  echo "Prompt contient '$ ' - Format correct"
else
  echo "Prompt ne contient ni '($)' ni '$ ' - Format inconnu"
fi

# Test interactif via pipe
echo -e "\n--- Test 15: Exit via pipe ---"
echo "exit 42" | ./hsh
echo "Return code: $?"

# Nettoyage
rm -f temp_script.sh error_output.txt prompt_output.txt