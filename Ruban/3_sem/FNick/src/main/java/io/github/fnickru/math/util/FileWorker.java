package io.github.fnickru.math.util;

import io.github.fnickru.math.struct.*;

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

    public static Simplex readSimplex(String filename) {
        Simplex simplex = null;
        try {
            List<String> lines = Files.readAllLines(Paths.get(filename));
            List<Limitation> limitations = new ArrayList<>();
            CostFunction costFunction = CostFunction.valueOf(lines.remove(0));
            for (String line : lines) {
                limitations.add(Limitation.valueOf(line));
            }
            simplex = new Simplex(costFunction, limitations.toArray(new Limitation[0]));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return simplex;
    }
}
