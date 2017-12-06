/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gc.gameproject.model;

import javafx.scene.image.Image;

/**
 *
 * @author gc
 */
public class Frog extends GameObject {
 
    public Frog(int x, int y) {
        super(x, y);
        this.image = new Image("images/frog.png");
    }
}
