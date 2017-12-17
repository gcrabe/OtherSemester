/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.io.FileNotFoundException;
import java.io.PrintStream;

/**
 *
 * @author user
 */
public class ParseResult {
    
    private boolean finalState;
    private int countValid;
    private String tokenName;
    private int priority;
    private String token;

    public ParseResult() {
        this.finalState = false;
        this.countValid = 0;
        this.tokenName = "empty";
        this.token = "";
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
    
    public String getTokenName() {
        return tokenName;
    }
    
    public void setTokenName(String tokenName) {
        this.tokenName = tokenName;
    }
    
    public int getPriority() {
        return priority;
    }
    
    public void setPriority(int priority) {
        this.priority = priority;
    }
    
    public String getToken() {
        return token;
    }
    
    public void setToken(String token) {
        this.token = token;
    }
        
    public void print() throws FileNotFoundException {
        PrintStream writer = System.out;
        
        writer.print("Token: \"" + getToken() + "\" -> ");
        writer.println(getTokenName() + ", " + getFinalState() + ", m = " + getCountValid());
    }
}
