#ifndef __BOARD_H
  #include "../hdr/Board.h"
#endif

#ifndef __SHIP_TYPE_H
  #include "../hdr/ShipType.h"
#endif

#ifndef __GLIBCXX_IOSTREAM
  #include <iostream>
#endif

#ifndef __GLIBCXX_STRING
  #include <string>
#endif

#ifdef DEBUG
  void showGuide(){
    int cap= BOARD_ROWS_NUM * BOARD_COLS_NUM;
    for(int i=0;i<cap;i++){
      std::cout
        <<"[ "
        << i
        <<" ]";
        if( (i+1) % BOARD_COLS_NUM == 0)
          std::cout<<std::endl;
        else
          std::cout<<' ';
    }
    std::cout<<std::endl;
  };
#endif

#define print_bool(a) (std::cout<< ( (a)? "true":"false") <<std::endl )

/* read_add_ship: reads userinput for the location and length of ships to be added */
void read_add_ship(int dest[2]); // TODO make it inline

int main(int argc,char **argv){

  /*ships::Board *b1=new ships::Board();*/
  ships::Board b1; /* no need to put it on heap for testing */
  ships::ShipType st=ships::DESTROYER;
  bool test=b1.add_ship(1,st,BOARD_DIRECTION_X);

  st=ships::CRUISER;
  test=b1.add_ship(5,st,BOARD_DIRECTION_Y);
  print_bool(test); // this should be true, but is false. however the add_ship is working

  test=b1.add_ship(1,st,BOARD_DIRECTION_X);
  print_bool(test);
  test=b1.add_ship(1,st,BOARD_DIRECTION_X);
  print_bool(test);
  test=b1.add_ship(1,st,BOARD_DIRECTION_X);
  print_bool(test);
  test=b1.add_ship(1,st,BOARD_DIRECTION_X);
  print_bool(test);

  /*test=b1.add_ship(16,5,BOARD_DIRECTION_Y);
  test=b1.add_ship(17,2,BOARD_DIRECTION_Y);
  test=b1.add_ship(18,2,BOARD_DIRECTION_Y);*/
  // b1.hit(0,2);
  /*b1.hit(0,5);
  b1.hit(0,4);
  b1.hit(0,3);
  // printBool(shit);
  #ifdef DEBUG
    showGuide();
  #endif*/
  b1.show();

  return 0;
}
/*
int[2] read_add_ship(void){

  bool read=false;
  int[2] len_dir;
  do{
    std::string in;
    cin>>in;
  }while(!read);


}
*/
