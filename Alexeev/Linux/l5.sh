
f=lab5

mkdir $f

cat l1.sh >$f/l5file


cp $f/l5file $f/l5copy
ln $f/l5file $f/l5file_hard
ln -s $f/l5file $f/l5file_soft
ls ./$f -l



ln -s $PWD/Var5/INFO/ $HOME/'Рабочий стол'/folder



current=$PWD
cd ~/'Рабочий стол'/
echo $current/Var5/INFO/ 
ln -s $current/Var5/INFO/ folder

#cd Var5
#ln -s ./INFO/ folder 
#mv folder ~/'Рабочий стол'/folder

path=$PWD/Var5/INFO/
cd $HOME/'Рабочий стол'
mkdir folder
cd folder
ln -s  $path


