package io.github.fnickru.math.struct;

import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class Solution<Table extends Memento<Table>> {

    private Map<String, Fraction> items;
    private Table table;

    public Solution(Table table) {
        this.table = table;
        items = new LinkedHashMap<>();
    }

    public void addItem(String key, Fraction value) {
        items.put(key, value);
    }

    public String toString() {
        String string = "";

        List<Table> stateList = table.getStateList();
        for (Table table : stateList) {
            string = string.concat(table + "\n");
        }
        string += table;

        for (Map.Entry<String, Fraction> item : items.entrySet())
            string = string.concat("\n" + item.getKey() + " = " + item.getValue());

        return string + "\n";
    }
}
