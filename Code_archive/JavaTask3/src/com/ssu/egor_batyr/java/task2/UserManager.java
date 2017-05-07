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
public class UserManager {

    private ArrayList<User> users;

    public UserManager() {
        users = new ArrayList<>();
    }

    public void add(User user) {
        users.add(user);
    }
    
    public ArrayList<User> getAll() {
        return users;
    }

    public User getUserById(int idx) {
        for (User curUser : users) {
            if (curUser.getId() == idx) {
                return curUser;
            }
        }

        return null;
    }
}
