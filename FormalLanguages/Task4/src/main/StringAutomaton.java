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
public class StringAutomaton {
    
    private final static String TOKEN_NAME = "String";
    public final static int priority = 2;
    
    enum State {
        q0, q1, q2, q3, qx
    };
    
    private State[] finalStates = {State.q3};
    
    private boolean isFinal(State state) {
        for (int i = 0; i < finalStates.length; i++) {
            if (finalStates[i] == state) {
                return true;
            }
        }
        
        return false;
    }
    
    private boolean isCorrectSymbol(char c) {
        return Character.isDefined(c);
    }
    
    private State move(State state, char c) {
        if (c == '{') {
            switch (state) {
                case q0:
                    return State.q1;
                default:
                    return State.qx;
            }
        }
        
        if (c == '}') {
            switch (state) {
                case q1:
                case q2:
                    return State.q3;
                default:
                    return State.qx;
            }
        }
        
        if (isCorrectSymbol(c)) {
            switch (state) {
                case q1:
                case q2:
                    return State.q2;
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
