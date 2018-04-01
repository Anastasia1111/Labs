package io.github.fnickru.math.struct.simplex;

import io.github.fnickru.math.struct.Fraction;

import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

class SimplexAnswer {

    private Map<String, Fraction> items;
    private SimplexTable simplexTable;

    SimplexAnswer(SimplexTable simplexTable) {
        this.simplexTable = simplexTable;
        items = new LinkedHashMap<>();
    }

    void addItem(String key, Fraction value) {
        items.put(key, value);
    }

    public String toString() {
        String string = "";

        List<SimplexTable> stateList = simplexTable.getStateList();
        for (SimplexTable table : stateList) {
            string = string.concat(table + "\n");
        }
        string += simplexTable;

        for (Map.Entry<String, Fraction> item : items.entrySet())
            string = string.concat("\n" + item.getKey() + " = " + item.getValue());

        return string + "\n";
    }
}
