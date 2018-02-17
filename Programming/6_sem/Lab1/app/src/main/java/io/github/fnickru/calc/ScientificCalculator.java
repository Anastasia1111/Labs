package io.github.fnickru.calc;

import org.apache.commons.lang3.ArrayUtils;

import java.util.Arrays;
import java.util.Stack;

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
     *     <li>u- - унарный минус</>
     *     <li>sin - синус</li>
     *     <li>cos - косинус</li>
     *     <li>log - двоичный логарифм</li>
     *     <li>sqrt - квадратный корень</li>
     * </ul>
     */
    private String[] operators = new String[]{
            "+",
            "-",
            "*",
            "/",
            "%",
            "u-",
            "sin",
            "cos",
            "log",
            "sqrt"
    };

    private String[] separators = ArrayUtils.addAll(operators,"(", ")");
    private boolean isExpressionCorrect = true;
    private String lastResult = "";
    private String lastError = "";

    private boolean isOperator(String x){
        return Arrays.asList(operators).contains(x);
    }

    private boolean isSeparator(String x){
        return Arrays.asList(separators).contains(x);
    }

    private int priority(String x) {
        switch (x) {
            case "(":
                return 1;
            case "+":
            case "-":
                return 2;
            case "*":
            case "/":
            case "%":
                return 3;
            default:
                return 4; // Унарные операции
        }
    }

    private String infix2postfix(String infix) {
        String postfix = "";
        Stack<String> stack = new Stack<>();

        infix = infix.replaceAll("\\s", "");
        for (String separator : separators) {
            infix = infix.replace(separator, "~" + separator + "~");
        }
        infix = infix.replace("~~", "~");
        String[] tokens = infix.split("~");

        String prev = "", curr;
        for (int i = 0; i < tokens.length; ++i)
        {
            curr = tokens[i];
            if (i == (tokens.length - 1) && isOperator(curr)) {
                postfix = ("#ERR1"); // Некорректное выражение
                isExpressionCorrect = false;
                return postfix;
            }
            if (isSeparator(curr)) {
                switch (curr) {
                    case "(":
                        stack.push(curr);
                        break;
                    case ")":
                        while (!stack.peek().equals("(")) {
                            postfix = postfix.concat(stack.pop() + " ");
                            if (stack.isEmpty()) {
                                postfix = ("#ERR2"); // Скобки не согласованы
                                isExpressionCorrect = false;
                                return postfix;
                            }
                        }
                        stack.pop();
                        break;
                    default:
                        if (curr.equals("-") && (prev.equals("") || (isSeparator(prev)  && !prev.equals(")")))) {
                            curr = "u-";
                        } else {
                            while (!stack.isEmpty() && (priority(curr) <= priority(stack.peek()))) {
                                postfix = postfix.concat(stack.pop() + " ");
                            }
                        }
                        stack.push(curr);
                }
            } else {
                postfix = postfix.concat(curr + " ");
            }
            prev = curr;
        }
        while (!stack.isEmpty()) {
            if (isOperator(stack.peek()))
                postfix = postfix.concat(stack.pop() + " ");
            else {
                postfix = "#ERR2"; // Скобки не согласованы
                isExpressionCorrect = false;
                return postfix;
            }
        }

        return postfix.trim();
    }

    @Override
    public boolean calculate(String expression) {
        //String postfix = infix2postfix(expression);
        lastResult = infix2postfix(expression);
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

    /**
     * Функция для тестирования работоспособности. Будет удалена после окончания работы над классом
     */
    public static void main(String[] args) {
        ScientificCalculator calc = ScientificCalculator.INSTANCE;

        calc.calculate("92/10");
        System.out.println(calc.result());
        calc.calculate("2+2-2*2/2");
        System.out.println(calc.result());
        calc.calculate("1 5 * -((3) - (4))");
        System.out.println(calc.result());
        calc.calculate("(25+sqrt(4)*5)/10--5%sin(45+90/2)");
        System.out.println(calc.result());
    }
}
