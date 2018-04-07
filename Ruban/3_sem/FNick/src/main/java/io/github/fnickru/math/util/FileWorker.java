package io.github.fnickru.math.util;

import io.github.fnickru.math.struct.*;
import io.github.fnickru.math.struct.simplex.CostFunction;
import io.github.fnickru.math.struct.simplex.Limitation;
import io.github.fnickru.math.struct.simplex.SimplexProblem;
import io.github.fnickru.math.struct.transportation.TransportationProblem;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class FileWorker {

    public static Matrix readMatrix(String filename) {
        Matrix matrix = null;
        try {
            List<String> lines = Files.readAllLines(Paths.get(filename));
            String[] size = lines.get(0).split(" ");
            matrix = new Matrix(Integer.valueOf(size[0]), Integer.valueOf(size[1]));
            for (int i = 0; i < matrix.rows(); ++i) {
                String[] values = lines.get(i + 1).split(" ");
                for (int j = 0; j < matrix.columns(); ++j)
                    matrix.set(new Fraction(values[j]), i, j);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return matrix;
    }

    public static SimplexProblem readLPP(String filename) {
        SimplexProblem problem = null;
        try {
            List<String> lines = Files.readAllLines(Paths.get(filename));
            List<Limitation> limitations = new ArrayList<>();
            CostFunction costFunction = CostFunction.valueOf(lines.remove(0));
            for (String line : lines) {
                limitations.add(Limitation.valueOf(line));
            }
            problem = new SimplexProblem(costFunction, limitations.toArray(new Limitation[0]));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return problem;
    }

    public static TransportationProblem readTP(String filename) {
        TransportationProblem problem = null;
        try {
            List<String> lines = Files.readAllLines(Paths.get(filename));
            String[] a = lines.remove(0).split(" ");
            List<Fraction> stock = new ArrayList<>();
            for (String s : a) {
                if (!s.isEmpty())
                    stock.add(new Fraction(s));
            }

            String[] b = lines.remove(0).split(" ");
            List<Fraction> required = new ArrayList<>();
            for (String s : b) {
                if (!s.isEmpty())
                    required.add(new Fraction(s));
            }

            Matrix matrix = new Matrix(stock.size(), required.size());
            for (int i = 0; i < matrix.rows(); ++i) {
                String[] values = lines.get(i).split(" ");
                for (int j = 0; j < matrix.columns(); ++j)
                    matrix.set(new Fraction(values[j]), i, j);
            }
            problem = new TransportationProblem(stock, required, matrix);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return problem;
    }
}
