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
  public void testNotFound() {
    int[] a = { 3 };
    assertEquals(-1, BinarySearch.indexOf(a, 7));
  }

  @Test
  public void testNotFound2() {
    int[] a = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 };
    assertEquals(-1, BinarySearch.indexOf(a, 8192));
  }

  @Test
  public void testFound() {
    int[] a = { 3 };
    assertEquals(0, BinarySearch.indexOf(a, 3));
  }

  @Test
  public void testFound2() {
    int[] a = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 };
    assertEquals(9, BinarySearch.indexOf(a, 1024));
  }

}
