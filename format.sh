#!/bin/bash

if [ $# != 1 ]; then
	echo Il faut ndonner le chemin où formatter les fichier
fi

liste=`find $1 \( -name '*.cpp' -o -name '*.hpp' \)`

for path in $liste
do
    if [ !$(head -n1 ${path} | grep 'NO_FORMAT') ]
    then
        astyle $path
    fi

    cat $path | sed -e 's/^{$/{\/*{{{*\//' | sed -e 's/^}$/}\/*}}}*\//' > tmp
    grep -v -E '^\s+/\*{{{' tmp > $path


done

find $1 -name *.orig -exec rm '{}' \;
rm tmp
