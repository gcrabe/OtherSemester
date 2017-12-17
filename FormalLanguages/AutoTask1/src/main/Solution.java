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
public class Solution {

    public static void main(String[] args) {
        String[] tests = { "10", "050", "+1000", "-+100", "050+123", "-", "", 
            "4.2", "-.5", "-5.", "5.", ".5",
            ".5e6", "5.e6", "5.e+6", "+5.e6", "+.5e6", "+.5e+6", "+5.e+6",
            "+5.1e+56", ".", "+.", "+.e6", "-.e+", "-.e+6", "-e+6", ".e6", 
            ".e+5", "+.e+6", "+e6", "e6"};
        
        NondetAutomaton automaton = new NondetAutomaton();
        
        for (int i = 0; i < tests.length; i++) {
            ParseResult result =  automaton.tryParse(tests[i], 0);
            result.print();
        }
    }
}
