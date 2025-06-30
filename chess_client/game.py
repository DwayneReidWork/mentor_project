import cmd2
import socket
from .netcomm import send_all, recv_expected
from .packet import Connect
from .game_pieces import PieceType as PT, Board
from .game_mechanics import move_piece
#for debugging
# from netcomm import send_all, recv_expected
# from packet import Connect
# from game_pieces import PieceType as PT, Board
# from game_mechanics import move_piece

def port_type(port_str: str) -> int:
    port = int(port_str)
    if port < 0 or port > 65535:
        raise ValueError(f"Port must be in the range [0-65535], have: {port}")
    return port

class CmdController(cmd2.Cmd):
    
    def __init__(self):
        super().__init__()
        self.sock = None
        self.board = Board.new_board()
        self.debug = True

    port_parser = cmd2.Cmd2ArgumentParser()
    port_parser.add_argument('port', type=port_type, nargs='?', action='store', default = 1234, help='What port would you like to connect to?')
    @cmd2.with_argparser(port_parser)
    def do_connect(self, args):
        connection = ("127.0.0.1", args.port)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect(connection)

        connection_packet = Connect(args.port).pack()
        send_all(self.sock, connection_packet)

    def do_display_board(self, args):
        self.board.display()

    def do_move_piece(self, args):
        move_piece(self.board)
    
    def do_new_game(self, args):
        self.board = Board.new_board()
        move_piece(self.board)

    def do_small_display(self, args):
        Board.display_small(self.board)