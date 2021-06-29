
#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H

#include <vector>
#include <iostream>

using std::vector;


class GridWorld {

  private:
    // private stuff goes here!
    //   typedefs
    //   data members
    //   private helper functions
    //   etc.

  public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districtcs) in which all 
    *    districtricts are empty (a wasteland!).
    */
    GridWorld(unsigned nrows, unsigned ncols)   {

      // your constructor code here!
    }
    ~GridWorld(){
      // your destructor code here.
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
      return false;
    }

    /*
     * function: death 
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     *
     * return:  indicates success/failure
     */
    bool death(int personID){

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
      return false;
    }

    std::vector<int> * members(int row, int col)const{

      return nullptr;
    }

    /*
     * function: population
     * description:  returns the current (living) population of the world.
     */
    int population()const{
      return 0;
    }
    
    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row, int col)const{
      return 0;
    }

    /*
     * function: num_rows
     * description:  returns number of rows in world
     */
    int num_rows()const {
      return 0;
    }

    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const {
      return 0;
    }



};

#endif
