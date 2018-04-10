package io.github.fnickru.math.labs;

import io.github.fnickru.math.struct.LinearProgrammingProblem;
import io.github.fnickru.math.struct.transportation.TransportationProblem;
import io.github.fnickru.math.util.FileWorker;

public class Transportation {

    public static void main(String[] args) {
        final int n = 2;
        TransportationProblem[] problems = new TransportationProblem[n];
        for (int i = 0; i < n; ++i)
            problems[i] = FileWorker.readTP(String.format("./src/main/resources/transportation/problem%d.txt", i + 1));
        for (int i = 0; i < n; ++i) {
            TransportationProblem problem = problems[i];
            System.out.println(problem);
            LinearProgrammingProblem.printSolution(problem);
        }
    }

}