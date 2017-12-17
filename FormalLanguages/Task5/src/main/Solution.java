/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author gc
 */
public class Solution {

    public static void main(String[] args) throws FileNotFoundException {

        Scanner reader = new Scanner(new File("E:/FormalLanguages/Task5/src/main/regs.txt"));
        ArrayList<String> input = new ArrayList<>();

        while (reader.hasNextLine()) {
            input.add(reader.nextLine());
        }
        
        reader.close();

        Generator generator = new Generator(input);
        ArrayList<Token> list = generator.getTokens();

        reader = new Scanner(new File("E:/FormalLanguages/Task5/src/main/input.txt"));
        StringBuilder line = new StringBuilder();
        
        while (reader.hasNextLine()) {
            line.append(reader.nextLine());
            line.append("\n");
        }
        
        reader.close();

        Analyzer analyzer = new Analyzer(list, line.toString());
        String result = analyzer.work();
        
        System.out.println(result);
    }
}
