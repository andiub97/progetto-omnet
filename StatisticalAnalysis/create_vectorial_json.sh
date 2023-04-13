cd ..
mkdir -p ./vectorial/single-results
cd ./vectorial/single-results
  for config in "First" "Second" "Third" "Fourth" "Fifth" "Sixth" "Seventh" "Eighth"
  do
    for n in 1 2 4
    do
      
      mkdir lifeTime      
      opp_scavetool x -f 'module=~*.sink AND ("lifeTime:vector")'             -o ./lifeTime/${config}-n${n}.json       -F JSON ../../simulation_data/single-results/${config}-n${n}-*.vec
      
  done
done
