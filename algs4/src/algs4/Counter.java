package algs4;

/**
 * A mutable data type to encapsulate a counter.
 */
public class Counter implements Comparable<Counter> {

  private final String name;
  private int count = 0;

  /**
   * Initializes a new counter starting at 0, with the given id.
   *
   * @param id the name of the counter
   */
  public Counter(String id) {
    name = id;
  }

  /**
   * Increments the counter by 1.
   */
  public void increment() {
    count++;
  }

  /**
   * Returns the current value of this counter.
   *
   * @return the current value of this counter
   */
  public int tally() {
    return count;
  }

  /**
   * Compares this counter to the specified counter.
   *
   * @param that the other counter
   * @return <tt>0</tt> if the value of this counter equals
   *         the value of that counter; a negative integer if
   *         the value of this counter is less than the value of
   *         that counter; and a positive integer if the value
   *         of this counter is greater than the value of that
   *         counter
   */
  @Override
  public int compareTo(Counter that) {
    if      (this.count < that.count) return -1;
    else if (this.count > that.count) return +1;
    else                              return  0;
  }

}
