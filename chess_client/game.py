import cmd2
import socket
import struct
from .netcomm import send_all, recv_expected
from .packet import Connect

class CmdController(cmd2.Cmd):
    
    def __init__(self):
        super().__init__()
        self.sock = None
        self.debug = True

    port_parser = cmd2.Cmd2ArgumentParser()
    port_parser.add_argument('port', type=int, nargs='?', action='store', default = 1234, help='What port would you like to connect to?')
    @cmd2.with_argparser(port_parser)
    def do_connect(self, args):
        connection = ("127.0.0.1", args.port)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect(connection)

        connection_packet = Connect(args.port).pack()
        send_all(self.sock, connection_packet)