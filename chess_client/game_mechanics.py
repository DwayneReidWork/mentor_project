import re
#from game_pieces import PieceType, Board
from .game_pieces import PieceType, Board

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

        if piece == PieceType.EMPTY:
            print("No piece at that location to move.")
            continue

        to_square = input("Enter the destination square: ")
        if not re.match(valid_squares, to_square):
            print("Invalid destination square.")
            continue
        
        to_row, to_col = notation_to_index(to_square)

        if check_valid_move(piece, from_row, from_col, to_row, to_col, board) == True:
            board.move_piece(from_row, from_col, to_row, to_col)
            print(f"Moved {piece.name} from {from_square} to {to_square}.")
            board.display()
            return board
        else:
            continue

def notation_to_index(square: str):
    file = square[0].lower()
    rank = square[1]

    #ord converts a char 2 its unicode #
    #input letter minus 'a' gives column coords.
    col = ord(file) - ord('a')
    #going backwards from 8 to invert the count for chess notation counting bottom up
    row = 8 - int(rank)
    return (row, col)

def check_valid_move(piece, from_row, from_col, to_row, to_col, board: Board):
    valid = False
    match piece & PieceType.NOCOLOR:
        case PieceType.PAWN:
            if piece & PieceType.WHITE:
                if (to_row != (from_row + 1)):
                    print("Invalid Move")
                else:
                    valid = True
            elif piece & PieceType.BLACK:
                if (to_row != (from_row - 1)):
                    print("Invalid Move")
                else:
                    valid = True
        case PieceType.KNIGHT:
            print("Knight Logic")
            valid = True
        case PieceType.BISHOP:
            if piece & PieceType.NOCOLOR:
                direction_x = to_col - from_col
                direction_y = to_row - from_row

                #for calculating left/right and up/down and if blocked
                if abs(direction_x) == abs(direction_y):
                    step_x = 1 if direction_x > 0 else -1
                    step_y = 1 if direction_y > 0 else -1

                    # Check squares along the diagonal, excluding end
                    x, y = from_col + step_x, from_row + step_y
                    while x != to_col and y != to_row:
                        if board.get_piece(y, x) != PieceType.EMPTY:
                            print("Path is blocked!")
                        else:
                            x += step_x
                            y += step_y
                        valid = True
                else:
                    print("Invalid bishop move (must be diagonal).")
        case PieceType.ROOK:
            print("Rook Logic")
            valid = True
        case PieceType.QUEEN:
            print("Queen Logic")
            valid = True
        case PieceType.KING:
            print("King Logic")
            valid = True
        case _:
            print("Unknown piece")
    return valid