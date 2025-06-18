from enum import IntFlag, auto

#Int Flag allows combination of members with bitwise operations
#So you can do things like King|Black and Rook|White etc
class PieceType(IntFlag):
    EMPTY = 0
    PAWN = 1
    KNIGHT = auto()
    BISHOP = auto()
    ROOK = auto()
    QUEEN = auto()
    KING = auto()
    BLACK = auto()
    WHITE = auto()
    NOCOLOR = 0b00111111

PIECE_UNICODE = {
    PieceType.WHITE | PieceType.KING:'\u2654',
    PieceType.WHITE | PieceType.QUEEN:'\u2655',
    PieceType.WHITE | PieceType.ROOK: '\u2656',
    PieceType.WHITE | PieceType.BISHOP:'\u2657',
    PieceType.WHITE | PieceType.KNIGHT: '\u2658',
    PieceType.WHITE | PieceType.PAWN: '\u2659',
    PieceType.BLACK | PieceType.KING: '\u265A',
    PieceType.BLACK | PieceType.QUEEN: '\u265B',
    PieceType.BLACK | PieceType.ROOK: '\u265C',
    PieceType.BLACK | PieceType.BISHOP: '\u265D',
    PieceType.BLACK | PieceType.KNIGHT: '\u265E',
    PieceType.BLACK | PieceType.PAWN: '\u265F',
    PieceType.EMPTY: '.', #'\u25A1' <- unicode for white square
}

class Board:
    def __init__(self):
        # 8x8 grid all EMPTY
        self.grid = [[PieceType.EMPTY for _ in range(8)] for _ in range(8)]

    #potentially will be move
    def set_piece(self, row, col, piece):
        self.grid[row][col] = piece
    
    #quickset board
    def set_pieces(self, positions, piece):
        for row, col in positions:
            self.set_piece(row, col, piece)

    def get_piece(self, row, col):
        return self.grid[row][col]

    def display(self):
        for row in self.grid:
            #For printing out symbols
            print(' '.join(PIECE_UNICODE[piece] for piece in row))
            
            #enums have intrinsic things like.name and.value
            #This line prints out piece name
            #print(' '.join(f"{piece.name:7}" for piece in row))
            

    @staticmethod
    def new_board():
        board = Board()
        # White Pieces
        board.set_pieces([(1, col) for col in range(8)], PieceType.WHITE | PieceType.PAWN)
        board.set_pieces([(0, 0), (0, 7)], PieceType.WHITE | PieceType.ROOK)
        board.set_pieces([(0, 1), (0, 6)], PieceType.WHITE | PieceType.KNIGHT)
        board.set_pieces([(0, 2), (0, 5)], PieceType.WHITE | PieceType.BISHOP)
        board.set_piece(0, 3, PieceType.WHITE | PieceType.QUEEN)
        board.set_piece(0, 4, PieceType.WHITE | PieceType.KING)

        #Black Pieces
        board.set_pieces([(6, col) for col in range(8)], PieceType.BLACK | PieceType.PAWN)
        board.set_pieces([(7, 0), (7, 7)], PieceType.BLACK | PieceType.ROOK)
        board.set_pieces([(7, 1), (7, 6)], PieceType.BLACK | PieceType.KNIGHT)
        board.set_pieces([(7, 2), (7, 5)], PieceType.BLACK | PieceType.BISHOP)
        board.set_piece(7, 3, PieceType.BLACK | PieceType.QUEEN)
        board.set_piece(7, 4, PieceType.BLACK | PieceType.KING)

        return board
    
    def __str__(self):
        lines = []
        lines.append("    A   B   C   D   E   F   G   H")
        horiz = "  +" + "---+" * 8
        lines.append(horiz)
        for r in range(8):
            row_pieces = [f" {PIECE_UNICODE[self.get_piece(r, c)]} " for c in range(8)]
            lines.append(f"{8 - r} |" + "|".join(row_pieces) + f"| {8 - r}")
            lines.append(horiz)
        lines.append("    A   B   C   D   E   F   G   H")
        return "\n".join(lines)







#Board.__str__(self=Board.new_board())
#piece = PieceType.BLACK | PieceType.ROOK

# if ((piece & (PieceType.WHITE | PieceType.QUEEN)) == (PieceType.WHITE | PieceType.QUEEN)):
#   # is a white queen
  
# if ((piece & PieceType.NOCOLOR) == PieceType.BISHOP):
#   # any bishop
  
# # you could make predefined versions of each piece in Python or C as well
# # in piece_type.py
# WHITE_ROOK = PieceType.WHITE | PieceType.ROOK


#INITIAL BOARD LAYOUT

# board = [ [" "] * 8 for _ in range(8)]

# def print_chess_board(board):
#     print("   A   B   C   D   E   F   G   H")
#     print(" +" + "---+" * 8)
#     for i, row in enumerate(board):
#         row_str = f"{8 - i}| " + " | ".join(row) + f" |{8 - i}"
#         print(row_str)
#         print(" +" + "---+" * 8)
#     print("   A   B   C   D   E   F   G   H")