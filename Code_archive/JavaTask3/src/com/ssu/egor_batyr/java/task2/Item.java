/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ssu.egor_batyr.java.task2;

/**
 *
 * @author gc
 */
public class Item {

    private static Item createItem(int id, String line) {
            String[] words = line.split(" ");
            String tempName = "";
            int pos;

            for (pos = 0; !Character.isDigit(words[pos].charAt(0)); pos++) {
                tempName += words[pos] + " ";
            }

            String name1 = tempName.substring(0, tempName.length() - 1);
            int weight1 = Integer.parseInt(words[pos]);
            double cost1 = Double.parseDouble(words[pos + 2]);
            
            return new Item(id, name1, weight1, cost1);
    }

    private int id;
    private String name;
    private int weight;
    private double cost;

    public Item() {
    }
    
    public Item(int id, String line) throws InvalidInputFormatException {
        try {
            Item.createItem(id, line);
        } catch (Exception e) {
            throw new InvalidInputFormatException();
        }
    }

    public Item(int id, String name, int weight, double cost) {
        this.id = id;
        this.name = name;
        this.weight = weight;
        this.cost = cost;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public void setCost(double cost) {
        this.cost = cost;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public int getWeight() {
        return weight;
    }

    public double getCost() {
        return cost;
    }
}
