package Utils;

import java.util.Random;

public class RandomNumberArrayGenerator {
    private Integer n = Integer.MAX_VALUE;
    private Random r = new Random();

    public RandomNumberArrayGenerator(Integer n) {
        this.n = n;
    }

    public Integer Get() {
        return (this.r.nextInt()%this.n);
    }
}
