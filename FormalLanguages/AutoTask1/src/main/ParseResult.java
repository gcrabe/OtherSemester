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
public class ParseResult {
    
    private boolean finalState;
    private int countValid;

    public ParseResult() {
        this.finalState = false;
        this.countValid = 0;
    }
    
    public boolean getFinalState() {
        return finalState;
    }
    
    public void setFinalState(boolean finalState) {
        this.finalState = finalState;
    }
    
    public int getCountValid() {
        return countValid;
    }
    
    public void setCountValid(int countValid) {
        this.countValid = countValid;
    }
    
    public void print() {
        System.out.println("Output: " + getFinalState() + ", m = " + getCountValid() + "\r\n");
    }
}
