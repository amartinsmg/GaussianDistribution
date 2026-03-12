public class Hash {
  public static int hash32(int x) {
    x ^= x >> 16;
    x *= 0x7feb352d;
    x ^= x >> 15;
    x *= 0x846ca68d;
    x ^= x >> 16;
    return x;
  }
}