rm -r run_dir
mkdir run_dir
cd run_dir

g++ -c ../../data/data_base.cpp
g++ -c ../../agents/agent_*.cpp
#g++ -c ../../agents/agent_order_1.cpp
#g++ -c ../../agents/agent_improved.cpp
g++ -c ../play_game.cpp

#g++ database.o agent_order_0.o agent_order_1.o agent_improved.o play_game.o -o sample
g++ *.o -o sample.out

#g++ ../../data/database.cpp ../../agents/agent_order0.cpp ../../agents/agent_order1.cpp ../play_game.cpp -o sample &> run.log
./sample.out
