/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.util.ArrayList;

/**
 *
 * @author gc
 */
public class NondetAutomaton {

    enum State {
        q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11
    };

    private State[] finalStates = {State.q3, State.q4, State.q5, State.q6, State.q10};

    private boolean isFinal(ArrayList<State> states) {
        for (int i = 0; i < finalStates.length; i++) {
            for (int j = 0; j < states.size(); j++) {
                if (finalStates[i] == states.get(j)) {
                    return true;
                }
            }
        }

        return false;
    }

    private ArrayList<State> move(ArrayList<State> states, char c) {
        ArrayList<State> temp = new ArrayList<>();

        for (State cur : states) {
            if (c == '-' || c == '+') {
                switch (cur) {
                    case q0: {
                        temp.add(State.q1);
                        temp.add(State.q2);
                        break;
                    }
                    case q7: {
                        temp.add(State.q9);
                        break;
                    }
                }
            }

            if (c >= '0' && c <= '9') {
                switch (cur) {
                    case q0:
                    case q2:
                    case q3:
                        temp.add(State.q3);
                        break;
                    case q5:
                    case q6:
                    case q11:
                        temp.add(State.q6);
                        break;
                    case q8:
                    case q9:
                    case q10:
                        temp.add(State.q10);
                        break;
                }
            }
            
            if (c == '.') {
                switch (cur) {
                    case q0:
                    case q1:
                        temp.add(State.q11);
                        break;
                    case q3:
                        temp.add(State.q4);
                        temp.add(State.q5);
                        break;
                }
            }
            
            if (c == 'e' || c == 'E') {
                switch (cur) {
                    case q4:
                    case q6:
                        temp.add(State.q7);
                        temp.add(State.q8);
                        break;
                }
            }
        }
        
        return temp;
    }
    
    public ParseResult tryParse(String s, int index) {
        ParseResult result = new ParseResult();
        System.out.println("test case = " + s);
        
        ArrayList<State> states = new ArrayList<>();
        states.add(State.q0);
        
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
}
