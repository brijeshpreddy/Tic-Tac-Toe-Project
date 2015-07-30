rm -r run_dir
mkdir run_dir
cd run_dir

# Compile databases
g++ -c ../../data/data_base.cpp |& tee run.log

# Compile agents
#g++ -c ../../agents/FILES_agents.cpp
g++ -c ../../agents/agent_order_0.cpp |& tee run.log
g++ -c ../../agents/agent_order_1.cpp |& tee run.log
g++ -c ../../agents/agent_improved.cpp |& tee run.log

# Compile game
g++ -c ../play_game.cpp |& tee run.log

#g++ database.o agent_order_0.o agent_order_1.o agent_improved.o play_game.o -o sample
g++ *.o -o sample.out |& tee run.log

# Run game
#g++ ../../data/database.cpp ../../agents/agent_order0.cpp ../../agents/agent_order1.cpp ../play_game.cpp -o sample &> run.log
./sample.out |& tee run.log
