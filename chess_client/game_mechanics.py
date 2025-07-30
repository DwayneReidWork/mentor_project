import re
from .game_pieces import PieceType, Board
#from game_pieces import PieceType, Board

#Val is the integer containing piece type/color in bit flags
def decode_piece(val: int) -> tuple[PieceType, PieceType]:
    #zero out color bits to just get piece
    piece_type = PieceType(val & PieceType.NOCOLOR)
    #zero out everything but color bits for color
    color = PieceType(val & PieceType.COLOR_MASK)
    return piece_type, color

def move_piece(board: Board):
    valid_squares = "^[a-hA-H][1-8]$"

    board.display()

    while True:
        from_square = input("Enter the chess notation of the square you'd like to move: ")
        if not re.match(valid_squares, from_square):
            print("Invalid source square.")
            continue

        from_row, from_col = notation_to_index(from_square)

        piece = board.get_piece(from_row, from_col)

        print(f"Selected piece at {from_square} is {piece.name}")
        if piece == PieceType.EMPTY:
            print("No piece at that location to move.")
            continue

        to_square = input("Enter the destination square: ")
        if not re.match(valid_squares, to_square):
            print("Invalid destination square.")
            continue
        
        to_row, to_col = notation_to_index(to_square)

        if check_valid_move(piece, from_row, from_col, to_row, to_col, board):
            end_piece = board.get_piece(to_row, to_col)
            if (end_piece == PieceType.EMPTY or
            (piece & PieceType.WHITE and end_piece & PieceType.BLACK) or
            (piece & PieceType.BLACK and end_piece & PieceType.WHITE)):
                board.move_piece(from_row, from_col, to_row, to_col)
                print(f"Moved {piece.name} from {from_square} to {to_square}.")
                board.display()
            elif (end_piece == PieceType.EMPTY or
            (piece & PieceType.WHITE and end_piece & PieceType.WHITE) or
            (piece & PieceType.BLACK and end_piece & PieceType.BLACK)):
                print("Space Occupied by same color piece. Invalid Move.")
            board.display()
            #return board
        else:
            #hit when invalid move tried
            print("Some other Error Occured.")
            continue

def notation_to_index(square: str):
    file = square[0].lower()
    rank = square[1]

    #ord converts a char 2 its unicode #
    #input letter minus 'a' gives column coords.
    col = ord(file) - ord('a')
    #going backwards from 8 to invert the count for chess notation counting bottom up
    row = Board.BOARD_SIZE - int(rank)
    return (row, col)

def check_valid_move(piece, start_row, start_col, end_row, end_col, board: Board):
    valid = False
    match piece & PieceType.NOCOLOR:
        case PieceType.PAWN:
            #directional movement by color
            direction = -1 if piece & PieceType.WHITE else 1
            #set home row for each color
            home_row = 6 if piece & PieceType.WHITE else 1
            row_diff = end_row - start_row
            col_diff = end_col - start_col

            target = board.get_piece(end_row, end_col)

            if row_diff == direction and col_diff == 0:
                if target & PieceType.NOCOLOR == PieceType.EMPTY:
                    valid = True
                else:
                    print("Blocked! Can't move forward to occupied square.")
                    valid = False
            # 2 square move from start
            elif row_diff == 2 * direction and col_diff == 0 and start_row == home_row:
                intermediate_row = start_row + direction
                if (board.get_piece(intermediate_row, start_col) & PieceType.NOCOLOR == PieceType.EMPTY and
                    target & PieceType.NOCOLOR == PieceType.EMPTY):
                    valid = True
                else:
                    print("2 Step move blocked.")
                    valid = False
            # Diagonal capture
            elif row_diff == direction and abs(col_diff) == 1:
                if (target != PieceType.EMPTY and
                    (target & PieceType.COLOR_MASK) != (piece & PieceType.COLOR_MASK)):
                    valid = True
                else:
                    print("No enemy piece to capture diagonally.")
                    valid = False
            else:
                print("Invalid Pawn Move.")
                valid = False

        case PieceType.KNIGHT:
            jump = abs(end_row - start_row), abs(end_col - start_col)
            if jump in [(1,2), (2,1)]:
                valid = True    
            else:
                print("Invalid Knight move")

        case PieceType.BISHOP:
            direction_x = end_col - start_col
            direction_y = end_row - start_row

            #for calculating left/right and up/down and if blocked
            if abs(direction_x) == abs(direction_y):
                step_x = 1 if direction_x > 0 else -1
                step_y = 1 if direction_y > 0 else -1

                # Check squares in diags excluding end
                # the base move method will handle dealing with if the selected square is occupied by other piecde.
                x, y = start_col + step_x, start_row + step_y
                while x != end_col and y != end_row:
                    if board.get_piece(y, x) != PieceType.EMPTY:
                        print("Path is blocked!")
                        valid = False
                        return valid
                    else:
                        x += step_x
                        y += step_y
                valid = True
            else:
                print("Invalid Bishop move.")

        case PieceType.ROOK:
            direction_x = end_col - start_col
            direction_y = end_row - start_row
            
            #check that we're only moving left/right or up/down
            if (direction_x == 0 and direction_y != 0) or (direction_x != 0 and direction_y == 0):
                step_x = 0
                step_y = 0

                if direction_x != 0:
                    step_x = 1 if direction_x > 0 else -1
                if direction_y != 0:
                    step_y = 1 if direction_y > 0 else -1

                x, y = start_col + step_x, start_row + step_y

                #check for empty along path 
                while (x != end_col or y != end_row):
                    if board.get_piece(y, x) != PieceType.EMPTY:
                        print("Path is blocked!")
                        valid = False
                        return valid
                    x += step_x
                    y += step_y
                valid = True
            else:
                print("Invalid Rook move.")
                valid = False

        case PieceType.QUEEN:
            direction_x = end_col - start_col
            direction_y = end_row - start_row

            if (direction_x == 0 and direction_y != 0) or (direction_x != 0 and direction_y == 0):
                step_x = 0
                step_y = 0

                if direction_x != 0:
                    step_x = 1 if direction_x > 0 else -1
                if direction_y != 0:
                    step_y = 1 if direction_y > 0 else -1

                x, y = start_col + step_x, start_row + step_y

                while (x != end_col or y != end_row):
                    if board.get_piece(y, x) != PieceType.EMPTY:
                        print("Path is blocked!")
                        valid = False
                        return False
                    x += step_x
                    y += step_y
                valid = True

            elif abs(direction_x) == abs(direction_y):
                step_x = 1 if direction_x > 0 else -1
                step_y = 1 if direction_y > 0 else -1

                x, y = start_col + step_x, start_row + step_y
                while x != end_col and y != end_row:
                    if board.get_piece(y, x) != PieceType.EMPTY:
                        print("Path is blocked!")
                        valid = False
                        return valid
                    x += step_x
                    y += step_y
                valid = True

            else:
                print("Invalid Queen move.")
                valid = False

        case PieceType.KING:
            direction_x = end_col - start_col
            direction_y = end_row - start_row

            move = abs(direction_x), abs(direction_y)
            if move in [(0,1), (1,0), (1,1)]:
                valid = True    
            else:
                print("Invalid King Move")
                valid = False
    return valid