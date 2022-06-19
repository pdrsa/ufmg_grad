count=0
for i in {0..99}
do
    python warcer.py $i > $i.txt
    now=$(wc -l $i.txt | tr ' ' '\n' | head -1)
    echo $now
    count=$(( $count+$now ))
done
echo "Total:"
echo $count
