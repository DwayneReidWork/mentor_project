from enum import IntEnum, auto
import struct

class PacketType(IntEnum):
    CONNECT = 1 
    MOVE = auto()
    DISPLAY_BOARD = auto() # Connect will also start new game but this one wont need to send over username

class Packet:
    def __init__(self, p_type: PacketType):
        self._p_type = p_type

    @property
    def packet_type(self):
        return self._p_type

    def packet_size(self) -> int:
        return 0 # for no header size inclusion
    
    def pack(self) -> bytes:
        # Format: Network(Big-endian + Single Byte)
        return struct.pack('!BI', self.packet_type, self.packet_size())
    
class Connect(Packet):
    def __init__(self, username: str):
        super().__init__(PacketType.CONNECT)
        self.username = username

    def packet_size(self):
        username_bytes = self.username.encode('utf-8')
        return struct.calcsize('!i') + len(username_bytes)

    def pack(self) -> bytes:
        username_bytes = self.username.encode('utf-8')
        # Format: Network(Big-endian + Single Byte)
        return super().pack() + struct.pack('!i', len(username_bytes)) + username_bytes

class Move(Packet):
    def __init__(self, start_square, end_square):
        super().__init__(PacketType.MOVE)
        self.start_square = start_square
        self.end_square = end_square

    def packet_size(self):
        move_bytes = self.start_square.encode('utf-8') + b" " + self.end_square.encode('utf-8')
        return len(move_bytes)

    def pack(self) -> bytes:
        move_bytes = self.start_square.encode('utf-8') + b" " + self.end_square.encode('utf-8')
        # Format: Network(Big-endian + Single Byte)
        return super().pack() + move_bytes
    
class Display_Board(Packet):
    def __init__(self):
        super().__init__(PacketType.DISPLAY_BOARD)

    def packet_size(self):
        return 0

    def packet(self):
        return super().pack()