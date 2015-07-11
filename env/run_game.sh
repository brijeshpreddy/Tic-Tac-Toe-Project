rm -r run_dir
mkdir run_dir
g++ ../data/*.cpp -o run_dir/game.out
./run_dir/game.out

#rm -r run_dir
#mkdir run_dir
#cd run_dir

#g++ -c ../../data/database.cpp
#g++ -c ../../agents/agent_order0.cpp
#g++ -c ../../agents/agent_order1.cpp
#g++ -c ../play_game.cpp

#g++ database.o agent_order0.cpp agent_order1.o play_game.o -o sample
#./sample
