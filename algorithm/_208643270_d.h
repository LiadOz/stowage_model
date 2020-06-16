#pragma once 
#include "AdvancedAlgorithm.h"

/* DIVESRITY IS OUR STRENGTH */
/*
 * This algorithm tries an odd approach to deliver the least amount of cargos,
 * it does so by trying to have the most diverse cargos possible.
 * the more diverse you are the less work you do.
 *
 *
 * In order to understand the power of diversity consider these cases:
 *  1. Prioritizing the closest ports - this means that most of the time when you 
 *  reach a port you will unload a high amount of cargos which makes you pay a lot
 *  but that also means that you freed a lot of cargos so you can load a lot.
 *
 *  2. Prioritizing the further ports - if the route is long then it becomes pretty
 *  close to the first case but also you need to you move operations very efficiently
 *  in order to not get a huge mess and you also lose the power of good unloads,
 *  if one cargo had moved 6 times then by the end you pay for it 28 which is 
 *  almost like having 5 additional cargos processed.
 *
 *  3. You reach a port with a 100 awaiting cargo - if you are unloading 50 cargos
 *  then you are going to pay at least 500 if you are unloading 10 then you will 
 *  pay 100. assuming there is one travel that has this amount you can save 400 
 *  in the final score.
 *
 *  TDLR:
 *  each container on the ship stops you from loading more containers
 *  then at all times you want to unload the least.
 */
class _208643270_d : public AdvancedAlgorithm {
protected:
    virtual void getPortInstructions(
            const string& port, vector<Container>& awaiting);
    // loads all cargos that were not at unload port
    Algorithm::InsertStatus loadAwaiting(vector<Container>& awaiting, unordered_set<string>& mustReturn);

    // will check where is the best place to start unloading, it should be the one 
    // where the port cargo is the highest then continue by that order
    unordered_set<string> unloadPort(const string& port, vector<Container>& awaiting);
    unordered_set<string> cargoToAdd(const string& port, vector<Container>& awaiting);
    // returns the best stack to move container with certain port to
    //
    // How a best stack is found:
    //  1. Search all the sorted stacks that the top goes after the target
    //  container, return the one that is closest to target.
    //  2. if you failed find a top of stack that goes after you first.
    //  3. if you failed find a top of stack that is as far away as possible
    pair<int, int> getBestStack(const string& port, int x, int );
public:
    _208643270_d (){};
    virtual ~_208643270_d(){};
};
