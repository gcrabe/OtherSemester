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
public class Order {

    private int idUser;
    private ArrayList<Integer> idItem = new ArrayList<>();

    public Order() {
    }

    public Order(int idUser, ArrayList<Integer> idItem) {
        this.idUser = idUser;
        this.idItem = idItem;
    }

    public void setIdUser(int idUser) {
        this.idUser = idUser;
    }

    public void setIdItem(ArrayList<Integer> idItem) {
        this.idItem = idItem;
    }

    public int getIdUser() {
        return idUser;
    }

    public ArrayList<Integer> getIdItem() {
        return idItem;
    }
}
