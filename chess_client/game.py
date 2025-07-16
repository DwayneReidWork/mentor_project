import cmd2
import socket
from .netcomm import send_all, recv_expected
from .packet import Connect, Move, Display_Board
from .game_pieces import PieceType as PT, Board
from .game_mechanics import move_piece
#for debugging
# from netcomm import send_all, recv_expected
# from packet import Connect, Move, Display_Board
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
    port_parser.add_argument('user_name', type=str, action='store', help="Your Username")
    port_parser.add_argument('port', type=port_type, nargs='?', action='store', default = 1234, help='[Optional] What port would you like to connect to?')
    @cmd2.with_argparser(port_parser)
    def do_connect(self, args):
        if self.sock is not None:
            raise Exception('Self.Sock is not none. Potential connection error')
        connection = ("127.0.0.1", args.port)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect(connection)
        connection_packet = Connect(args.user_name).pack()
        send_all(self.sock, connection_packet)

    def do_display_board(self, args):
        if self.sock is None:
            raise Exception('Not Connected.')
        #self.board.display()
        display_pack = Display_Board().pack()
        send_all(self.sock, display_pack)

    move_parser = cmd2.Cmd2ArgumentParser()
    move_parser.add_argument('from_square', type=str, action='store', help='Please enter the grid square of the piece you would like to move and its destination (a-h & 1-8)Ex: c2 c3')
    move_parser.add_argument('to_square', type=str, action='store', help='Please enter the grid square of the piece you would like to move and its destination (a-h & 1-8)Ex: c2 c3')
    @cmd2.with_argparser(move_parser)
    def do_move_piece(self, args):
        if self.sock is None:
            raise Exception('Not Connected.')
        packet_obj = Move(args.from_square, args.to_square)

        # #shows packet size
        # print(packet_obj.packet_size())
        # #shows bytes
        # print(packet_obj.pack())

        send_all(self.sock, packet_obj.pack())
        #original way to move board will be replaced with just rendering board state as sent back by server
        #move_piece(self.board)
    
    def do_new_game(self, args):
        if self.sock is None:
            raise Exception('Not Connected.')
        self.board = Board.new_board()
        move_piece(self.board)

    def do_small_display(self, args):
        Board.display_small(self.board)