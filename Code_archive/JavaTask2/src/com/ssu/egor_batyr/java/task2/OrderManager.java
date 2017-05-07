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
public class OrderManager {

    private ArrayList<Order> orders;

    public OrderManager() {
        orders = new ArrayList<>();
    }

    public void add(Order order) {
        orders.add(order);
    }

    public Order getOrderById(int idOrder) {
        for (Order curOrder : orders) {
            if (curOrder.getIdUser() == idOrder) {
                return curOrder;
            }
        }

        return null;
    }

    public ArrayList<Order> getAll() {
        return orders;
    }

    public int countOfItem(int idItem) {
        int res = 0;

        for (Order order : orders) {
            ArrayList<Integer> idItems = order.getIdItem();

            for (int curIdItem : idItems) {
                if (curIdItem == idItem) {
                    res++;
                }
            }
        }

        return res;
    }
}
