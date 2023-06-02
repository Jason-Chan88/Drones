#include "show.h"
Show::Show(){
    m_root = nullptr;
}

Show::~Show(){
    if (m_root != nullptr) {
        clear();
    }
    m_root = nullptr;
}

void Show::insert(const Drone& aDrone){

    if (!findDrone(aDrone.m_id)) { // no duplicates
        if (MINID <= aDrone.m_id && aDrone.m_id <= MAXID) { // ID within range
                    m_root = insertHelper(aDrone, m_root);
            }
    }
}

void Show::clear(){
    helpClear(m_root);
}

void Show::remove(int id){ // need to do this
    if (findDrone(id)) { // finds ID to remove
        m_root = removeHelper(m_root, id);
    }
}

void Show::dumpTree() const {
    dump(m_root);
}

void Show::dump(Drone* aDrone) const{
    if (aDrone != nullptr){
        cout << "(";
        dump(aDrone->m_left);//first visit the left child
        cout << aDrone->m_id << ":" << aDrone->m_height;//second visit the node itself
        dump(aDrone->m_right);//third visit the right child
        cout << ")";
    }
}

void Show::listDrones() const { // print in order from low to high
    listHelper(m_root);
}

bool Show::setState(int id, STATE state){
    Drone *target = findHelper(id, m_root);

    if (target != nullptr) {
        target->m_state = state;
        return true;
    }
    return false;
}

void Show::removeLightOff(){
    if(m_root != nullptr) {
        helpLightOff(m_root);
    }
}

bool Show::findDrone(int id) const {
    return findHelper(id, m_root) != nullptr;
}

const Show & Show::operator=(const Show & rhs){

    if (&rhs != this) {
        clear();
        m_root = helpCopy(rhs.m_root);
    }
    return *this;
}

int Show::countDrones(LIGHTCOLOR aColor) const{
    return helpCount(m_root, aColor);
}
// create drone helper to create drones
Drone * Show::createDrone(const Drone &aDrone, Drone* curr) {
    Drone *newDrone = new Drone(aDrone.m_id, aDrone.m_type, aDrone.m_state);
    newDrone->m_right = nullptr;
    newDrone->m_left = nullptr;
    newDrone->m_height = 0;
    return newDrone;
}

Drone *Show::insertHelper(const Drone &aDrone, Drone *curr) {
    if (curr == nullptr){
       curr = createDrone(aDrone, curr); //adds node if curr == nullptr
    }
    else if (aDrone.m_id < curr->m_id) { // going left
        if (curr->m_left != nullptr) { // keep's going recursive until it hit's nullptr and adds
            curr->m_left = insertHelper(aDrone, curr->m_left);
        } else {
            curr->m_left = createDrone(aDrone, curr->m_left);
        }
    } else if (aDrone.m_id > curr->m_id) {   // going right
        if (curr->m_right != nullptr) { // keep's going recursive until it hit's nullptr and adds
            curr->m_right = insertHelper(aDrone, curr->m_right);

        } else {
            curr->m_right = createDrone(aDrone, curr->m_right);
        }
    }

    helpHeight(curr); // adjust height
    curr = rebalanceHelper(curr); // rebalances

    return curr;
}

Drone *Show::findHelper(int id, Drone *curr) const {

    if (curr == nullptr) {
        return nullptr;
    }
    else if(curr->m_id == id) { // if ID found returns it
        return curr;
    }
    else if (id < curr->m_id) { // left
        return findHelper(id, curr->m_left);
    }
    else { // right
        return findHelper(id, curr->m_right);
    }
}

void Show::listHelper(Drone *aDrone) const { // prints out a list of Drones with state and color
    if (aDrone != nullptr){
        listHelper(aDrone->m_left);//first visit the left child
        cout << aDrone->m_id << ":" << aDrone->getStateStr() << ":" << aDrone->getTypeStr() << endl;//second visit the node itself
        listHelper(aDrone->m_right);//third visit the right child
    }
}

int Show::helpCount(Drone *aDrone, LIGHTCOLOR aColor)const { // counts specific color
    int holder = 0;
    if (aDrone == nullptr) {
        return 0;
    }
    else{
        if (aDrone->m_type == aColor) { // adds to holder when ID type equals that color
            holder += 1;
        }
        holder += helpCount(aDrone->m_left, aColor);
        holder += helpCount(aDrone->m_right, aColor);
    }
    return holder;
}

void Show::helpClear(Drone *curr) { // helps clearing everything

    if (curr == nullptr) {

    }
    else{
        helpClear(curr->m_left);
        helpClear(curr->m_right);
    }
    delete curr;
}

Drone * Show::helpCopy(Drone *curr) { // for assignment operator copying
    Drone *temp = nullptr;
    if (curr != nullptr) {
        temp = new Drone(*curr);
        temp->m_left = helpCopy(curr->m_left);
        temp->m_right = helpCopy(curr->m_right);
    }
    return temp;
}

int Show::countNodes(Drone * curr) { // count total nodes
    if (curr == nullptr) {
        return 0;
    }
    else{
        return 1 + countNodes(curr->m_left) + countNodes(curr->m_right);
    }
}

void Show::helpLightOff(Drone *curr) { // finds all the lightoff NODES and call remove for them
    Drone * temp = curr;

    if (temp == nullptr) {
        return;
    }
        if (temp->m_state == LIGHTOFF) {
            remove(temp->getID());
            helpLightOff(m_root); // important as with rebalancing after remove you miss some nodes so back to mroot
        }
    helpLightOff(temp->m_left);
    helpLightOff(temp->m_right);
}

void Show::helpHeight(Drone * curr) {
    if(curr != nullptr) {
        helpHeight(curr->m_left); // these two recursive function makes sure the heights are correct
        helpHeight(curr->m_right);

        // all cases for remove
        if (curr->m_left == nullptr && curr->m_right == nullptr) {
            curr->m_height = DEFAULT_HEIGHT;
        } else if (curr->m_left != nullptr && curr->m_right == nullptr) {
            curr->m_height = curr->m_left->m_height + 1;
        } else if (curr->m_right != nullptr && curr->m_left == nullptr) {
            curr->m_height = curr->m_right->m_height + 1;
        } else {
            if (curr->m_right->m_height >= curr->m_left->m_height) {
                curr->m_height = curr->m_right->m_height + 1;
            } else {
                curr->m_height = curr->m_left->m_height + 1;
            }
        }
    }
}

Drone *Show::removeHelper(Drone *curr, int id) {
    if (curr == nullptr){
        return curr;
    }
    else if (id < curr->m_id) { // going left
        if (curr->m_left != nullptr) {
            curr->m_left = removeHelper(curr->m_left, id);
        }
    }
    else if(id > curr->m_id)  {   // going right
        if (curr->m_right != nullptr) {
            curr->m_right = removeHelper(curr->m_right, id);
        }
    }
    else{
        if (curr->m_left == nullptr && curr->m_right == nullptr) { // no kids
            delete curr;
            return nullptr;
        }
        else if (curr->m_left == nullptr) { // no left kid
            Drone *temp = curr->m_right;
            delete curr;
            helpHeight(temp);
            temp = rebalanceHelper(temp);
            return temp;
        }
        else if(curr->m_right == nullptr) { // no right kid
            Drone *temp = curr->m_left;
            delete curr;
            helpHeight(temp);
            temp = rebalanceHelper(temp);
            return temp;
        }
        else{ // both kids
            Drone *temp;
            Drone *drone = curr->m_right;

            while ((drone != nullptr) && (drone->m_left != nullptr)) {
                drone = drone->m_left;
            }
            temp = drone;
            curr->m_id = temp->m_id;
            curr->m_right = removeHelper(curr->m_right, temp->m_id);
            helpHeight(curr);
            curr = rebalanceHelper(curr);
        }
    }

    helpHeight(curr);
    curr = rebalanceHelper(curr);

    return curr;
}

Drone *Show::rebalanceHelper(Drone *curr) { // rebalanced cases

    int balance = helpBalance(curr);

    if (balance == 0) {
        return curr;
    }
    // Left Left case
    if (balance < -1 && helpBalance(curr->m_right) <= 0) {
        if (m_root == curr) {
           m_root = helpLeftLeftRotate(curr);
            curr = m_root;
        }
        else {
            curr = helpLeftLeftRotate(curr);
        }
    }
    // Left Right case
    else if (balance < -1 && helpBalance(curr->m_right) > 0) {
        if (m_root == curr) {
            m_root = helpRightLeftRotate(curr);
            curr = m_root;
        }
        else {
            curr = helpRightLeftRotate(curr);
        }
    }
    // Right Right Case
    else if (balance > 1 && helpBalance(curr->m_left) >= 0){
        if (m_root == curr) {
            m_root = helpRightRightRotate(curr);
            curr = m_root;
        }
        else {
            curr = helpRightRightRotate(curr);
        }
    }
    // Right Left Case
    else if (balance > 1 && helpBalance(curr->m_left) < 0) {
        if (m_root == curr) {
            m_root = helpLeftRightRotate(curr);
            curr = m_root;
        }
        else {
            curr = helpLeftRightRotate(curr);
        }
    }

    return curr;
}

int Show::helpBalance(Drone * curr) {
    if(curr == nullptr) {
        return 0;
    }
    else {
        int leftSide = findHeight(curr->m_left);
        int rightSide = findHeight(curr->m_right);
        return (leftSide - rightSide);
    }
}

Drone *Show::helpRightRightRotate(Drone *curr) {
    Drone *temp = curr->m_left;
    curr->m_left = temp->m_right;
    temp->m_right = curr;
    return temp;
}

Drone *Show::helpLeftLeftRotate(Drone *curr) {
    Drone *temp = curr->m_right;
    curr->m_right = temp->m_left;
    temp->m_left = curr;
    return temp;
}

Drone *Show::helpRightLeftRotate(Drone *curr) {
    Drone *temp = curr->m_right;
    curr->m_right = helpRightRightRotate(temp);
    return helpLeftLeftRotate(curr);
}

Drone *Show::helpLeftRightRotate(Drone *curr) {
    Drone *temp = curr->m_left;
    curr->m_left = helpLeftLeftRotate(temp);
    return helpRightRightRotate(curr);
}

int Show::findHeight(Drone *curr) { // gets height for rebalanced purposes
    if(curr == nullptr) {
        return -1;
    }
    else{
        return curr->m_height;
    }
}

bool Show::testBalance(Drone *curr) { // test if tree is balanced by checking balanced > 2 or < -2
    bool result = true;
    if (curr != nullptr) {
        int balanced = findHeight(curr->m_left) - findHeight(curr->m_right);
        result = result && testBalance(curr->m_left);
        result = result && testBalance(curr->m_right);

        if (balanced >= 2 || balanced <= -2) {
            result = false;
            return result;
        }
    }
    return result;
}



bool Show::testBSTProperty(Drone * curr) { // checks the BST property, makes sure ID are in the right spot
    bool result = true;
    if (curr != nullptr) {
        result = result && testBSTProperty(curr->m_left);
        result = result && testBSTProperty(curr->m_right);
        if(curr->m_left != nullptr && curr->m_id < curr->m_left->m_id) {
            result = false;
        }
        if(curr->m_right != nullptr && curr->m_id > curr->m_right->m_id) {
            result = false;
        }
        return result;
    }
    return result;
}

int Show::helpCountState(Drone *aDrone, STATE LIGHTOFF) const { // function for counting LIGHTOFF for testing
    int amount = 0;
    if (aDrone == nullptr) {
        return 0;
    }
    else{
        if (aDrone->m_state == LIGHTOFF) {
            amount += 1;
        }
        amount += helpCountState(aDrone->m_left, LIGHTOFF);
        amount += helpCountState(aDrone->m_right, LIGHTOFF);
    }
    return amount;
}
