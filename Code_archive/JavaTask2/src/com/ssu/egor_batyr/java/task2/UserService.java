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
public class UserService {

    private UserManager manager;
    final private Solution solution;

    public UserService(Solution solution) {
        manager = new UserManager();
        this.solution = solution;
    }

    public void addUser(User user) {
        manager.add(user);
    }

    public void addUser(int id, String name) {
        User user = new User(id, name);
        manager.add(user);
    }
    
    public ArrayList<User> getAll() {
        return manager.getAll();
    }

    public User getUserById(int idx) {
        return manager.getUserById(idx);
    }
}
