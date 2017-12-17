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
public class Token implements Comparable<Token> {

    private Automaton auto;
    private String id;
    private int priority;

    public Token(Automaton auto, String id, int priority) {
        this.auto = auto;
        this.id = id;
        this.priority = priority;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public int getPriority() {
        return priority;
    }

    public void setPriority(int priority) {
        this.priority = priority;
    }

    public ParseResult tryParse(String s, int index) {
        return auto.tryParse(s, index);
    }

    @Override
    public int compareTo(Token token) {
        if (priority > token.getPriority()) {
            return -1;
        }

        if (priority < token.getPriority()) {
            return 1;
        }
        
        return 0;
    }
}
