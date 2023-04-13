for data in "single-results"
do
  cd ../
  mkdir -p ./scalar/${data}
  cd ./scalar/${data}
  for config in "First" "Second" "Third" "Fourth" "Fifth" "Sixth" "Seventh" "Eighth"
  do
    for n in 1 2 4
    do
      mkdir -p ./${config}-n${n}

      opp_scavetool export -f 'module=~*.sink AND ("lifeTime:mean")'              -o ./${config}-n${n}/LifeTimeMeanTotal.csv              -F CSV-S ../../simulation_data/${data}/${config}-n${n}-*.sca
      opp_scavetool export -f 'module=~*.sink AND ("lifeTime:min")'               -o ./${config}-n${n}/LifeTimeMinTotal.csv               -F CSV-S ../../simulation_data/${data}/${config}-n${n}-*.sca
      opp_scavetool export -f 'module=~*.sink AND ("lifeTime:max")'               -o ./${config}-n${n}/LifeTimeMaxTotal.csv               -F CSV-S ../../simulation_data/${data}/${config}-n${n}-*.sca
      opp_scavetool export -f 'module=~*.passiveQueue1 AND ("expired:count")'     -o ./${config}-n${n}/PassiveQueue1ExpJobs.csv           -F CSV-S ../../simulation_data/${data}/${config}-n${n}-*.sca
      opp_scavetool export -f 'module=~*.passiveQueue2 AND ("expired:count")'     -o ./${config}-n${n}/PassiveQueue2ExpJobs.csv           -F CSV-S ../../simulation_data/${data}/${config}-n${n}-*.sca
      opp_scavetool export -f 'module=~*.passiveQueue3 AND ("expired:count")'     -o ./${config}-n${n}/PassiveQueue3ExpJobs.csv           -F CSV-S ../../simulation_data/${data}/${config}-n${n}-*.sca
      opp_scavetool export -f 'module=~*.passiveQueue4 AND ("expired:count")'     -o ./${config}-n${n}/PassiveQueue4ExpJobs.csv           -F CSV-S ../../simulation_data/${data}/${config}-n${n}-*.sca
      opp_scavetool x -f 'module=~*.server AND ("response_time:histogram")'       -o ./${config}-n${n}/ResponseTimeTotal.json             -F JSON ../../simulation_data/${data}/${config}-n${n}-*.sca
      # opp_scavetool x -f 'module=~*.passiveQueue1 AND ("waiting_time:histogram")' -o ./${config}-n${n}/PassiveQueue1WaitingTimeTotal.json -F JSON ../../simulation_data/${data}/${config}-n${n}-*.sca
      # opp_scavetool x -f 'module=~*.passiveQueue2 AND ("waiting_time:histogram")' -o ./${config}-n${n}/PassiveQueue2WaitingTimeTotal.json -F JSON ../../simulation_data/${data}/${config}-n${n}-*.sca
      # opp_scavetool x -f 'module=~*.passiveQueue3 AND ("waiting_time:histogram")' -o ./${config}-n${n}/PassiveQueue3WaitingTimeTotal.json -F JSON ../../simulation_data/${data}/${config}-n${n}-*.sca
      # opp_scavetool x -f 'module=~*.passiveQueue4 AND ("waiting_time:histogram")' -o ./${config}-n${n}/PassiveQueue4WaitingTimeTotal.json -F JSON ../../simulation_data/${data}/${config}-n${n}-*.sca

    done
  done
done