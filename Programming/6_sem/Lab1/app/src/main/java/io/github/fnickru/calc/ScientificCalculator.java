package io.github.fnickru.calc;

import android.support.v4.math.MathUtils;
import org.apache.commons.lang3.ArrayUtils;

import java.text.NumberFormat;
import java.text.ParseException;
import java.util.Arrays;
import java.util.Locale;
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
     *     <li>sin - синус (аргумент в градусах)</li>
     *     <li>cos - косинус (аргумент в градусах)</li>
     *     <li>log - натуральный логарифм</li>
     *     <li>sqrt - квадратный корень</li>
     * </ul>
     */
    private String[] binaryOperators = new String[]{"+", "-", "*", "/", "%",};
    private String[] operators = ArrayUtils.addAll(binaryOperators, "u-", "sin", "cos", "log", "sqrt");
    private String[] separators = ArrayUtils.addAll(operators, "(", ")");

    private boolean isExpressionCorrect = true;
    private String lastResult = "";
    private String lastError = "";

    private boolean isOperator(String x) {
        return Arrays.asList(operators).contains(x);
    }

    private boolean isBinaryOperator(String x) {
        return Arrays.asList(binaryOperators).contains(x);
    }

    private boolean isUnaryOperator(String x) {
        return isOperator(x) && !isBinaryOperator(x);
    }

    private boolean isOperand(String x) {
        try {
            Double.valueOf(x);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    private boolean isSeparator(String x) {
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

    private String complete(String expression) {
        String extendedExpression = expression;

        if (extendedExpression.endsWith("=")) {
            String subexp = extendedExpression.substring(0, extendedExpression.length() - 1);
            if (isOperand(subexp))
                extendedExpression = extendedExpression.replace("=", lastOperation);
            else {
                String possibleOperator = subexp.substring(subexp.length() - 1);
                String possibleOperand = subexp.substring(0, subexp.length() - 1);
                if (isBinaryOperator(possibleOperator) && isOperand(possibleOperand))
                    extendedExpression = extendedExpression.replace((possibleOperator + "="), (possibleOperator + possibleOperand));
                else
                    extendedExpression = subexp;
            }
        }

        return extendedExpression;
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
                isExpressionCorrect = false;
                lastError = "#WRONGEXP"; // Некорректное выражение
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
                                isExpressionCorrect = false;
                                lastError = "#BRACERR"; // Скобки не согласованы
                                return postfix;
                            }
                        }
                        stack.pop();
                        break;
                    default: // Операторы
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
                isExpressionCorrect = false;
                lastError = "#BRACERR"; // Скобки не согласованы
                return postfix;
            }
        }

        return postfix.trim();
    }

    private String postfixCalc(String expression)
    {
        String[] tokens = expression.split(" ");
        Stack<String> stack = new Stack<>();
        Double res, arg1, arg2;

        try {
            for (String token : tokens) {
                switch (token) {
                    case "+":
                        arg1 = Double.valueOf(stack.pop());
                        arg2 = Double.valueOf(stack.pop());
                        res = arg2 + arg1;
                        lastOperation = "+" + arg1;
                        stack.push(String.format(Locale.getDefault(), "%.12f", res).replace(",", "."));
                        break;
                    case "-":
                        arg1 = Double.valueOf(stack.pop());
                        arg2 = Double.valueOf(stack.pop());
                        res = arg2 - arg1;
                        lastOperation = "-" + arg1;
                        stack.push(String.format(Locale.getDefault(), "%.12f", res).replace(",", "."));
                        break;
                    case "*":
                        arg1 = Double.valueOf(stack.pop());
                        arg2 = Double.valueOf(stack.pop());
                        res = arg2 * arg1;
                        lastOperation = "*" + arg1;
                        stack.push(String.format(Locale.getDefault(), "%.12f", res).replace(",", "."));
                        break;
                    case "/":
                        arg1 = Double.valueOf(stack.pop());
                        arg2 = Double.valueOf(stack.pop());
                        res = arg2 / arg1;
                        lastOperation = "/" + arg1;
                        if (res.isNaN() || res.isInfinite())
                            throw new ArithmeticException("Division by zero");
                        stack.push(String.format(Locale.getDefault(), "%.12f", res).replace(",", "."));
                        break;
                    case "%":
                        arg1 = Double.valueOf(stack.pop());
                        arg2 = Double.valueOf(stack.pop());
                        res = arg2 % arg1;
                        lastOperation = "%" + arg1;
                        if (res.isNaN() || res.isInfinite())
                            throw new ArithmeticException("Division by zero");
                        stack.push(String.format(Locale.getDefault(), "%.12f", res).replace(",", "."));
                        break;
                    case "u-":
                        arg1 = Double.valueOf(stack.pop());
                        res = -arg1;
                        stack.push(String.format(Locale.getDefault(), "%.12f", res).replace(",", "."));
                        break;
                    case "sin":
                        arg1 = Double.valueOf(stack.pop());
                        res = Math.sin(Math.toRadians(arg1));
                        stack.push(String.format(Locale.getDefault(), "%.12f", res).replace(",", "."));
                        break;
                    case "cos":
                        arg1 = Double.valueOf(stack.pop());
                        res = Math.cos(Math.toRadians(arg1));
                        stack.push(String.format(Locale.getDefault(), "%.12f", res).replace(",", "."));
                        break;
                    case "log":
                        arg1 = Double.valueOf(stack.pop());
                        res = Math.log(arg1);
                        stack.push(String.format(Locale.getDefault(), "%.12f", res).replace(",", "."));
                        break;
                    case "sqrt":
                        arg1 = Double.valueOf(stack.pop());
                        res = Math.sqrt(arg1);
                        stack.push(String.format(Locale.getDefault(), "%.12f", res).replace(",", "."));
                        break;
                    default: // Операнды
                        stack.push(token);
                }
            }
        } catch (NumberFormatException e) {
            isExpressionCorrect = false;
            String wrongArgument = e.getMessage().substring(e.getMessage().indexOf("\"")).replace("\"", "");
            lastError = String.format("#NaN (%s)", wrongArgument);
            return "";
        } catch (ArithmeticException e) {
            isExpressionCorrect = false;
            lastError = "#ZERODIV";
            return "";
        }
        try {
            res = Double.valueOf(stack.pop());
            return String.format(Locale.getDefault(), "%.8f", res).replace(",", ".");
        } catch (NumberFormatException e) {
            isExpressionCorrect = false;
            lastError = "#EMPTY";
            return "";
        }
    }

    @Override
    public boolean calculate(String expression) {
        String infix = complete(expression);

        isExpressionCorrect = true;
        lastOperation = "";
        lastResult = "";
        lastError = "";

        String postfix = infix2postfix(infix);
        if (isExpressionCorrect)
            lastResult = postfixCalc(postfix);
        return isExpressionCorrect;
    }

    @Override
    public String errorMessage() {
        return isExpressionCorrect ? "" : lastError;
    }

    @Override
    public String result() {
        return isExpressionCorrect ? lastResult : lastError;
    }

    /**
     * Функция для тестирования работоспособности. Будет удалена после окончания работы над классом
     */
    public static void main(String[] args) {
        ScientificCalculator calc = ScientificCalculator.INSTANCE;

        calc.calculate("");
        System.out.println(calc.result()); // #EMPTY
        calc.calculate("50");
        System.out.println(calc.result()); // 50
        calc.calculate(calc.result() + "=");
        System.out.println(calc.result()); // 50
        calc.calculate("2+");
        System.out.println(calc.result()); // #WRONGEXP
        calc.calculate("4+=");
        System.out.println(calc.result()); // 8
        calc.calculate("7=");
        System.out.println(calc.result()); // 11
        calc.calculate("92/10=");
        System.out.println(calc.result()); // 9.2
        calc.calculate(calc.result() + "=");
        System.out.println(calc.result()); // 0.92
        calc.calculate("2+2-2*2/2");
        System.out.println(calc.result()); // 2
        calc.calculate(calc.result() + "=");
        System.out.println(calc.result()); // 0
        calc.calculate("15 * -((3) - (4))=");
        System.out.println(calc.result()); // 15
        calc.calculate(calc.result() + "=");
        System.out.println(calc.result()); // 15
        calc.calculate("(25+sqrt(4)*5)/10--5%cos(45+90/2)=");
        System.out.println(calc.result()); // #ZERODIV
    }
}
