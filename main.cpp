#include "show.h"
#include <random>
using namespace std;

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }

private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution
};

class Tester{
public:
    double sampleTimeMeasurement(Show & aShow, int tempArray[], int arraySize);

    bool insertNormalCase(Show & ashow); // insert 200
    bool insertEdgeCase(Show & ashow); // insert just 1 node for edge case
    bool insertErrorCase(Show & ashow); // show insert 0 nodes and return false
    bool insertBalanced(Show & ashow); // inserts 300 than checks if they are balanced
    bool insertBSTProperty(Show & ashow); // inserts 300 than checks BST property
    bool removeNormalCase(Show & ashow); // inserts 300 than removes 300
    bool removeEdgeCase(Show & ashow); // inserts 300 than removes the root
    bool removeBalanced(Show & ashow); // inserts 300 than removes 150, checks if it's balanced
    bool removeBSTProperty(Show & ashow); // inserts 300 than removes 150, checks if it follow BST Property
    bool testRemoveLightOff(Show & ashow); //see if removelightoff function works
    bool testCountDrones(Show & ashow); // see's if it correctly counts the amount of red
    bool findDroneNormal(Show & ashow); // test finding drone
    bool findDroneError(Show & ashow); // test finding drone that doesn't exist
    bool testAssignmentOperatorNormal(); // checks if the two tree have the same root id
    bool testAssignmentOperatorError(); // test copying empty object should return false
    bool testRemoveTimeMeasurement(); // removes 1000 and 2000 nodes than checks if they fall within range
    bool testInsertTimeMeasurement(); // inserts 10000 and 5000 nodes than checks if they fall in range
};

int main(){
    Tester tester;
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); // there are three colors

   Show show1;

    if (tester.insertNormalCase(show1)) // should return true
        cout << "\ttestinsertNormalCase() returned true." << endl;
    else
        cout << "\ttestinsertNormalCase() returned false." << endl;

    Show show2;

    if (tester.insertEdgeCase(show2)) // should return true
        cout << "\ttestinsertEdgeCase() returned true." << endl;
    else
        cout << "\ttestinsertEdgeCase() returned false." << endl;

    Show show3;

    if (tester.insertErrorCase(show3)) // should return false
        cout << "\ttestinsertErrorCase() returned true." << endl;
    else
        cout << "\ttestinsertErrorCase() returned false." << endl;

    Show show4;

    if (tester.insertBalanced(show4)) // should return true
        cout << "\ttestinsertBalanced() returned true." << endl;
    else
        cout << "\ttestinsertBalanced() returned false." << endl;

    Show show5;

    if (tester.insertBSTProperty(show5)) // should return true
        cout << "\ttestinsertBSTProperty() returned true." << endl;
    else
        cout << "\ttestinsertBSTProperty() returned false." << endl;

    Show show11;

    if (tester.testCountDrones(show11)) // should return true
        cout << "\ttestCountDrones() returned true." << endl;
    else
        cout << "\ttestCountDrones() returned false." << endl;

    Show show12;

    if (tester.findDroneNormal(show12)) // should return true
        cout << "\ttestfindDroneNormal() returned true." << endl;
    else
        cout << "\ttestfindDroneNormal() returned false." << endl;

    Show show13;

    if (tester.findDroneError(show13)) // should return false
        cout << "\ttestfindDroneError() returned true." << endl;
    else
        cout << "\ttestfindDroneError() returned false." << endl;

    if (tester.testAssignmentOperatorNormal()) // should return true
        cout << "\ttestAssignmentOperatorNormal() returned true." << endl;
    else
        cout << "\ttestAssignmentOperatorNormal() returned false." << endl;

    if (tester.testAssignmentOperatorError()) // should return true
        cout << "\ttestAssignmentOperatorError() returned true." << endl;
    else
        cout << "\ttestAssignmentOperatorError() returned false." << endl;

    Show show7;

    if (tester.removeEdgeCase(show7)) // should return true
        cout << "\ttestremoveEdgeCase() returned true." << endl;
    else
        cout << "\ttestremoveEdgeCase() returned false." << endl;

    Show show6;

    if (tester.removeNormalCase(show6)) // should return true
        cout << "\ttestremoveNormalCase() returned true." << endl;
    else
        cout << "\ttestremoveNormalCase() returned false." << endl;

    Show show8;

    if (tester.removeBalanced(show8)) // should return true
        cout << "\ttestremoveBalanced() returned true." << endl;
    else
        cout << "\ttestremoveBalanced() returned false." << endl;

    Show show9;

    if (tester.removeBSTProperty(show9)) // should return true
        cout << "\ttestremoveBSTProperty() returned true." << endl;
    else
        cout << "\ttestremoveBSTProperty() returned false." << endl;

    Show show10;

    if (tester.testRemoveLightOff(show10)) // should return true
        cout << "\ttestRemoveLightOff() returned true." << endl;
    else
        cout << "\ttestRemoveLightOff() returned false." << endl;

    if (tester.testRemoveTimeMeasurement()) // should return true
        cout << "\ttestRemoveTimeMeasurement() returned true." << endl;
    else
        cout << "\ttestRemoveTimeMeasurement() returned false." << endl;

    if (tester.testInsertTimeMeasurement()) // should return true
        cout << "\ttestInsertTimeMeasurement() returned true." << endl;
    else
        cout << "\ttestInsertTimeMeasurement() returned false." << endl;


    {
        Show show;
        int teamSize = 10;
        int tempID = 0;
        int ID = 0;
        for(int i=0;i<teamSize;i++) {
            ID = idGen.getRandNum();
            if (i == teamSize / 2) tempID = ID;//we store this ID for later use
            Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
            show.insert(drone);
        }
        cout << "\nDump after inserting " << teamSize << " nodes:\n\n";
        show.dumpTree();
        cout << "\n\nList of Drones after inserting " << teamSize << " nodes:\n";
        show.listDrones();
        cout << endl;

        show.remove(tempID);
        cout << "\nDump after removig the node with ID: " << tempID << "\n\n";
        show.dumpTree();
        cout << "\n\nList of Drones after removing the node with ID: " << tempID << "\n";
        show.listDrones();
        cout << endl;
    }
    {

        Show show;
        int size = 1000;
        int tempIDs[1001] = {0};
        int id = 0;
        for(int i=0;i<size;i++){
            id = idGen.getRandNum();
            tempIDs[i] = id;//we store this ID for later use
            Drone drone(id,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
            show.insert(drone);
        }
        cout << endl << "Calling Tester::sampleTimeMeasurement(...): " << endl;
        cout << "Finding 1000 nodes takes " << tester.sampleTimeMeasurement(show, tempIDs, size) << " seconds." << endl;

         }

    return 0;
}

double Tester::sampleTimeMeasurement(Show & aShow, int tempArray[], int arraySize){
    double T = 0.0;//stores running times
    clock_t start, stop;//stores the clock ticks while running the program
    start = clock();
    // the algorithm to be measured
    for (int j=0;j<arraySize;j++){
        aShow.findDrone(tempArray[j]);
    }
    stop = clock();
    T = stop - start;//number of clock ticks the algorithm took
    double measureTime = T/CLOCKS_PER_SEC;//time in seconds
    return measureTime;
}
//Function: Tester::insertNormalCase
//Case: Insert 10000 nodes and it matches size
//Expected result: we expect this to return true as the amount of nodes counted
//should match the amount of nodes inserted which is 10000
bool Tester::insertNormalCase(Show & ashow){ // insert 10000
    Random idGen(MINID,MAXID);
    Random typeGen(0,2); // get's random color
    Random stateGen(0,1); // get's random state

    bool result;

    int teamSize = 10000;
    int ID = 10000;
    for(int i=0;i<teamSize;i++) {
        if (i == teamSize / 2);//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()), static_cast<STATE>(stateGen.getRandNum()));
        ashow.insert(drone); // uses insert to insert nodes
        ID++;
    }

    if (ashow.countNodes(ashow.m_root) == teamSize) { // test case
        result = true;
    }
    else {
        result = false;
    }

    return result;
}
//Function: Tester::insertEdgeCase
//Case: Insert 1 as edge case should become root node
//Expected result: expect it to return true, as inserting one node and
// it being the root is the first case of insert as the AVL tree is empty
bool Tester::insertEdgeCase(Show & ashow){ // insert just 1 node for edge case
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result;

    int teamSize = 1;
    int ID = 0;
    for(int i=0;i<teamSize;i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()), static_cast<STATE>(stateGen.getRandNum()));
        ashow.insert(drone);
    }
    if (ashow.countNodes(ashow.m_root) == 1) { // checks to see if there's only one node
        result = true;
    }
    else {
        result = false;
    }
    return result;
}
//Function: Tester::insertErrorCase
//Case: Insert a node with an invalid ID
//Expected result: expect it to return false as 5000 isn't a valid ID
bool Tester::insertErrorCase(Show & ashow){ // show insert 0 nodes and return false
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int teamSize = 10;
    for(int i=0;i<teamSize;i++) {
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(5000, static_cast<LIGHTCOLOR>(typeGen.getRandNum()), static_cast<STATE>(stateGen.getRandNum()));
        ashow.insert(drone);
    }
    result = result && ashow.countNodes(ashow.m_root); // count nodes should be 0 aka false

    return result;
}
//Function: Tester::insertBalance
//Case: Insert 10000 nodes and checks if they are balanced
//Expected result: expect it to return true as balancing is called
// while inserting and I have a helper function testing balance
bool Tester::insertBalanced(Show & ashow){ // inserts 10000 than checks if they are balanced
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int teamSize = 10000;
    int ID = 10000;
    for(int i=0;i<teamSize;i++) {
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        ashow.insert(drone);
        ID++;
    }

    result = result && ashow.countNodes(ashow.m_root) == teamSize; // test to make sure there's 1000
    result = result && ashow.testBalance(ashow.m_root); // test balance should return true

    return result;
}
//Function: Tester::insertBSTProperty
//Case: Insert 10000 nodes and checks if they follow BST Property
//Expected result: expect it to return true as the tree should follow BST Property when
// it was inserted
bool Tester::insertBSTProperty(Show & ashow){ // inserts 10000 than checks BST property
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int teamSize = 10000;
    int ID = 10000;
    for(int i=0;i<teamSize;i++) {
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        ashow.insert(drone);
        ID++;
    }

    result = result && ashow.countNodes(ashow.m_root) == teamSize; // test to make sure there's 1000
    result = result && ashow.testBalance(ashow.m_root); // test balance should return true
    result = result && ashow.testBSTProperty(ashow.m_root); // test if it follows BST Property
    return result;
}
//Function: Tester::RemoveNormalCase
//Case: Insert 10000 nodes and removes 10000
//Expected result: expect it to return true as remove should remove all of them
// this get's done by putting ID's into an array and calling those array of ID's in remove
bool Tester::removeNormalCase(Show & ashow){ // inserts 10000 than removes 10000
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int size = 10000;
    int array[size]; // this is the array to hold ID's

    int teamSize = 10000;
    int ID = 10000;
    for(int i=0;i<teamSize;i++) {
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        ashow.insert(drone);
        array[i] = ID;
        ID++;
    }

    for(int i = 0; i < size; i++) {
        ashow.remove(array[i]);
    }

    result = result && (ashow.countNodes(ashow.m_root) == 0); // all these should pass
    result = result && ashow.testBSTProperty(ashow.m_root);
    result = result && ashow.testBalance(ashow.m_root);

    return result;
}
//Function: Tester::RemoveEdgeCase
//Case: Insert 1000 nodes and removes the m_root ID as the edge case
//Expected result: expect it to return true as remove should just remove the root
// than the tree should still be balanced and follow BSTProperty
bool Tester::removeEdgeCase(Show & ashow){ // inserts 300 than removes m_root
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int teamSize = 1000;
    int ID = 0;
    for(int i=0;i<teamSize;i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        ashow.insert(drone);
    }
    int find = ashow.m_root->m_id; // put it into a variable so it won't change
    ashow.remove(find);

    result = result && !ashow.findDrone(find); // it shouldn't find it as it doesn't exist

    return result;
}
//Function: Tester::RemoveBalanced
//Case: Insert 10000 nodes and removes 5000 checks if it's balanced
//Expected result: expect it to return true as remove should remove 5000 of them
// this get's done by putting ID's into an array and calling those array of ID's in remove
bool Tester::removeBalanced(Show & ashow){ // inserts 10000 than removes 5000, checks if it's balanced
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int size = 5000;
    int array[size];

    int teamSize = 10000;
    int ID = 10000;
    for(int i=0;i<teamSize;i++) {
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        ashow.insert(drone);
        if(i < size) {// this makes sure it only adds 500 ID's to the array very important
            array[i] = ID;
        }
        ID++;
    }

    for(int i = 0; i < size; i++) {
        ashow.remove(array[i]);
    }

    result = result && (ashow.countNodes(ashow.m_root) == size); // should all return true
    result = result && ashow.testBSTProperty(ashow.m_root);
    result = result && ashow.testBalance(ashow.m_root);

    return result;
}
//Function: Tester::RemoveBSTProperty
//Case: Insert 10000 nodes and removes 5000 checks if it follow BST Property
//Expected result: expect it to return true as remove should remove 500
// this get's done by putting ID's into an array and calling those array of ID's in remove
bool Tester::removeBSTProperty(Show & ashow){ // inserts 10000 than removes 5000, checks if it follow BST Property
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int size = 5000;
    int array[size];

    int teamSize = 10000;
    int ID = 10000;
    for(int i=0;i<teamSize;i++) {
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        ashow.insert(drone);
        if(i < size) {
            array[i] = ID;
        }
        ID++;
    }

    for(int i = 0; i < size; i++) {
        ashow.remove(array[i]);
    }

    result = result && (ashow.countNodes(ashow.m_root) == size);
    result = result && ashow.testBSTProperty(ashow.m_root);

    return result;
}
//Function: Tester::RemoveLightOff
//Case: Insert 10000 nodes and removes all the ID's with the state LIGHTOFF
//Expected result: expect it to return true as remove should all the ID's with the state LIGHTOFF
// should be 0 ID's with the state LIGHTOFF at the end;
bool Tester::testRemoveLightOff(Show & ashow){ //see if removelightoff function works
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int teamSize = 10000;
    int ID = 10000;
    for(int i=0;i<teamSize;i++) {
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()), static_cast<STATE>(stateGen.getRandNum()));
        ashow.insert(drone);
        ID++;
    }

    ashow.removeLightOff();

    result = result && (ashow.helpCountState(ashow.m_root, LIGHTOFF) == 0); // should be 0 and return true

    return result;
}
//Function: Tester::testCountDrones
//Case: Insert 1000 nodes with RED color and checks to see if countDrones get's the right amount of 1000
//Expected result: should return true as it finds all 1000 RED Nodes
bool Tester::testCountDrones(Show & ashow){ // see's if it correctly counts the amount of red
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int teamSize = 1000;
    int ID = 10000;
    for(int i=0;i<teamSize;i++) {
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, RED, static_cast<STATE>(stateGen.getRandNum())); // just set color for drones to Red
        ashow.insert(drone);
        ID++;
    }

    result = result && (ashow.countDrones(RED) == teamSize); // should equal team size

    return result;
}
//Function: Tester::findDroneNormal
//Case: Insert 1000 nodes and tries to find 1 of the ID's
//Expected result: should return true as it's finding an ID that exist in the AVL tree
bool Tester::findDroneNormal(Show & ashow){ // test finding drone
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int teamSize = 1000;
    int ID = 10000;
    int tempID;
    for(int i=0;i<teamSize;i++) {
        tempID = ID;
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()), static_cast<STATE>(stateGen.getRandNum()));
        ashow.insert(drone);
        ID++;
    }

    result = result && ashow.findDrone(tempID); // should find ID

    return result;
}
//Function: Tester::findDroneError
//Case: Insert 1000 nodes and tries to find an ID with an INVALID ID
//Expected result: should return false as the ID doesn't/can't exist
bool Tester::findDroneError(Show & ashow){ // test finding drone that doesn't exist
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int teamSize = 1000;
    int ID = 1000;
    for(int i=0;i<teamSize;i++) {
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()), static_cast<STATE>(stateGen.getRandNum()));
        ashow.insert(drone);
        ID++;
    }
    result = result && ashow.findDrone(5000); // trying to find an ID of 5000 but 5000 isn't valid

    return result;
}
//Function: Tester::testAssignmentOperatorNormal
//Case: Insert 1000 nodes, see's if show1 properly copies to show 2
//Expected result: should return true and they should have the same root ID
bool Tester::testAssignmentOperatorNormal(){ // checks if the two tree have the same root id
    Show show1;
    Show show2;

    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int teamSize = 10000;
    int ID = 10000;
    for(int i=10000;i<10002;i++) {
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()), static_cast<STATE>(stateGen.getRandNum()));
        show1.insert(drone);
        ID++;
    }
    cout << "before" <<endl;
    show1.dumpTree();
    show2.dumpTree();

    show2 = show1;

    show1.dumpTree();
    cout << "what" <<endl;
    show2.dumpTree();

    result = result && (show2.m_root->m_id == show1.m_root->m_id); // checking for same ID

    return result;
}
//Function: Tester::testAssignmentOperatorError
//Case: Insert 1000 nodes, see's if an empty object can copy another
//Expected result: should return true as if both are nullptr than that means nothing happen and both are empty
bool Tester::testAssignmentOperatorError(){ // test copying empty object
    Show show1;
    Show show2;

    Random idGen(MINID,MAXID);
    Random typeGen(0,2);
    Random stateGen(0,1);

    bool result = true;

    int teamSize = 300;
    int ID = 0;
    for(int i=0;i<teamSize;i++) {
        ID = idGen.getRandNum();
        if (i == teamSize / 2) ;//we store this ID for later use
        Drone drone(ID, static_cast<LIGHTCOLOR>(typeGen.getRandNum()), static_cast<STATE>(stateGen.getRandNum()));
        //show1.insert(drone);
    }
    show2 = show1;

    result = result && (show2.m_root == nullptr && show1.m_root == nullptr); // checking if both empty

    return result;
}
//Function: Tester::testRemoveTimeMeasurement
//Case: Insert 1000 nodes and 2000 nodes than remove both and see's if removing takes O(log n)
//Expected result: should return true as it should stay between 0.7 and 1.5 as that's the condition
bool Tester::testRemoveTimeMeasurement() {
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show1;
    Show show2;

    bool result = true;

    int size1 = 11000;
    int tempIDs1[1001] = {0};
    for(int i=10000;i<size1;i++){
        Drone drone(i,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show1.insert(drone);
    }

    double T = 0.0;//stores running times
    clock_t start, stop;//stores the clock ticks while running the program
    start = clock();
    // the algorithm to be measured
    for (int j=10000;j<size1;j++){
        show1.remove(j);
    }
    stop = clock();
    T = stop - start;//number of clock ticks the algorithm took
    double measureTime1 = T/CLOCKS_PER_SEC;//time in seconds

    int size2 = 12000;
    for(int i=10000;i<size2;i++){
        Drone drone(i,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show2.insert(drone);
    }

    double T2 = 0.0;//stores running times
    clock_t start2, stop2;//stores the clock ticks while running the program
    start2 = clock();
    // the algorithm to be measured
    for (int j=10000;j<size2;j++){
        show2.remove(j);
    }
    stop2 = clock();
    T2 = stop2 - start2;//number of clock ticks the algorithm took
    double measureTime2 = T2/CLOCKS_PER_SEC;//time in seconds

    cout << 2*measureTime1 << endl;
    cout << measureTime2 << endl;
    cout << (measureTime2/(2*measureTime1)) << endl;
    result = result && ((1.1-0.4) <= (measureTime2/(2*measureTime1)) && (measureTime2/(2*measureTime1))  <= (1.1+0.4)); // should be true// should end up being true

    return result;
}
//Function: Tester::testInsertTimeMeasurement
//Case: Insert 10000 nodes and 5000 nodes than see's if it performs O(log n)
//Expected result: should return true as it should stay between 0.7 and 1.5 as that's the condition
bool Tester::testInsertTimeMeasurement() {
    Random idGen(MINID,MAXID);
    Random typeGen(0,2);

    Show show1;
    Show show2;

    bool result = true;

    int size1 = 11000;
    int id1 = 0;

    double T = 0.0;//stores running times
    clock_t start, stop;//stores the clock ticks while running the program
    start = clock();
    // the algorithm to be measured
    for (int i=10000;i<size1;i++){
        //id1 = idGen.getRandNum();
        Drone drone(i,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show1.insert(drone);
    }
    stop = clock();
    T = stop - start;//number of clock ticks the algorithm took
    double measureTime1 = T/CLOCKS_PER_SEC;//time in seconds

    int size2 = 12000;
    int id2 = 0;

    double T2 = 0.0;//stores running times
    clock_t start2, stop2;//stores the clock ticks while running the program
    start2 = clock();
    // the algorithm to be measured
    for (int i=10000;i<size2;i++){
        //id2 = idGen.getRandNum();
        Drone drone(i,static_cast<LIGHTCOLOR>(typeGen.getRandNum()));
        show2.insert(drone);
    }
    stop2 = clock();
    T2 = stop2 - start2;//number of clock ticks the algorithm took
    double measureTime2 = T2/CLOCKS_PER_SEC;//time in seconds

    cout << 2*measureTime1 << endl;
    cout << measureTime2 << endl;
    cout << (measureTime2/(2*measureTime1)) << endl;
    result = result && ((1.1-0.4) <= (measureTime2/(2*measureTime1)) && (measureTime2/(2*measureTime1))  <= (1.1+0.4)); // should be true

    return result;
}