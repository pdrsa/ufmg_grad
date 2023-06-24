for i in BFS UCS Greedy Astar
do
    echo $i
    time ./pathfinder mapas/cidade.map $i 1 1 250 250 > out
    echo ""
    cat out
    echo "--------------------------------------"
done
