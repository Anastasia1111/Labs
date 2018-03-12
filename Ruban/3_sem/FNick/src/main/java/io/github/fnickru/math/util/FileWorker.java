package io.github.fnickru.math.util;

import io.github.fnickru.math.types.Fraction;
import io.github.fnickru.math.types.Matrix;

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
}
