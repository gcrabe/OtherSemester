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
public class OrderService {

    private OrderManager manager;
    final private Solution solution;

    public OrderService(Solution solution) {
        manager = new OrderManager();
        this.solution = solution;
    }
    
    public void addOrder(Order order) {
        manager.add(order);
    }
    
    public void addOrder(int idUser, ArrayList<Integer> idItems) {
        Order order = new Order(idUser, idItems);
        manager.add(order);
    }
    
    public Order getOrderById(int idUser) {
        return manager.getOrderById(idUser);
    }

    public double totalCost(int idOrder) {
        Order order = getOrderById(idOrder);
        double res = 0;

        ArrayList<Integer> idItems = order.getIdItem();

        for (int curIdItem : idItems) {
            Item item = solution.getItemService().getItemById(curIdItem);
            res += item.getCost();
        }

        return res;
    }

    public ArrayList<Order> getAll() {
        return manager.getAll();
    }

    public int countOfItem(int idItem) {
        return manager.countOfItem(idItem);
    }
}
