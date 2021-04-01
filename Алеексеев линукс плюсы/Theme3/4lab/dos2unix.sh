for file in Makefile ;
do

echo $file
vim $file -c "set ff=unix" -c ":wq"

done