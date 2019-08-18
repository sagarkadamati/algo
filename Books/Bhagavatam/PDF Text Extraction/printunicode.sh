#!/bin/bash

for r in 0 1 2 3 4 5 6 7 8 9 A B C D E F; do
	for c in 0 1 2 3 4 5 6 7; do
		str="0C$c$r"
		echo -en "$str - \u$str, "
	done
	echo ""
done

# for r in 0 1 2 3 4 5 6 7 8 9 A B C D E F; do
#	for c in 0 1 2 3 4 5 6 7; do
#		str="0C$c$r"
#		echo -e "$str - \u$str"
#	done
# done

