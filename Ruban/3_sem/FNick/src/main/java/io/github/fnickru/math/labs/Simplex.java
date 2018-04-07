package io.github.fnickru.math.labs;

import io.github.fnickru.math.struct.LinearProgrammingProblem;
import io.github.fnickru.math.struct.simplex.SimplexProblem;
import io.github.fnickru.math.util.FileWorker;

public class Simplex {

    public static void main(String[] args) {
        final int n = 6;
        SimplexProblem[] problems = new SimplexProblem[n];
        for (int i = 0; i < n; ++i)
            problems[i] = FileWorker.readLPP(String.format("./src/main/resources/simplex/simplex%d.txt", i + 1));
        for (int i = 0; i < n; ++i) {
            SimplexProblem problem = problems[i];
            System.out.println(problem);
            LinearProgrammingProblem.printSolution(problem);
        }
    }
}