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
public class ItemManager {

    private ArrayList<Item> items;

    public ItemManager() {
        items = new ArrayList<>();
    }

    public void add(Item item) {
        items.add(item);
    }

    public int getIdByName(String itemName) {
        int idx = -1;

        for (Item curItem : items) {
            int hashItemName = itemName.hashCode();
            int hashCurItem = curItem.hashCode();
            if (itemName.equals(curItem.getName())) {
                idx = curItem.getId();
                break;
            }
        }

        return idx;
    }

    public Item getItemById(int idx) {
        for (Item curItem : items) {
            if (curItem.getId() == idx) {
                return curItem;
            }
        }

        return null;
    }

    public ArrayList<Item> getAll() {
        return items;
    }
}
