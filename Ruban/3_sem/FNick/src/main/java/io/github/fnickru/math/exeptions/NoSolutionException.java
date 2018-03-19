package io.github.fnickru.math.exeptions;

public class NoSolutionException extends Exception{

    public NoSolutionException() {
        this("Cost function is not limited");
    }

    public NoSolutionException(String message) {
        super(message);
    }

    public NoSolutionException(String message, Throwable throwable) {
        super(message, throwable);
    }
}
