
for file in plot.sh Makefile ;
do

echo $file
vim $file -c "set ff=unix" -c ":wq"

done