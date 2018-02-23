clear
echo "------------FAILED------------"

for file in $(find `pwd`/tests -name *.hco)
do
	./huw "$file" > ./output/$(basename $file)
	diff -q ./output/$(basename $file) ./expected/$(basename $file)
done
echo "------------------------------"
