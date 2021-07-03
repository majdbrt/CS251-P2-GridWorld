
#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H

#include <vector>
#include <iostream>

using std::vector;
using namespace std;

class GridWorld {
  private:
    // private stuff goes here!
    //   typedefs
    //   data members
    //   private helper functions
    //   etc.

  struct Node{
    int ID;
    Node* next;
    Node* prev;
  };

  class District{
    private:
     
    int size;
    Node* front;
    Node* back;

    public:

    District(){
      size = 0;
      front = nullptr;
      back = nullptr;
    }

    int get_size(){
      return size;
    }

    Node* get_front(){
      return front;
    }

    Node* get_back(){
      return back;
    }

    bool is_empty(){
      if(size == 0)
        return true;
      return false;
    }

    void push_back(int IDnum){
      if(front == nullptr){

        front = new Node();
        back = front;
        front->ID = IDnum;
        front->prev = nullptr;
        front->next = nullptr;

        size++;
        return;
      }// if

      if(back == front){

        Node* newNode = new Node();
        newNode->ID = IDnum;
        back = newNode;
        front->next = newNode;
        back->prev = front;
        back->next = nullptr;

        size++;
        return;
      }// if

      Node* newNode = new Node();
      newNode->ID = IDnum;
      Node* cur = back;
      cur->next = newNode;
      back = newNode;
      back->prev = cur;
      back->next = nullptr;
      size++;
    }// push_back

    int pop_front(){
      if(front == nullptr)
        return -1;

      if(front == back){
        Node* cur = front;
        int x = cur->ID;
        front = nullptr;
        back = nullptr;

        size--;
        delete cur;
        return x;
      }// if

      Node* cur = front;
      front = cur->next;
      front->prev = nullptr;
      int x = cur->ID;

      size--;
      delete cur;
      return x;
    }// pop_front

    void remove_node(Node* x){

      Node* prevNode = x->prev;
      Node* nextNode = x->next;

      if(prevNode != nullptr)
        prevNode->next = nextNode;
      else
        front = nextNode;
      
      if(nextNode != nullptr)
        nextNode->prev = prevNode;
      else
        back = prevNode;

      delete x;
      size--;
    }// remove_node
  };    
  
  struct Person{
    bool alive;
    int distRow;
    int distCol;
    Node* memberPtr;    
  };
  
  
  District** world;
  vector<Person> people;
  District* deadPool;
  int totalPopulation;
 

  int world_rows;
  int world_cols;
  
  bool valid_RowCol(int row, int col){
    if(row < world_rows
    && row >= 0
    && col < world_cols 
    && col >= 0)
      return true;

    return false;    
  }// valid_RowCol
  public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districtcs) in which all 
    *    districtricts are empty (a wasteland!).
    */
    GridWorld(unsigned nrows, unsigned ncols)   {

      world_rows = nrows;
      world_cols = ncols;
      totalPopulation = 0;
      
      // create the world matrix
      world = new District*[world_rows]();

      for(int i = 0; i < world_rows; i++)
        world[i] = new District[world_cols]();

      // create deadPool LL
      deadPool = new District();

    }
    ~GridWorld(){
      // remove the world matrix.
      for(int i = 0; i < world_rows; i++)
        delete world[i];
      
      delete world;

      // remove deadPool LL
      delete deadPool;
    }

    /*
     * function: birth
     * description:  if row/col is valid, a new person is created
     *   with an ID according to rules in handout.  New person is
     *   placed in district (row, col)
     *
     * return:  indicates success/failure
     */
    bool birth(int row, int col, int &id){
      if(!valid_RowCol(row, col))
        return false;

      if(deadPool->is_empty()){
        world[row][col].push_back(people.size());
        Person p;
        p.alive = true;
        p.distRow = row;
        p.distCol = row;
        p.memberPtr = world[row][col].get_back();

        id = people.size();
        people.push_back(p);
      }// if

      else{
        id = deadPool->pop_front();
        world[row][col].push_back(id);
        people[id].alive = true;
        people[id].distRow = row;
        people[id].distCol = col;
        people[id].memberPtr = world[row][col].get_back();
      }// else
      
      totalPopulation++;
      return true;
    }

    /*
     * function: death 
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     *
     * return:  indicates success/failure
     */
    bool death(int personID){
      if(people.empty() || personID >= people.size())
        return false;
      
      if(people[personID].alive){
        
        int r = people[personID].distRow;
        int c = people[personID].distCol;

        world[r][c].remove_node(people[personID].memberPtr);
        people[personID].memberPtr = nullptr;
        people[personID].alive = false;
        
        deadPool->push_back(personID);
        totalPopulation--;
        
        return true;
      }// if

      return false;
    }

    /*
     * function: whereis
     * description:  if given person is alive, his/her current residence
     *   is reported via reference parameters row and col.
     *
     * return:  indicates success/failure
     */
    bool whereis(int id, int &row, int &col)const{
      
      if(people.empty() || id >= people.size())
        return false;

      if(people[id].alive){
        row = people[id].distRow;
        col = people[id].distCol;
        return true;
      }// if

      return false;
    }

    /*
     * function: move
     * description:  if given person is alive, and specified target-row
     *   and column are valid, person is moved to specified district and
     *   data structures updated accordingly.
     *
     * return:  indicates success/failure
     *
     * comment/note:  the specified person becomes the 'newest' member
     *   of target district (least seniority) --  see requirements of members().
     */
    bool move(int id, int targetRow, int targetCol){
      if(people.empty() || id >= people.size())
        return false;

      if(people[id].alive && valid_RowCol(targetRow, targetCol)){

        int r = people[id].distRow;
        int c = people[id].distCol;

        world[r][c].remove_node(people[id].memberPtr);

        r = people[id].distRow = targetRow;
        c = people[id].distCol = targetCol;

        world[r][c].push_back(id);
        people[id].memberPtr = world[r][c].get_back(); 

        return true;
      }// if

      return false;
    }

    std::vector<int> * members(int row, int col)const{

      vector<int>* distMembers = new vector<int>;
      Node* cur = world[row][col].get_front();

      while(cur != nullptr){
        distMembers->push_back(cur->ID);
        cur = cur->next;
      }// while

      return distMembers;
    }

    /*
     * function: population
     * description:  returns the current (living) population of the world.
     */
    int population()const{
      return totalPopulation;
    }
    
    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row, int col)const{
      return world[row][col].get_size();
    }

    /*
     * function: num_rows
     * description:  returns number of rows in world
     */
    int num_rows()const {
      return world_rows;
    }

    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const {
      return world_cols;
    }

};

#endif
