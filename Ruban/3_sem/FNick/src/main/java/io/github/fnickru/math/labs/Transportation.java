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
        /*
        p1 = 790
        p2 = 330
        p3 = 4150
        p4 = 693
         */
        for (int i = 0; i < n; ++i) {
            System.out.printf("Problem #%d\n", i + 1);
            TransportationProblem problem = problems[i];
            System.out.println(problem);
            LinearProgrammingProblem.printSolution(problem);
        }
    }

}
