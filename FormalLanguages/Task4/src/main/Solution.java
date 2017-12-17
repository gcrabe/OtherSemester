/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.io.FileNotFoundException;
import java.io.PrintWriter;

/**
 *
 * @author user
 */
public class Solution {
    
    public static void main(String[] args) throws FileNotFoundException {
        
        EmptyOperatorAutomaton emptyOperatorAuto = new EmptyOperatorAutomaton();
        OperationAutomaton operationAutomaton = new OperationAutomaton();
        IdAutomaton idAuto = new IdAutomaton();
        SetOperatorAutomaton setOperatorAutomaton = new SetOperatorAutomaton();
        
        IntegerAutomaton integerAuto = new IntegerAutomaton();
        RealAutomaton realAutomaton = new RealAutomaton();
        
        LeftBracketAutomaton leftBracketAutomaton = new LeftBracketAutomaton();
        RightBracketAutomaton rightBracketAutomaton = new RightBracketAutomaton();
        
        StringAutomaton stringAutomaton = new StringAutomaton();
        WhiteSpaceAutomaton whiteSpaceAutomaton = new WhiteSpaceAutomaton();
        CommentAutomaton commentAuto = new CommentAutomaton();
        
        KeyWordAutomaton keyWordAutomaton = new KeyWordAutomaton();
        
        int MAXN = 12;
        ParseResult[] res = new ParseResult[MAXN];
        
        String test = "if (x := 7.3) then begin1 := 7;";
        int position = 0;
        
        while (true) {
            res[0] = commentAuto.tryParse(test, position);
            res[1] = emptyOperatorAuto.tryParse(test, position);
            res[2] = idAuto.tryParse(test, position);
            res[3] = integerAuto.tryParse(test, position);
            res[4] = leftBracketAutomaton.tryParse(test, position);
            res[5] = operationAutomaton.tryParse(test, position);
            res[6] = setOperatorAutomaton.tryParse(test, position);
            res[7] = realAutomaton.tryParse(test, position);
            res[8] = rightBracketAutomaton.tryParse(test, position);
            res[9] = stringAutomaton.tryParse(test, position);
            res[10] = whiteSpaceAutomaton.tryParse(test, position);
            res[11] = keyWordAutomaton.tryParse(test, position);
            
            for (int i = 0; i < MAXN; i++) {
                String token = test.substring(position, position + res[i].getCountValid());
                res[i].setToken(token);
            }
           
            ParseResult temp = res[0];
            
            for (int i = 0; i < MAXN; i++) {
                if (res[i].getFinalState()) {
                    if (res[i].getCountValid() > temp.getCountValid() 
                            || (res[i].getCountValid() == temp.getCountValid() 
                            && res[i].getPriority() > temp.getPriority()))
                        temp = res[i];
                }
            }
            
            position += temp.getCountValid();
            temp.print();
            
            if (position == test.length() || !temp.getFinalState()) {
                break;
            }
        }
    }
}
