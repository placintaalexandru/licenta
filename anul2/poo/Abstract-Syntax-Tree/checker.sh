#!/bin/bash

make clean &> /dev/null
make build &> /dev/null

no_tests=10

grade=0
for i in `seq 0 $(($no_tests - 1))`; do
	cp "test/arbore"$i".in" arbore.in
	cp "test/arbore"$i".ok" ref.txt
	make run &> /dev/null
	diff arbore.out ref.txt &> /dev/null
	if [  $? -eq 0 ]
 	then 
		grade=$(($grade+10));
		echo "test"$i".............10"
	else
		echo "test"$i"............. 0"
		# diff "output/test"$i".out" "ref/test"$i".ref"
	fi
	
	rm -rf arbore.in arbore.out ref.txt &> /dev/null
done

echo ""
echo "GRADE.................................$grade";

