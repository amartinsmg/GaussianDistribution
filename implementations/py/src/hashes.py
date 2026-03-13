def int32(n):
    n &= 0xFFFFFFFF
    if n & 0x80000000:
        n -= 0x100000000
    return n


def hash32(x: int):
    x = int32(x)
    x ^= int32(x >> 16)
    x = int32(x * 0x7FEB352D)
    x ^= int32(x >> 15)
    x = int32(x * 0x846CA68D)
    x ^= int32(x >> 16)
    return int32(x)
