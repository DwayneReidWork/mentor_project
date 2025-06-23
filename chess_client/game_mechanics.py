import re
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

        board.move_piece(from_row, from_col, to_row, to_col)
        print(f"Moved {piece.name} from {from_square} to {to_square}.")
        board.display()
        return board

def notation_to_index(square: str):
    file = square[0].lower()
    rank = square[1]

    #ord converts a char 2 its unicode #
    #input letter minus 'a' gives column coords.
    col = ord(file) - ord('a')
    #going backwards from 8 to invert the count for chess notation counting bottom up
    row = 8 - int(rank)
    return (row, col)