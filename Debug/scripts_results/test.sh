#/bin/bash

while read p; do
	echo $p
	grep $p syms.txt | wc -l
done < uniq.txt
