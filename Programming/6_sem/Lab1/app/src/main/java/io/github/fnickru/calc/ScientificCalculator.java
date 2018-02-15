package io.github.fnickru.calc;

/**
 * Инженерный калькулятор в виде неленивого сингтона
 */
public enum ScientificCalculator implements Calculator {

    INSTANCE;

    /**
     * Последняя левоассоциативная операция операция, выполненная калькулятором.
     * <b>Пример:</> для выражения "2+3*7" последней операцией будет "+21".
     */
    private String lastOperation = "";

    /**
     * Список операций, поддерживаемых калькулятором:
     * <ul>
     *     <li>+ - сложение</li>
     *     <li>- - вычитание</li>
     *     <li>* - умножение</li>
     *     <li>/ - деление</li>
     *     <li>% - остаток от деления</li>
     *     <li>u - унарный минус</>
     *     <li>s - синус</li>
     *     <li>c - косинус</li>
     *     <li>l - двоичный логарифм</li>
     *     <li>q - квадратный корень</li>
     * </ul>
     */
    private String operators = "+-*/%usclq";

    private String delimiters = operators + "( )";
    private boolean isExpressionCorrect = true;
    private String lastResult = "";
    private String lastError = "";

    private boolean isOperator(String x){
        if(x.length() != 1) return false;
        return operators.contains(x);
    }

    private boolean isDelimiter(String x){
        if(x.length() != 1) return false;
        return delimiters.contains(x);
    }

    private String infix2postfix(String infix) {
        String postfix = "";



        return postfix;
    }

    @Override
    public boolean calculate(String expression) {
        String postfix = infix2postfix(expression);
        return isExpressionCorrect;
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
