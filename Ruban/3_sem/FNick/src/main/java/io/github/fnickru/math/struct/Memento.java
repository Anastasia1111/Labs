package io.github.fnickru.math.struct;

import java.util.List;

/**
 * Класс, который "помнит" свои предыдущие состояния в виде объектов класса T
 */
public interface Memento<T> {

    List<T> getStateList();

}
