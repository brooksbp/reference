package algs4;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class BinarySearchTest {

  @Test
  public void testEmpty() {
    int[] a = { };
    assertEquals(-1, BinarySearch.indexOf(a, 7));
  }

  @Test
  public void testFound1() {
    int[] a = { 3 };
    assertEquals(0, BinarySearch.indexOf(a, 3));
  }

}
