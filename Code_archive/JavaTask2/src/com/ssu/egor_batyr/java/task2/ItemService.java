/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ssu.egor_batyr.java.task2;

import java.util.ArrayList;

/**
 *
 * @author gc
 */
public class ItemService {

    private ItemManager manager;
    final private Solution solution;

    public ItemService(Solution solution) {
        manager = new ItemManager();
        this.solution = solution;
    }

    public void addItem(Item item) {
        manager.add(item);
    }

    public void addItem(int id, String name, int weight, double cost) {
        Item item = new Item(id, name, weight, cost);
        manager.add(item);
    }

    public int getItemIdByName(String itemName) {
        return manager.getIdByName(itemName);
    }

    public Item getItemById(int idx) {
        return manager.getItemById(idx);
    }

    public ArrayList<Item> getAll() {
        return manager.getAll();
    }
}
