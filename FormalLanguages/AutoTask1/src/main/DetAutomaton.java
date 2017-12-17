/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

/**
 *
 * @author gc
 */
public class DetAutomaton {

    enum State {
        START, SIGN, DIGIT, INCORRECT
    };

    private State[] finalStates = {State.DIGIT};

    private boolean isFinal(State state) {
        for (int i = 0; i < finalStates.length; i++) {
            if (finalStates[i] == state) {
                return true;
            }
        }
        
        return false;
    }

    private State move(State state, char c) {
        if (c == '+' || c == '-') {
            switch (state) {
                case START:
                    return State.SIGN;
                default:
                    return State.INCORRECT;
            }
        }

        if (c >= '0' && c <= '9') {
            switch (state) {
                case START:
                case SIGN:
                case DIGIT:
                    return State.DIGIT;
                default:
                    return State.INCORRECT;
            }
        }

        return State.INCORRECT;
    }

    public ParseResult tryParse(String s, int index) {
        ParseResult result = new ParseResult();
        
        State state = State.START;

        System.out.println("test case = \"" + s + "\"");

        for (int i = index; i < s.length(); i++) {
            state = move(state, s.charAt(i));

            if (isFinal(state)) {
                result.setFinalState(true);
                result.setCountValid(i - index + 1);
            }

            if (state == State.INCORRECT) {
                break;
            }
        }
        
        return result;
    }
}
