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
public class Solution {

    private ItemService itemService = new ItemService(this);
    private UserService userService = new UserService(this);
    private OrderService orderService = new OrderService(this);

    private Controller controller = new Controller(this);

    public ItemService getItemService() {
        return itemService;
    }

    public UserService getUserService() {
        return userService;
    }

    public OrderService getOrderService() {
        return orderService;
    }

    public void startApplication() {
        ArrayList<Item> menuInput = controller.readItems();
        
        for (Item curItem : menuInput) {
            itemService.addItem(curItem);
        }
        
        ArrayList<Order> orderInput = controller.readOrders();
        
        for (Order curOrder : orderInput) {
            orderService.addOrder(curOrder);
        }
        
        controller.createCompanyReport(System.out);
        controller.createUserReport(System.out);
    }
}
