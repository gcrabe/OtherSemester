/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.util.HashMap;
import java.util.HashSet;

/**
 *
 * @author user
 */
public class Operator {

    public static Automaton association(Automaton a, Automaton b) {
        HashSet<String> alph = a.getAlph();
        alph.addAll(b.getAlph());
        
        HashSet<String> start = a.getStart();
        start.addAll(b.getStart());
        
        HashMap<String, HashMap<String, HashSet<String>>> table = makeTableForAssociation(a, b, alph);
        
        HashSet<String> finish = a.getFinish();
        finish.addAll(b.getFinish());
        
        return new Automaton(start, finish, alph, table);
    }

    public static Automaton catenation(Automaton a, Automaton b) {
        HashSet<String> alph = a.getAlph();
        alph.addAll(b.getAlph());
        
        HashSet<String> start = a.getStart();
        
        HashMap<String, HashMap<String, HashSet<String>>> table = makeTableForCatenation(a, b, alph);
        
        HashSet<String> finish = b.getFinish();
        finish.addAll(addFinish(a.getFinish(), b.getStart(), b.getFinish()));
        
        return new Automaton(start, finish, alph, table);
    }

    public static Automaton iteration(Automaton a) {
        HashSet<String> alph = a.getAlph();
        
        HashSet<String> start = a.getStart();
        
        HashMap<String, HashMap<String, HashSet<String>>> table = makeTableForIteration(a);
        
        HashSet<String> finish = a.getFinish();
        
        start.add(Integer.toString(Automaton.numBranch));
        finish.add(Integer.toString(Automaton.numBranch));
        Automaton.numBranch++;

        return new Automaton(start, finish, alph, table);
    }

    private static HashMap<String, HashMap<String, HashSet<String>>> makeTableForAssociation(
            Automaton a, Automaton b, HashSet<String> alph) {
        HashMap<String, HashMap<String, HashSet<String>>> c = new HashMap<>(a.getTable().size() + b.getTable().size());
        
        for (String i : a.getTable().keySet()) {
            HashMap<String, HashSet<String>> temp = new HashMap<>();
            
            for (String j : alph) {
                temp.put(j, new HashSet<>());
            }
            
            c.put(i, temp);
        }

        for (String i : b.getTable().keySet()) {
            if (!c.containsKey(i)) {
                HashMap<String, HashSet<String>> temp = new HashMap<>();
                
                for (String j  : alph) {
                    temp.put(j, new HashSet<>());
                }
                
                c.put(i, temp);
            }
        }
        
        for (String i : a.getTable().keySet()) {
            for (String j : a.getTable().get(i).keySet()) {
                HashSet<String> temp = c.get(i).get(j);
                temp.addAll(a.getTable().get(i).get(j));
                
                c.get(i).put(j, temp);
            }
        }
        
        for (String i : b.getTable().keySet()) {
            for (String j : b.getTable().get(i).keySet()) {
                HashSet<String> temp = c.get(i).get(j);
                temp.addAll(b.getTable().get(i).get(j));
                
                c.get(i).put(j, temp);
            }
        }
        
        return c;
    }
    
    private static HashMap<String, HashMap<String, HashSet<String>>> makeTableForCatenation(
            Automaton a, Automaton b, HashSet<String> alph) {
        HashMap<String, HashMap<String, HashSet<String>>> c = new HashMap<>(a.getTable().size() + b.getTable().size());

        for (String i : a.getTable().keySet()) {
            HashMap<String, HashSet<String>> temp = new HashMap<>();

            for (String j : alph) {
                temp.put(j, new HashSet<>());
            }

            c.put(i, temp);
        }

        for (String i : b.getTable().keySet()) {
            if (!c.containsKey(i)) {
                HashMap<String, HashSet<String>> temp = new HashMap<>();
                
                for (String j  : alph) {
                    temp.put(j, new HashSet<>());
                }
                
                c.put(i, temp);
            }
        }
        
        for (String i : a.getTable().keySet()) {
            for (String j : a.getTable().get(i).keySet()) {
                HashSet<String> temp = c.get(i).get(j);
                temp.addAll(a.getTable().get(i).get(j));
                
                c.get(i).put(j, temp);
            }
        }
        
        for (String i : b.getTable().keySet()) {
            for (String j : b.getTable().get(i).keySet()) {
                HashSet<String> temp = c.get(i).get(j);
                temp.addAll(b.getTable().get(i).get(j));
                
                c.get(i).put(j, temp);
            }
        }
        
        for (String i : b.getStart()) {
            for (String k : alph) {
                if (!c.get(i).get(k).isEmpty()) {
                    for (String j : a.getFinish()) {
                        HashSet<String> temp = c.get(j).get(k);
                        temp.addAll(c.get(i).get(k));
                        
                        c.get(j).put(k, temp);
                    }
                }
            }
        }
        
        return c;
    }
    
    private static HashSet<String> addFinish(HashSet<String> af, HashSet<String> bs, HashSet<String> bf) {
        HashSet<String> c = new HashSet<>();
        
        for (String i : bs) {
            if (bf.contains(i)) {
                c = af;
                break;
            }
        }
        
        return c;
    }
    
    private static HashMap<String, HashMap<String, HashSet<String>>> makeTableForIteration(Automaton a) {
        HashMap<String, HashMap<String, HashSet<String>>> c = a.getTable();
        
        for (String i : a.getStart()) {
            for (String j : a.getAlph()) {
                if (a.getTable().get(i).get(j).size() > 0) {
                    for (String k : a.getFinish()) {
                        HashSet<String> temp = c.get(i).get(j);
                        temp.addAll(a.getTable().get(i).get(j));
                        
                        c.get(k).put(j, temp);
                    }
                }
            }
        }
        
        HashMap<String, HashSet<String>> l = new HashMap<>();
        
        for (String i : a.getAlph()) {
            l.put(i, new HashSet<>());
        }
        
        c.put(Integer.toString(Automaton.numBranch), l);
        
        return c;
    }
}



















