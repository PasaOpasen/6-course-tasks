


mkdir Var5
cd Var5
mkdir A{1,2}
mkdir INFO

for f in Personal University Hobby;
do
mkdir INFO/$f
done

cd A1
mkdir B{1,2}
cd B1
mkdir C{1,2}


cd ../../

for f in B4 B5;
do
mkdir A2/$f
done


rmdir A1/B2

now=INFO/Personal
echo "Пасько Дмитрий Анатольевич" >$now/Name.txt
echo "22 08 1997" >$now/Date.txt
echo "Гимназия № 87" >$now/School.txt

echo "КубГУ 02.04.01 математика и компьютерные науки" >INFO/University/Name.txt
echo "искуственный интеллект" >INFO/Hobby/hobby.txt

cp INFO/Hobby/hobby.txt A2/hobby.txt

for file in `ls INFO/Personal`;
do
cat INFO/Personal/$file >> all.txt
done

cp all.txt A1/all.txt
