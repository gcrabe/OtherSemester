/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ssu.egor_batyr.java.task2;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.ArrayList;

/**
 *
 * @author gc
 */
public class Controller {

    final static int CNT_ITEMS = 15;
    final static int CNT_USERS = 4;

    final private Solution solution;

    public Controller(Solution solution) {
        this.solution = solution;
    }

    public ArrayList<Item> readItems() {
        BufferedReader reader = null;
        ArrayList<String> lines = new ArrayList<>();

        try {
            reader = new BufferedReader(new InputStreamReader(
                    new FileInputStream("C:\\THE_CODE\\JavaTask3\\src\\com\\ssu\\egor_batyr\\java\\task2\\inputmenufile.txt")));

            String tempLine;

            while ((tempLine = reader.readLine()) != null) {
                lines.add(tempLine);
            }
        } catch (IOException openException) {
            System.out.println("input menu open error");
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException closeException) {
                    System.out.println("input menu close error");
                }
            }
        }

        ArrayList<Item> menuInput = new ArrayList<>();

        for (int i = 0; i < lines.size(); i++) {
            try {
                Item item = new Item(i, lines.get(i));
                menuInput.add(item);
            } catch (InvalidInputFormatException e) {
                e.ShowMessage();
            }
        }

        return menuInput;
    }

    public ArrayList<Order> readOrders() {

        ArrayList<String> orderLines = new ArrayList<>();
        BufferedReader reader = null;

        try {
            reader = new BufferedReader(new InputStreamReader(
                    new FileInputStream("C:\\THE_CODE\\JavaTask3\\src\\com\\ssu\\egor_batyr\\java\\task2\\inputorderfile.txt")));

            String orderLine;

            while ((orderLine = reader.readLine()) != null) {
                orderLines.add(orderLine);
            }
        } catch (IOException e) {
            System.out.println("input orders open error");
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    System.out.println("input orders close error");
                }
            }
        }

        ArrayList<Order> ordersInput = new ArrayList<>();

        ArrayList<User> users = new ArrayList<>();
        ArrayList<ArrayList<String>> orderItems = new ArrayList<>();

        for (int i = 0; i < orderLines.size(); i++) {
            String[] words = orderLines.get(i).split(" ");

            String userName = words[0] + " " + words[1];
            users.add(new User(i, userName));

            ArrayList<String> itemNames = new ArrayList<>();
            String tempItemName = "";

            for (int pos = 2; pos < words.length; pos++) {
                tempItemName += words[pos];

                if (words[pos].endsWith(",")) {
                    String itemName = tempItemName.substring(0, tempItemName.length() - 1);
                    itemNames.add(itemName);
                    tempItemName = "";
                } else {
                    tempItemName += " ";
                }
            }

            if (!tempItemName.isEmpty()) {
                itemNames.add(tempItemName.substring(0, tempItemName.length() - 1));
            }

            orderItems.add(itemNames);
        }

        ArrayList<Integer> userIds = new ArrayList<>();

        for (User curUser : users) {
            solution.getUserService().addUser(curUser);
            userIds.add(curUser.getId());
        }

        int cntOrders = orderItems.size();

        ArrayList<Integer>[] itemIds = new ArrayList[cntOrders];

        for (int i = 0; i < cntOrders; i++) {
            itemIds[i] = new ArrayList<>();
            ArrayList<String> curOrder = orderItems.get(i);

            for (String curItemName : curOrder) {
                int tempItemId = solution.getItemService().getItemIdByName(curItemName);
                itemIds[i].add(tempItemId);
            }
        }

        for (int i = 0; i < cntOrders; i++) {
            Order order = new Order(userIds.get(i), itemIds[i]);
            ordersInput.add(order);
        }

        return ordersInput;
    }

    public void createCompanyReport(PrintStream outstream) {
        outstream.println("First report:");

        ArrayList<Item> items = solution.getItemService().getAll();

        double totalOrderCost = 0;

        for (Item curItem : items) {
            int curCount = solution.getOrderService().countOfItem(curItem.getId());

            if (curCount == 0) {
                continue;
            }

            outstream.print(curItem.getName() + " " + curCount + " ");

            double curCost = curItem.getCost() * curCount;
            outstream.println(curCost);

            totalOrderCost += curCost;
        }

        outstream.println(totalOrderCost + "\n");
    }

    public void createUserReport(PrintStream outstream) {
        outstream.println("Second report:");

        ArrayList<Order> orders = solution.getOrderService().getAll();

        for (Order curOrder : orders) {
            User user = solution.getUserService().getUserById(curOrder.getIdUser());
            outstream.print(user.getName() + " ");

            ArrayList<Integer> idItems = curOrder.getIdItem();

            for (int curIdItem : idItems) {
                Item item = solution.getItemService().getItemById(curIdItem);
                outstream.print(item.getName() + " ");
            }

            double totalPersonCost = solution.getOrderService().totalCost(user.getId());

            outstream.println(totalPersonCost);
        }

        outstream.println();
    }
}
