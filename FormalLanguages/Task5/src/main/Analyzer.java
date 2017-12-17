/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;

/**
 *
 * @author user
 */
public class Analyzer {

    private String input;
    private StringBuilder output;

    private ArrayList<Token> tokens;
    private ArrayList<ParseResult> parseResultList;

    public Analyzer(ArrayList<Token> tokens, String input) {
        this.tokens = tokens;
        this.input = input;
        this.output = new StringBuilder();
        parseResultList = new ArrayList<>();
    }

    public String work() throws FileNotFoundException {
        Collections.sort(tokens);
        
        int i = 0;
        while (i < input.length()) {
            parseResultList = defineToken(input, i);
            int numToken = findNumToken();

            if (numToken == -1) {
                output.append("Не достигнут конец строки\n");
                break;
            }
            
            parseResultList.get(numToken).print();
            
            i += parseResultList.get(numToken).getCountValid(); 
        }

        return output.toString();
    }
    
    private ArrayList<ParseResult> defineToken(String s, int index) {
        ArrayList<ParseResult> result = new ArrayList<>();
        
        for (int j = 0; j < tokens.size(); j++) {
            ParseResult temp = tokens.get(j).tryParse(s, index);
            
            if (temp.getFinalState()) {
                temp.setTokenName(tokens.get(j).getId());
                temp.setToken(s.substring(index, index + temp.getCountValid()));
                temp.setPriority(tokens.get(j).getPriority());
            }
            
            result.add(temp);
        } 
        
        return result;
    }

    private int findNumToken() {
        int maxima = Integer.MIN_VALUE;
        int index = -1;

        for (int i = 0; i < parseResultList.size(); i++) {
            int curElement = parseResultList.get(i).getCountValid();
            
            if (curElement > 0 && curElement > maxima) {
                maxima = parseResultList.get(i).getCountValid();
                index = i;
            }
        }

        return index;
    }
}
