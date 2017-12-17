/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.util.ArrayList;
import java.util.Stack;

/**
 *
 * @author gc
 */
public class Generator {

    private ArrayList<String> description;
    private ArrayList<Token> tokens;
    
    public Generator(ArrayList<String> description) {
        this.description = description;
        this.tokens = new ArrayList<>();
    }

    public ArrayList<Token> getTokens() {
        for (int i = 0; i < description.size(); i++) {
            String[] parts = pickOutParts(description.get(i));
            String reg = processReg(parts[2]);
            Automaton auto = createAutomaton(reg);
            Token token = new Token(auto, parts[0], Integer.parseInt(parts[1]));
            tokens.add(token);
        }

        return tokens;
    }

    private String[] pickOutParts(String line) {
        String[] res = new String[3];

        int id1 = line.indexOf(' ');
        res[0] = line.substring(1, id1);

        int id2 = line.indexOf(' ', id1 + 1);
        res[1] = line.substring(id1 + 1, id2);

        res[2] = "(" + line.substring(id2 + 1, line.length() - 1) + ")";

        return res;
    }

    private String processReg(String reg) {
        StringBuilder res = new StringBuilder();

        for (int i = 0; i < reg.length(); i++) {
            if (reg.charAt(i) == ',' && isPartReg(reg, i - 1)) {
                res.append('|');
                continue;
            }

            if (reg.charAt(i) == '+' && isPartReg(reg, i - 1)) {
                res.append('|');
                continue;
            }

            if (reg.charAt(i) == '('
                    && ((i > 0 && (reg.charAt(i - 1) == ')' && isPartReg(reg, i - 2)))
                    || (i > 0 && (reg.charAt(i - 1) == '*' && reg.charAt(i - 2) == ')' && isPartReg(reg, i - 3))))) {
                res.append('.');
            }

            res.append(reg.charAt(i));

            if (canPointSet(reg, i)) {
                res.append('.');
            }
        }

        return res.toString();
    }

    private Automaton createAutomaton(String reg) {
        Stack<Automaton> operands = new Stack<>();
        Stack<Character> operations = new Stack<>();

        for (int i = 0; i < reg.length(); i++) {
            if (reg.charAt(i) == '\\') {
                if (reg.charAt(i + 1) == 'w' || reg.charAt(i + 1) == 'd') {
                    operands.push(new Automaton(Character.toString(reg.charAt(i + 1))));

                    if (!operations.isEmpty()) {
                        if (operations.peek() == '.') {
                            Automaton b = operands.pop();
                            Automaton a = operands.pop();
                            
                            operands.push(Operator.catenation(a, b));
                            operations.pop();
                        }
                    }

                    i++;
                    continue;
                }

                if (reg.charAt(i + 1) == 'n' || reg.charAt(i + 1) == 't' || reg.charAt(i + 1) == 'r') {
                    char c = ' ';

                    if (reg.charAt(i + 1) == 'n') {
                        c = '\n';
                    }

                    if (reg.charAt(i + 1) == 't') {
                        c = '\t';
                    }

                    if (reg.charAt(i + 1) == 'r') {
                        c = '\r';
                    }

                    operands.push(new Automaton(c));

                    if (!operations.isEmpty()) {
                        if (operations.peek() == '.') {
                            Automaton b = operands.pop();
                            Automaton a = operands.pop();

                            operands.push(Operator.catenation(a, b));
                            operations.pop();
                        }
                    }

                    i++;
                    continue;
                }

                operands.push(new Automaton(reg.charAt(i + 1)));

                if (!operations.isEmpty()) {
                    if (operations.peek() == '.') {
                        Automaton b = operands.pop();
                        Automaton a = operands.pop();

                        operands.push(Operator.catenation(a, b));
                        operations.pop();
                    }
                }

                i++;
                continue;
            }

            if (isLetter(reg.charAt(i)) || isDigit(reg.charAt(i))) {
                operands.push(new Automaton(reg.charAt(i)));

                if (!operations.isEmpty()) {
                    if (operations.peek() == '.') {
                        Automaton b = operands.pop();
                        Automaton a = operands.pop();

                        operands.push(Operator.catenation(a, b));
                        operations.pop();
                    }
                }

                continue;
            }

            if (reg.charAt(i) == '*' && isPartReg(reg, i - 1)) {
                Automaton a = operands.pop();
                operands.push(Operator.iteration(a));
                continue;
            }

            if (reg.charAt(i) == '(' && isPartReg(reg, i - 1)) {
                operations.push(reg.charAt(i));
                continue;
            }

            if (reg.charAt(i) == ')' && isPartReg(reg, i - 1)) {
                operands.push(calcExp(operands, operations));

                if (!operations.isEmpty()) {
                    if (operations.peek() == '.') {
                        Automaton b = operands.pop();
                        Automaton a = operands.pop();
                        
                        operands.push(Operator.catenation(a, b));
                        operations.pop();
                    }
                }
                continue;
            }
            
            if (reg.charAt(i) == '|' || reg.charAt(i) == '.') {
                operations.push(reg.charAt(i));
            }
        }
        
        System.out.println(!operands.isEmpty());
        return operands.pop();
    }

    private boolean isPartReg(String s, int index) {
        if (index < 0) {
            return true;
        }

        int count = 0;

        for (int i = index; i >= 0; i--) {
            if (s.charAt(i) == '\\') {
                count++;
                continue;
            }

            break;
        }

        return count % 2 == 0;
    }

    private boolean canPointSet(String s, int i) {
        if (s.length() <= i + 1) {
            return false;
        }

        if (isSym(s, i) && (isSym(s, i + 1) || (s.charAt(i + 1) == '\\') || s.charAt(i + 1) == '(')) {
            return true;
        }

        if ((s.charAt(i) == '*' || s.charAt(i) == ')') && isPartReg(s, i - 1) && (isSym(s, i + 1) || (s.charAt(i + 1) == '\\'))) {
            return true;
        }

        return false;
    }

    private boolean isSym(String s, int i) {

        return ('0' <= s.charAt(i) && s.charAt(i) <= '9')
                || ('a' <= s.charAt(i) && s.charAt(i) <= 'z')
                || ('A' <= s.charAt(i) && s.charAt(i) <= 'Z')
                || (!isPartReg(s, i - 1));
    }

    private boolean isLetter(char c) {

        return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
    }

    private boolean isDigit(char c) {

        return '0' <= c && c <= '9';
    }

    private Automaton calcExp(Stack<Automaton> operands, Stack<Character> operation) {
        Automaton res = operands.pop();

        while (operation.peek() != '(') {
            if (!operands.isEmpty()) {
                Automaton b = operands.pop();
                res = Operator.association(b, res);
            }

            operation.pop();
        }

        operation.pop();

        return res;
    }
}
