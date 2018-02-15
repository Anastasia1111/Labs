package io.github.fnickru.calc;

/** Инженерный калькулятор в виде неленивого сингтона
 */
public enum ScientificCalculator implements Calculator {

    INSTANCE;

    boolean isExpressionCorrect = true;
    String lastResult = "";
    String lastError = "";

    @Override
    public boolean calculate(String expression) {
        return false;
    }

    @Override
    public String errorMessage() {
        return isExpressionCorrect ? "" : lastError;
    }

    @Override
    public String result() {
        return lastResult;
    }
}
