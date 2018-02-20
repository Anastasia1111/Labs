package io.github.fnickru.math.util;

import io.github.fnickru.math.types.Fraction;
import io.github.fnickru.math.types.Matrix;
import io.github.fnickru.math.types.SquareMatrix;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class FileWorker {

    // In development
    /*
    public static void writeFraction(Fraction fraction, String filename)
    {
    }

    public static void writeMatrix(Matrix matrix, String filename)
    {
    }
    */

    public static Fraction[] readAllFraction(String filename) {
        List<Fraction> fractions = new ArrayList<>();

        try {
            List<String> lines = Files.readAllLines(Paths.get(filename));
            for (String line : lines) {
                String[] values = line.split(" ");
                for (String value : values) {
                    fractions.add(new Fraction(value));
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return (Fraction[]) fractions.toArray();
    }

    public static SquareMatrix readSquareMatrix(String filename) {
        try {
            List<String> lines = Files.readAllLines(Paths.get(filename));
            SquareMatrix matrix = new SquareMatrix(lines.size());
            for (int i = 0; i < matrix.size(); ++i) {
                String[] values = lines.get(i).split(" ");
                for (int j = 0; j < matrix.size(); ++j)
                    matrix.set(new Fraction(values[j]), i, j);
            }
            return matrix;
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }
}
