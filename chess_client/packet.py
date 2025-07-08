from enum import IntEnum, auto
import struct

class PacketType(IntEnum):
    CONNECT = 1

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
    def __init__(self, port: int, username: str):
        super().__init__(PacketType.CONNECT)
        self.port = port
        self.username = username

    def packet_size(self):
        username_bytes = self.username.encode('utf-8')
        return struct.calcsize('!ii') + len(username_bytes)

    def pack(self) -> bytes:
        username_bytes = self.username.encode('utf-8')
        # Format: Network(Big-endian + Single Byte)
        return super().pack() + struct.pack('!ii', self.port, len(username_bytes)) + username_bytes