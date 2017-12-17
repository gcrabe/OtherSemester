/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

/**
 *
 * @author user
 */
public class OperationAutomaton {

    private final static String TOKEN_NAME = "Operation";
    public final static int priority = 10;
    
    enum State {
        q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, qx
    };

    private State[] finalStates = {
        State.q1, State.q2, State.q3, State.q4,
        State.q9, State.q10, State.q12
    };

    private boolean isFinal(State state) {
        for (int i = 0; i < finalStates.length; i++) {
            if (finalStates[i] == state) {
                return true;
            }
        }

        return false;
    }

    private State move(State state, char c) {
        if (c == '+') {
            switch (state) {
                case q0:
                    return State.q1;
                default:
                    return State.qx;
            }
        }
        
        if (c == '-') {
            switch (state) {
                case q0:
                    return State.q2;
                default:
                    return State.qx;
            }
        }
        
        if (c == '*') {
            switch (state) {
                case q0:
                    return State.q3;
                default:
                    return State.qx;
            }
        }
        
        if (c == '/') {
            switch (state) {
                case q0:
                    return State.q4;
                default:
                    return State.qx;
            }
        }
        
        if (c == 'a') {
            switch (state) {
                case q0:
                    return State.q5;
                default:
                    return State.qx;
            }
        }
        
        if (c == 'o') {
            switch (state) {
                case q0:
                    return State.q6;
                case q7:
                    return State.q11;
                default:
                    return State.qx;
            }
        }
        
        if (c == 'n') {
            switch (state) {
                case q0:
                    return State.q7;
                case q3:
                    return State.q8;
                default:
                    return State.qx;
            }
        }
        
        if (c == 'd') {
            switch (state) {
                case q8:
                    return State.q9;
                default:
                    return State.qx;
            }
        }
        
        if (c == 'r') {
            switch (state) {
                case q6:
                    return State.q10;
                default:
                    return State.qx;
            }
        }
        
        if (c == 't') {
            switch (state) {
                case q11:
                    return State.q12;
                default:
                    return State.qx;
            }
        }
        
        return State.qx;
    }

    public ParseResult tryParse(String s, int index) {
        ParseResult result = new ParseResult();

        State state = State.q0;

//        System.out.println("test case = \"" + s + "\"");

        for (int i = index; i < s.length(); i++) {
            state = move(state, s.charAt(i));

            if (isFinal(state)) {
                result.setFinalState(true);
                result.setCountValid(i - index + 1);
            }

            if (state == State.qx) {
                break;
            }
        }

        result.setTokenName(TOKEN_NAME);
        result.setPriority(priority);

        return result;
    }
}
