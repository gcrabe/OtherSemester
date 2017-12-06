/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gc.gameproject.model;

import com.gc.gameproject.ConstantImmutable;

import java.util.ArrayList;
import javafx.scene.image.Image;

/**
 *
 * @author gc
 */
public class Snake implements Runnable, ConstantImmutable {
    
    private ArrayList<SnakeElement> elements;
    private int direction;
    private boolean isRunning;

    public Snake() {
        direction = STATE_DOWN;
        isRunning = true;
        elements = new ArrayList<SnakeElement>() {
            {
                add(new SnakeElement(0, 2, new Image("images/head.png")));
                add(new SnakeElement(0, 1, new Image("images/body.png")));
                add(new SnakeElement(0, 0, new Image("images/tail.png")));
            }
        };
    }

    public ArrayList<SnakeElement> getElements() {
        return elements;
    }

    public void setElements(ArrayList<SnakeElement> parts) {
        this.elements = parts;
    }

    public int getDirection() {
        return direction;
    }

    public void setDirection(int direction) {
        this.direction = direction;
    }

    public boolean isRunning() {
        return isRunning;
    }

    public void setRunning(boolean running) {
        isRunning = running;
    }

    public void turnLeft() {
        direction += 1;

        if (direction > STATE_RIGHT) {
            direction = STATE_UP;
        }
    }

    public void turnRight() {
        direction -= 1;

        if (direction < STATE_UP) {
            direction = STATE_RIGHT;
        }
    }

    public void increase() {
        SnakeElement end = elements.get(elements.size() - 1);
        end.setImage(new Image("images/tail.png"));
        elements.add(elements.size() - 1, new SnakeElement(end.getX(), end.getY(), new Image("images/body.png")));
    }

    public void move() {
        SnakeElement head = elements.get(0);

        for (int i = elements.size() - 1; i > 0; i--) {
            SnakeElement before = elements.get(i - 1);
            SnakeElement part = elements.get(i);

            part.setX(before.getX());
            part.setY(before.getY());
        }

        switch (direction) {
            case STATE_UP: {
                head.setY(head.getY() - 1);
                break;
            }
            case STATE_LEFT: {
                head.setX(head.getX() - 1);
                break;
            }
            case STATE_DOWN: {
                head.setY(head.getY() + 1);
                break;
            }
            case STATE_RIGHT: {
                head.setX(head.getX() + 1);
                break;
            }
        }

        if (head.getX() < 0) {
            head.setX(GAME_SPACE_WIDTH - 1);
        }
        if (head.getX() > GAME_SPACE_WIDTH - 1) {
            head.setX(0);
        }
        if (head.getY() < 0) {
            head.setY(GAME_SPACE_HEIGHT - 1);
        }
        if (head.getY() > GAME_SPACE_HEIGHT - 1) {
            head.setY(0);
        }
    }

    public boolean isBitten() {
        SnakeElement head = elements.get(0);

        for (int i = 1; i < elements.size(); i++) {
            SnakeElement part = elements.get(i);

            if (part.getX() == head.getX() && part.getY() == head.getY()) {
                return true;
            }
        }

        return false;
    }

    @Override
    public void run() {
        if (isRunning) {
            move();
        }
    }
}
