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
public class KeyWordAutomaton {

    private final static String TOKEN_NAME = "KeyWord";
    private final static int priority = 12;

    enum State {
        qs,
        q0, q1, q2, q3, q4, q5, q6,
        q7, q8, q9, q10,
        q11, q12, q13, q14, q15,
        q16, q17, q18, q19, q20, q21, q22,
        q23, q24, q25, q26, q27, q28, q29, q30,
        q31, q32, q33,
        q34, q35, q36, q37, q38, 
        q39, q40, q41, q42, q43,
        q44, q45, q46, q47,
        q48, q49, q50,
        q51, q52, q53,
        q54, q55, q56, q57, q58, q59, 
        q60, q61, q62, q63
    };

    private State[] finalStates = {
        State.q6, State.q10, State.q15, State.q22, State.q30,
        State.q33, State.q38, State.q43, State.q47, State.q50,
        State.q53, State.q59, State.q63
    };

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

        for (State state : states) {
            if (c == 'a') {
                switch (state) {
                    case q4:
                        temp.add(State.q5);
                        break;
                    case q8:
                        temp.add(State.q9);
                        break;
                    case q13:
                        temp.add(State.q14);
                        break;
                    case q28:
                        temp.add(State.q29);
                        break;
                }
            }

            if (c == 'b') {
                switch (state) {
                    case qs:
                        temp.add(State.q23);
                        temp.add(State.q54);
                        break;
                    case q23:
                        temp.add(State.q24);
                        break;
                    case q54:
                        temp.add(State.q55);
                        break;
                }
            }

            if (c == 'd') {
                switch (state) {
                    case qs:
                        temp.add(State.q51);
                        break;
                    case q51:
                        temp.add(State.q52);
                        break;
                    case q62:
                        temp.add(State.q63);
                        break;
                }
            }

            if (c == 'e') {
                switch (state) {
                    case qs:
                        temp.add(State.q39);
                        temp.add(State.q60);
                        break;
                    case q12:
                        temp.add(State.q13);
                        break;
                    case q27:
                        temp.add(State.q28);
                        break;
                    case q36:
                        temp.add(State.q37);
                        break;
                    case q39:
                        temp.add(State.q40);
                        break;
                    case q42:
                        temp.add(State.q43);
                        break;
                    case q55:
                        temp.add(State.q56);
                        break;
                    case q60:
                        temp.add(State.q61);
                        break;
                }
            }

            if (c == 'f') {
                switch (state) {
                    case qs:
                        temp.add(State.q44);
                        break;
                    case q32:
                        temp.add(State.q33);
                        break;
                    case q44:
                        temp.add(State.q45);
                        break;
                }
            }

            if (c == 'g') {
                switch (state) {
                    case q3:
                        temp.add(State.q4);
                        break;
                    case q21:
                        temp.add(State.q22);
                        break;
                    case q56:
                        temp.add(State.q57);
                        break;
                }
            }

            if (c == 'h') {
                switch (state) {
                    case q35:
                        temp.add(State.q36);
                        break;
                }
            }

            if (c == 'i') {
                switch (state) {
                    case qs:
                        temp.add(State.q31);
                        break;
                    case q19:
                        temp.add(State.q20);
                        break;
                    case q31:
                        temp.add(State.q32);
                        break;
                    case q57:
                        temp.add(State.q58);
                        break;
                }
            }

            if (c == 'l') {
                switch (state) {
                    case q14:
                        temp.add(State.q15);
                        break;
                    case q26:
                        temp.add(State.q27);
                        break;
                    case q40:
                        temp.add(State.q41);
                        break;
                }
            }

            if (c == 'm') {
                switch (state) {
                    case q5:
                        temp.add(State.q6);
                        break;
                }
            }

            if (c == 'n') {
                switch (state) {
                    case q20:
                        temp.add(State.q21);
                        break;
                    case q29:
                        temp.add(State.q30);
                        break;
                    case q37:
                        temp.add(State.q38);
                        break;
                    case q58:
                        temp.add(State.q59);
                        break;
                    case q61:
                        temp.add(State.q62);
                        break;
                }
            }

            if (c == 'o') {
                switch (state) {
                    case q2:
                        temp.add(State.q3);
                        break;
                    case q24:
                        temp.add(State.q25);
                        break;
                    case q25:
                        temp.add(State.q26);
                        break;
                    case q45:
                        temp.add(State.q46);
                        break;
                    case q49:
                        temp.add(State.q50);
                        break;
                    case q52:
                        temp.add(State.q53);
                        break;
                }
            }

            if (c == 'p') {
                switch (state) {
                    case qs:
                        temp.add(State.q0);
                        break;
                    case q0:
                        temp.add(State.q1);
                        break;
                }
            }

            if (c == 'r') {
                switch (state) {
                    case qs:
                        temp.add(State.q11);
                        break;
                    case q1:
                        temp.add(State.q2);
                        break;
                    case q4:
                        temp.add(State.q5);
                        break;
                    case q9:
                        temp.add(State.q10);
                        break;
                    case q11:
                        temp.add(State.q12);
                        break;
                    case q18:
                        temp.add(State.q19);
                        break;
                    case q46:
                        temp.add(State.q47);
                        break;
                }
            }

            if (c == 's') {
                switch (state) {
                    case qs:
                        temp.add(State.q16);
                        break;
                    case q16:
                        temp.add(State.q17);
                        break;
                    case q41:
                        temp.add(State.q42);
                        break;
                }
            }

            if (c == 't') {
                switch (state) {
                    case qs:
                        temp.add(State.q34);
                        temp.add(State.q48);
                        break;
                    case q17:
                        temp.add(State.q18);
                        break;
                    case q34:
                        temp.add(State.q35);
                        break;
                    case q48:
                        temp.add(State.q49);
                        break;
                }
            }

            if (c == 'v') {
                switch (state) {
                    case qs:
                        temp.add(State.q7);
                        break;
                    case q7:
                        temp.add(State.q8);
                        break;
                }
            }
        }
        
        return temp;
    }

    public ParseResult tryParse(String s, int index) {
        ParseResult result = new ParseResult();
//        System.out.println("test case = " + s);
        
        ArrayList<State> states = new ArrayList<>();
        states.add(State.qs);
        
        boolean start = true;
        
        for (int i = index; i < s.length(); ) {
            states = move(states, s.charAt(i));
            
            if (start) {
                start = false;
                continue;
            }
            
            if (isFinal(states)) {
                result.setFinalState(true);
                result.setCountValid(i - index + 1);
            }
            
            if (states.isEmpty()) {
                break;
            }
            
            i++;
        }
        
        result.setTokenName(TOKEN_NAME);
        result.setPriority(priority);
        
        return result;
    }
}
