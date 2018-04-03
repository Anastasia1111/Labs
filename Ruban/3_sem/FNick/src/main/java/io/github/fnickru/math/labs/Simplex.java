package io.github.fnickru.math.labs;

import io.github.fnickru.math.exeptions.NoSolutionException;
import io.github.fnickru.math.struct.simplex.Problem;
import io.github.fnickru.math.util.FileWorker;

public class Simplex {

    public static void main(String[] args) {
        final int n = 6;
        Problem[] problems = new Problem[n];
        for (int i = 0; i < n; ++i)
            problems[i] = FileWorker.readLPP(String.format("./src/main/resources/simplex%d.txt", i + 1));
        for (int i = 0; i < n; ++i) {
            Problem problem = problems[i];
            System.out.println(problem);
            try {
                problem.solve();
                System.out.println(problem.getAnswer());
            } catch (NoSolutionException e) {
                e.printStackTrace();
                if (i == 3 || i == 4) System.err.println("...and that's ok!");
            }
        }
    }
}