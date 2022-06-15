#ifndef __BOARD_H
#define __BOARD_H 1
#define BOARD_DIRECTION_X 0
#define BOARD_DIRECTION_Y 1
#define BOARD_ROWS_NUM 8
#define BOARD_COLS_NUM 8
#define MAX_SHIP_LEN 5
#define TILE_TAKEN 1
#define TILE_HIT 2
#define TILE_EMPTY 0
#define TILE_HIT_CHAR 'X'

#ifndef __SHIP_TYPE_H
  #include "./ShipType.h"
#endif

namespace ships{

  class Board{

    private:

      /* number of ship types one Board has yet to deploy */
      /* DESTROYER ,CRUISER , FRIGATE, CARRIER */
      int m_ships_left[4];
      int* m_board;
      int m_health;
      bool is_available(int start,int len,bool direction);

    public:

      Board();
      ~Board();
      bool add_ship(int start,ShipType& st,bool direction);
      bool hit(int x,int y);
      int health()const;
      void show();
  };

}
#endif
