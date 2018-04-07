package io.github.fnickru.math.struct;

import io.github.fnickru.math.exeptions.NoSolutionException;

public interface LinearProgrammingProblem {

    void solve() throws NoSolutionException;

    String getSolution();

    static void printSolution(LinearProgrammingProblem problem) {
        try {
            problem.solve();
            System.out.println(problem.getSolution());
        } catch (NoSolutionException e) {
            e.printStackTrace();
        }
    }

}
