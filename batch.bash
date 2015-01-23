for ((i=13;i<24;i+=1))
do
    echo $i
    python test.py -n $i -m $i -f $i.dat
done
