clear
echo "------FORMATTING FAILED-------"

for file in $(find `pwd`/tests -name *.hco)
do
	./huw --hc "$file" > ./formatter/$(basename $file)
	./huw ./formatter/$(basename $file) > ./output/$(basename $file)
	diff -q ./output/$(basename $file) ./expected/$(basename $file)
done
echo "------------------------------"
