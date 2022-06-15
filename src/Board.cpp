#ifndef __BOARD_H
  #include "../hdr/Board.h"
#endif

#ifndef __SHIP_TYPE_H
  #include "../hdr/ShipType.h"
#endif

#ifndef __GLIBCXX_IOSTREAM
  #include <iostream>
#endif

namespace ships{

  /* just init the object with default values */
  Board::Board():
    m_health(0),
    m_board(new int[BOARD_ROWS_NUM * BOARD_COLS_NUM]),
    m_ships_left{3,2,1,1}
  {}

  Board::~Board(){
    delete[] m_board;
    /*delete[] m_ships_left;*/ // this is not needed since the array isn't dynamically allocated
  }

  bool Board::is_available(int start,int len,bool direction){
    int cap;
    if(start<0) return false;
    cap = BOARD_ROWS_NUM * BOARD_COLS_NUM;
    if(direction == BOARD_DIRECTION_X){
      if(
        (start+1) % BOARD_COLS_NUM == 0 // if start itself is the last on the line
        || (start+len) >= cap // out of bound
        || ((start+len) % BOARD_COLS_NUM )==0 // gets out of the line
      ) return false;

      for(int i=start;len>0;i++){
        if(m_board[i]==TILE_TAKEN)
          return false;
        len--;
      }
    }

    else {
      for(int i=start;len>0 ;i+=BOARD_COLS_NUM){
        if( i>=cap || m_board[i]==TILE_TAKEN)
          return false;
        len--;
      }
    }
    return true;
  }

  bool Board::add_ship(int start,ShipType& st,bool direction){

    int len=st;
    int indx;

    switch(st){
      case ships::DESTROYER : indx=0 ;break;
      case ships::CRUISER   : indx=1 ;break;
      case ships::FRIGATE   : indx=2 ;break;
      case ships::CARRIER   : indx=3 ;break;
      default:break;
    }

    if(indx<0){
      std::cerr<<"INDEX < 0 "<<std::endl;
      return false;
    }

    /* no ships remaining or no slots available */
    if(m_ships_left[indx]<=0 || !is_available(start,len,direction))return false;

    m_ships_left[indx]--;
    #ifdef DEBUG
      std::cout<<"index:\t"<<indx;
      switch(indx){
        case ships::DESTROYER : std::cout<<"\tDESTROYER left:\t";break;
        case ships::CRUISER   : std::cout<<"\tCRUISER left:\t";break;
        case ships::FRIGATE   : std::cout<<"\tFRIGATE left:\t";break;
        case ships::CARRIER   : std::cout<<"\tCARRIER left:\t";break;
        default:break;
      }
      std::cout<<m_ships_left[indx]<<std::endl;
    #endif

    /* finally adding the ship */
    if(direction==BOARD_DIRECTION_Y){
      for(;len>=0;len--){
        m_board[start]=TILE_TAKEN;
        start+= BOARD_COLS_NUM;
      }
    }
    else
      for(;len>=0;len--){
        m_board[start]=TILE_TAKEN;
        start++;
      }

    m_health+=len;
    return true;
  }

  int Board::health()const{return m_health;}

  bool Board::hit(int x, int y){
    int cap=BOARD_ROWS_NUM * BOARD_COLS_NUM;
    if( x>= BOARD_COLS_NUM || x<0 || x>= cap || y>= BOARD_ROWS_NUM) return false;
    if( (y=x+(y* BOARD_COLS_NUM)) >= cap) return false; // calculating the real position and saving it in y
    m_board[y]=TILE_HIT;
    return true;
  }

  void Board::show(){
    int cap= BOARD_ROWS_NUM * BOARD_COLS_NUM;
    int row=0;
    std::cout<<std::endl;
    for(int i=0;i< BOARD_COLS_NUM; i++)
      std::cout<<" "<< i <<"  ";
    std::cout<<std::endl;
    for(int i=0;i<cap;i++){ /* NOTE: i is re-used here */
      std::cout
        <<"["
        #ifdef DEBUG
          <<(m_board[i]==TILE_TAKEN?'$':(m_board[i]==TILE_HIT?TILE_HIT_CHAR:' '))
        #else
          <<(m_board[i]==TILE_HIT?TILE_HIT_CHAR:' ') // i.e. hide information from oponent's eyes
        #endif
        <<"]";
        if( (i+1) % BOARD_COLS_NUM == 0){
          std::cout<<" : "<<row<<std::endl;
          row++;
        }
        else
          std::cout<<' ';
    }
    std::cout<<std::endl;
  }

}
