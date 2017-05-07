/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ssu.egor_batyr.java.task2;

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
        String[] itemNames = new String[CNT_ITEMS];

        itemNames[0] = "Рулет с изюмом";
        itemNames[1] = "Пирог с повидлом";
        itemNames[2] = "Пирог с яблоками";
        itemNames[3] = "Салат Изюминка";
        itemNames[4] = "Салат Лукошко";
        itemNames[5] = "Салат Капустный с помидором";
        itemNames[6] = "Суп харчо с говядиной";
        itemNames[7] = "Суп куриный с грибами";
        itemNames[8] = "Суп болгарский вегетарианский";
        itemNames[9] = "Рыбное филе с помидоркой";
        itemNames[10] = "Печень по королевски";
        itemNames[11] = "Свинина запеченная \"По-гусарски\"";
        itemNames[12] = "Греча с маслом";
        itemNames[13] = "Макароны отварные";
        itemNames[14] = "Рис отварной с маслом";

        int[] itemWeight = new int[CNT_ITEMS];

        itemWeight[0] = 75;
        itemWeight[1] = 60;
        itemWeight[2] = 60;
        itemWeight[3] = 100;
        itemWeight[4] = 100;
        itemWeight[5] = 100;
        itemWeight[6] = 250;
        itemWeight[7] = 250;
        itemWeight[8] = 250;
        itemWeight[9] = 80;
        itemWeight[10] = 150;
        itemWeight[11] = 80;
        itemWeight[12] = 170;
        itemWeight[13] = 170;
        itemWeight[14] = 170;

        double[] itemCost = new double[CNT_ITEMS];

        itemCost[0] = 15;
        itemCost[1] = 13;
        itemCost[2] = 13;
        itemCost[3] = 35;
        itemCost[4] = 40;
        itemCost[5] = 19;
        itemCost[6] = 31;
        itemCost[7] = 34;
        itemCost[8] = 21;
        itemCost[9] = 54;
        itemCost[10] = 54;
        itemCost[11] = 68;
        itemCost[12] = 17;
        itemCost[13] = 15;
        itemCost[14] = 16;

        ArrayList<Item> menuInput = new ArrayList<>();

        for (int i = 0; i < CNT_ITEMS; i++) {
            menuInput.add(new Item(i, itemNames[i], itemWeight[i], itemCost[i]));
        }

        return menuInput;
    }

    public ArrayList<User> readUsers() {
        ArrayList<User> userInput = new ArrayList<>();

        String[] userNames = new String[CNT_USERS];

        userNames[0] = "Пупкин А.";
        userNames[1] = "Кривенко С.";
        userNames[2] = "Гайченов П.";
        userNames[3] = "Сухожилов Л.";

        for (int i = 0; i < CNT_USERS; i++) {
            userInput.add(new User(i, userNames[i]));
        }

        return userInput;
    }

    public ArrayList<ArrayList<String>> readOrders() {

        ArrayList<String>[] orders = new ArrayList[CNT_USERS];

        orders[0] = new ArrayList<String>() {
            {
                add("Салат Изюминка");
                add("Печень по королевски");
                add("Рис отварной с маслом");
                add("Рулет с изюмом");
            }
        };
        orders[1] = new ArrayList<String>() {
            {
                add("Салат Лукошко");
                add("Суп куриный с грибами");
                add("Свинина запеченная \"По-гусарски\"");
                add("Макароны отварные");
                add("Пирог с яблоками");
            }
        };
        orders[2] = new ArrayList<String>() {
            {
                add("Суп болгарский вегетарианский");
                add("Рыбное филе с помидоркой");
                add("Рулет с изюмом");
                add("Пирог с повидлом");
            }
        };
        orders[3] = new ArrayList<String>() {
            {
                add("Салат Изюминка");
                add("Суп куриный с грибами");
                add("Печень по королевски");
                add("Макароны отварные");
                add("Пирог с повидлом");
            }
        };

        ArrayList<ArrayList<String>> orderInput = new ArrayList<>();

        for (int i = 0; i < CNT_USERS; i++) {
            orderInput.add(orders[i]);
        }

        return orderInput;
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
