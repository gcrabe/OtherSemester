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
public abstract class GameObject {
    
    protected int x;
    protected int y;
    protected Image image;
    
    public GameObject(int x, int y) {
        this.x = x;
        this.y = y;
    }
    
    public GameObject(int x, int y, Image image) {
        this(x, y);
        this.image = image;
    }
    
    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }
    
    public Image getImage() {
        return image;
    }

    public void setImage(Image image) {
        this.image = image;
    }
}
