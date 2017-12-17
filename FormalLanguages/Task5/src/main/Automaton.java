/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.util.HashMap;
import java.util.HashSet;

/**
 *
 * @author gc
 */
public class Automaton {

    public static int numBranch = 0;

    private HashSet<String> start;
    private HashSet<String> finish;

    private HashSet<String> alph;

    private HashMap<String, HashMap<String, HashSet<String>>> table;

    public HashSet<String> getStart() {
        return start;
    }

    public void setStart(HashSet<String> start) {
        this.start = start;
    }

    public HashSet<String> getFinish() {
        return finish;
    }

    public void setFinish(HashSet<String> finish) {
        this.finish = finish;
    }

    public HashSet<String> getAlph() {
        return alph;
    }

    public void setAlph(HashSet<String> alph) {
        this.alph = alph;
    }

    public HashMap<String, HashMap<String, HashSet<String>>> getTable() {
        return table;
    }

    public void setTable(HashMap<String, HashMap<String, HashSet<String>>> table) {
        this.table = table;
    }

    public Automaton() {
        this.start = new HashSet<>();
        this.finish = new HashSet<>();
        this.alph = new HashSet<>();
        this.table = new HashMap<>();
    }

    public Automaton(char c) {
        this();
        initByChar(start, finish, alph, table, c);
    }

    public Automaton(String s) {
        this();

        if (s.equals("w")) {
            initByW(start, finish, alph, table);
        }

        if (s.equals("d")) {
            initByD(start, finish, alph, table);
        }
    }

    public Automaton(HashSet<String> start, HashSet<String> finish, HashSet<String> alph,
            HashMap<String, HashMap<String, HashSet<String>>> table) {
        this.start = start;
        this.finish = finish;
        this.alph = alph;
        this.table = table;
    }

    public ParseResult tryParse(String s, int index) {
        ParseResult result = new ParseResult();

        HashSet<String> states = start;

        for (int i = index; i < s.length(); i++) {
            states = move(states, s.charAt(i));

            if (isFinal(states)) {
                result.setFinalState(true);
                result.setCountValid(i - index + 1);
            }

            if (states.isEmpty()) {
                break;
            }
        }

        return result;
    }

    private boolean isFinal(HashSet<String> states) {
        for (String cur : states) {
            if (finish.contains(cur)) {
                return true;
            }
        }

        return false;
    }

    private HashSet<String> move(HashSet<String> states, char c) {
        HashSet<String> temp = new HashSet<>();

        for (String cur : states) {
            String cstr = Character.toString(c);

            if (table.get(cur).containsKey(cstr) && !table.get(cur).get(cstr).isEmpty()) {

                HashSet<String> line = table.get(cur).get(cstr);

                for (String l : line) {
                    if (!temp.contains(l)) {
                        temp.add(l);
                    }
                }
            }
        }

        return temp;
    }

    private void initByChar(HashSet<String> start, HashSet<String> finish, HashSet<String> alph,
            HashMap<String, HashMap<String, HashSet<String>>> table, char c) {
        alph.add(Character.toString(c));
        start.add(Integer.toString(numBranch));

        table.put(Integer.toString(numBranch), new HashMap<>());
        table.put(Integer.toString(numBranch + 1), new HashMap<>());

        table.get(Integer.toString(numBranch)).put(Character.toString(c), new HashSet<>());
        table.get(Integer.toString(numBranch + 1)).put(Character.toString(c), new HashSet<>());
        table.get(Integer.toString(numBranch)).get(Character.toString(c)).add(Integer.toString(++numBranch));

        finish.add(Integer.toString(numBranch));

        numBranch++;
    }

    private void initByW(HashSet<String> start, HashSet<String> finish, HashSet<String> alph,
            HashMap<String, HashMap<String, HashSet<String>>> table) {
        for (int i = (int) ('a'); i <= (int) ('z'); i++) {
            char c = (char) i;
            alph.add(Character.toString(c));
        }

        for (int i = (int) ('A'); i <= (int) ('Z'); i++) {
            char c = (char) i;
            alph.add(Character.toString(c));
        }

        start.add(Integer.toString(numBranch));

        table.put(Integer.toString(numBranch), new HashMap<>());
        table.put(Integer.toString(numBranch + 1), new HashMap<>());

        HashSet<String> temp = new HashSet<>();
        temp.add(Integer.toString(numBranch + 1));

        for (String a : alph) {
            table.get(Integer.toString(numBranch)).put(a, temp);
            table.get(Integer.toString(numBranch + 1)).put(a, new HashSet<>());
        }

        finish.add(Integer.toString(++numBranch));

        numBranch++;
    }

    private void initByD(HashSet<String> start, HashSet<String> finish, HashSet<String> alph,
            HashMap<String, HashMap<String, HashSet<String>>> table) {
        for (int i = 0; i <= 9; i++) {
            alph.add(Integer.toString(i));
        }

        start.add(Integer.toString(numBranch));

        table.put(Integer.toString(numBranch), new HashMap<>());
        table.put(Integer.toString(numBranch + 1), new HashMap<>());

        HashSet<String> temp = new HashSet<>();
        temp.add(Integer.toString(numBranch + 1));

        for (String a : alph) {
            table.get(Integer.toString(numBranch)).put(a, temp);
            table.get(Integer.toString(numBranch + 1)).put(a, new HashSet<>());
        }

        finish.add(Integer.toString(++numBranch));

        numBranch++;
    }
}
