package algs4;

import static org.junit.Assert.*;
import org.junit.Test;

public class CounterTest {

  @Test
  public void testCounter() {
    Counter counter = new Counter("myCounter");
    assertEquals(0, counter.tally());
  }

}
