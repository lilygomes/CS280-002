/*
 * Lily Gomes
 * CS 280-002
 * Project 1: Knight's Tour
 * 4 June 2026
 */

#include <iostream>
#include <format>

using namespace std;

// board to traverse
// row, col
short board[8][8] = {0}; 
// where am i?
short row, col = 0;
// how many times have i moved?
short turns = 1;
// syntactic sugar
const short KNIGHT = 32766;
// parameters
const short START_ROW = 0;
const short START_COL = 0;

// prints out board
void print_board(Chess* c) {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      short spot = c->board[y][x];
      if (spot == KNIGHT)
        cout << "  K ";
      else
        // pad outputs to three spaces
        cout << (spot < 100 ? (spot < 10 ? "  " : " ") : "") << spot << " ";
    }
    cout << endl;
  }
}

// check if board solved
bool is_solved(Chess* b) {
  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 8; x++)
       if (b->board[y][x] == 0) return false;
  return true;
}

// movement function
enum Movement_direction {upleft, upright, leftup, leftdown, rightup, rightdown, downright, downleft, unset};
bool move(Movement_direction d, Chess* b) {
  // ensure move is in bounds
  bool test = false;
  switch (d) {
    case Movement_direction::upright:
      test = (col + 1 < 8 && row - 2 >= 0);
      break;
    case Movement_direction::upleft:
      test = (col - 1 >= 0 && row - 2 >= 0);
      break;
    case Movement_direction::rightup:
      test = (col + 2 < 8 && row - 1 >= 0);
      break;
    case Movement_direction::rightdown:
      test = (col + 2 < 8 && row + 1 < 8);
      break;
    case Movement_direction::leftup:
      test = (col - 2 >= 0 && row - 1 >= 0);
      break;
    case Movement_direction::leftdown:
      test = (col - 2 >= 0 && row + 1 < 8);
      break;
    case Movement_direction::downright:
      test = (col + 1 < 8 && row + 2 < 8);
      break;
    case Movement_direction::downleft:
      test = (col - 1 >= 0 && row + 2 < 8);
      break;
    default:
      cout << "Cannot move to unset direction" << endl;
      return false;
  }
  // If move fails bounds check, fail move
  if (!test) return false;
  else {
    // record we have visited this tile on which turn
    b->board[row][col] = turns;
    // set location to move piece to based on direction 
    switch (d) {
      case Movement_direction::upright:
        row -= 2; col += 1;
        break;
      case Movement_direction::upleft:
        row -= 2; col -= 1;
        break;
      case Movement_direction::downright:
        row += 2; col += 1;
        break;
      case Movement_direction::downleft:
        row += 2; col -= 1;
        break;
      case Movement_direction::leftup:
        row -= 1; col -= 2;
        break;
      case Movement_direction::leftdown:
        row += 1; col -= 2;
        break;
      case Movement_direction::rightup:
        row -= 1; col += 2;
        break;
      case Movement_direction::rightdown:
        row += 1; col += 2;
        break;
      default:
        cout << "Cannot move to unset direction" << endl;
        return false;
    }
    // move knight to spot
    b->board[row][col] = KNIGHT;
    return true;
  }
} 

int main(int argc, char** argv) {
  // place knight in top-left corner
  Chess c;
  c.board[START_ROW][START_COL] = KNIGHT;

  // keep moving through the board until we return to start 
  do {
    Movement_direction next_move = Movement_direction::unset;
    // for each direction, record if it is accessible, and if it has been tread previously
    // [0][_]: up  [1][_]: left  [2][_]: right  [3][_]: down
    // [_][0]: left/up  [_][1]: right/down
    // -1: invalid, 0: previously tread, 1: free
    short directions[4][2] = {-1};
    // check upwards
    if (row > 1) {
      // check upleft
      if (col > 0)
        directions[0][0] = (c.board[row - 2][col - 1] == 0) ? 1 : 0;
      else
        directions[0][0] = -1;
      // check upright
      if (col < 7)
        directions[0][1] =  (c.board[row - 2][col + 1] == 0) ? 1 : 0;
      else
        directions[0][1] = -1;
    } else 
      directions[0][0] = directions[0][1] = -1;
    // check leftwards
    if (col > 1) {
      // check leftup
      if (row > 0)
        directions[1][0] = (c.board[row - 1][col - 2] == 0) ? 1 : 0;
      else
        directions[1][0] = -1;
      // check leftdown
      if (row < 6)
        directions[1][1] =  (c.board[row + 1][col - 2] == 0) ? 1 : 0;
      else
        directions[1][1] = -1;
    } else
      directions[1][0] = directions[1][1] = -1;
    // check rightwards
    if (col < 6) {
      // check rightup
      if (row > 0)
        directions[2][0] = (c.board[row - 1][col + 2] == 0) ? 1 : 0;
      else
        directions[2][0] = -1;
      // check rightdown
      if (row < 7)
        directions[2][1] =  (c.board[row + 1][col + 2] == 0) ? 1 : 0;
      else
        directions[2][1] = -1;
    } else
      directions[2][0] = directions[2][1] = -1;
    // check downwards
    if (row < 6) {
      // check downleft
      if (col > 0)
        directions[3][0] = (c.board[row + 2][col - 1] == 0) ? 1 : 0;
      else
        directions[3][0] = -1;
      // check downright
      if (col < 7)
        directions[3][1] =  (c.board[row + 2][col + 1] == 0) ? 1 : 0;
      else
        directions[3][1] = -1;
    } else
      directions[3][0] = directions[3][1] = -1;

    // print available directions  TODO remove
    if (directions[0][0] > -1) cout << "ul ";
    if (directions[0][1] > -1) cout << "ur ";
    if (directions[1][0] > -1) cout << "lu ";
    if (directions[1][1] > -1) cout << "ld ";
    if (directions[2][0] > -1) cout << "ru ";
    if (directions[2][1] > -1) cout << "rd ";
    if (directions[3][0] > -1) cout << "dl ";
    if (directions[3][1] > -1) cout << "dr ";
    cout << endl;

    // go through directions until a move is picked
    while (next_move == Movement_direction::unset) {
      // look for unvisited tiles
      int next_direction, next_side = 0;
      bool found_move = false;
      for (next_direction = 0; next_direction < 4; next_direction++) {
        if (directions[next_direction][0] == 1) {
          found_move = true;
          break;
        } else if (directions[next_direction][1] == 1) {
          next_side = 1;
          found_move = true;
          break;
        }
      }
      // if no unvisited tiles found, find visited tile 
      if (!found_move) {
        for (next_direction = 0; next_direction < 4; next_direction++) {
          if (directions[next_direction][0] == 0) {
            found_move = true;
            break;
          } else if (directions[next_direction][1] == 0) {
            next_side = 1;
            found_move = true;
            break;
          }
        }
      }

      if (directions[next_direction][next_side] != -1)
        switch (next_direction) {
          case 0:
            next_move = (next_side == 0) ? Movement_direction::upleft : Movement_direction::upright;
            break;
          case 1:
            next_move = (next_side == 0) ? Movement_direction::leftup : Movement_direction::leftdown;
            break;
          case 2:
            next_move = (next_side == 0) ? Movement_direction::rightup : Movement_direction::rightdown;
            break;
          case 3:
            next_move = (next_side == 0) ? Movement_direction::downleft : Movement_direction::downright;
            break;
          default:
            cout << "Illegal next move " << next_direction << ":" << "next_side" << endl;
            return 1;
        }
    }
    // Check we can move piece
    if (next_move != Movement_direction::unset) {
      // on failed move, break execution
      if (move(next_move, &c)) {
        print_board(&c); // TODO remove
        cout << "Turn " << ++turns << " ---" << endl;
      } else {
        string move_name = "";
        switch (next_move) {
          case Movement_direction::upleft:
            move_name = "upleft";
            break;
          case Movement_direction::upright:
            move_name = "upright";
            break;
          case Movement_direction::leftup:
            move_name = "leftup";
            break;
          case Movement_direction::leftdown:
            move_name = "leftdown";
            break;
          case Movement_direction::rightdown:
            move_name = "rightdown";
            break;
          case Movement_direction::rightup:
            move_name = "rightup";
            break;
          case Movement_direction::downleft:
            move_name = "downleft";
            break;
          case Movement_direction::downright:
            move_name = "downright";
            break;
          default:
            move_name = "INVALID";
        }
        cout << "Failed making move " << move_name << " from [" << row << "][" << col << "]" << endl;
        print_board(&c);
        return 3;
      }
    } else {
      cout << "Cannot determine next move from position [" << row << "][" << col << "]" << endl;
      return 2;
    }
  } while (!is_solved(&c));


  // at the end, print the board
  print_board(&c);
  
  // exit
  return 0;
}
