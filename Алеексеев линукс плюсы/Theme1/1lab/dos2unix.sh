
for file in static.sh dynamic.sh Makefile ;
do

echo $file
vim $file -c "set ff=unix" -c ":wq"

done

