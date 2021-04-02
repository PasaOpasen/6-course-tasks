
folder=Var

chmod 4 Var5/INFO # r = 4  w = 2  x = 1

mkdir $folder; cd $folder

mkdir test; cd test

touch file; ls -l file;
chmod -rwx file; ls -l file;
echo "test" > file
cat file

chmod u+w file; ls -l file;
echo "test" > file
cat file

chmod g+r file; ls -l file;
cat file

chmod u+r file; cat file


mkdir dir
echo "file2" >dir/new_file; cat dir/new_file

ls dir
chmod a-x dir 
cat dir/new_file
rm dir/new_file


cd ../
f=Primer
mkdir $f
touch $f/primer1.txt $f/primer2.txt
chmod 455 $f/primer2.txt

