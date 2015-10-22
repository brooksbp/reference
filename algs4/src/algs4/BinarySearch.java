package algs4;

import java.util.Arrays;

public class BinarySearch {

  /**
   * This class should not be instantiated.
   */
  private BinarySearch() { }

  /**
   * Returns the index of the specified key in the specified array.
   *
   * @param  a the array of integers, must be sorted in ascending order
   * @param  key the search key
   * @return index of key in array <tt>a</tt> if present; <tt>-1</tt> otherwise
   */
  public static int indexOf(int[] a, int key) {
    int lo = 0;
    int hi = a.length - 1;
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      if      (key < a[mid]) hi = mid - 1;
      else if (key > a[mid]) lo = mid + 1;
      else return mid;
    }
    return -1;
  }

}
