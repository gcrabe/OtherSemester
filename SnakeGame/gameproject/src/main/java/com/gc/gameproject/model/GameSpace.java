/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gc.gameproject.model;

import com.gc.gameproject.ConstantImmutable;

import java.util.Random;

/**
 *
 * @author gc
 */
public class GameSpace implements ConstantImmutable {
    
    private Snake snake;
    private Frog frog;
    private boolean gameOver;
    private boolean isRunning;
    private int score;
    private boolean[][] used;
    private final Random random = new Random();
    private float tickTime;
    private static float tick;

    public GameSpace() {
        this.snake = new Snake();
        
        Thread snakeThread = new Thread(snake);
        snakeThread.setDaemon(true);
        snakeThread.start();
        
        this.gameOver = false;
        this.isRunning = true;
        this.score = 0;
        this.used = new boolean[GAME_SPACE_WIDTH][GAME_SPACE_HEIGHT];
        this.tickTime = 0;
        GameSpace.tick = GAME_TICK_INITIAL;

        placeFrog();
    }

    public static float getTick() {
        return tick;
    }

    public static void setTick(float tick) {
        GameSpace.tick = tick;
    }

    public float getTickTime() {
        return tickTime;
    }

    public void setTickTime(float tickTime) {
        this.tickTime = tickTime;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public Frog getFrog() {
        return frog;
    }

    public void setFrog(Frog frog) {
        this.frog = frog;
    }

    public Snake getSnake() {
        return snake;
    }

    public void setSnake(Snake snake) {
        this.snake = snake;
    }

    public boolean isGameOver() {
        return gameOver;
    }

    public void setGameOver(boolean gameOver) {
        this.gameOver = gameOver;
    }

    public boolean[][] getFields() {
        return used;
    }

    public void setFields(boolean[][] fields) {
        this.used = fields;
    }

    public boolean isRunning() {
        return isRunning;
    }

    public void setRunning(boolean running) {
        this.isRunning = running;
    }

    public void placeFrog() {
        for (int x = 0; x < GAME_SPACE_WIDTH; x++) {
            for (int y = 0; y < GAME_SPACE_HEIGHT; y++) {
                used[x][y] = false;
            }
        }

        for (int i = 0; i < snake.getElements().size(); i++) {
            SnakeElement part = snake.getElements().get(i);
            used[part.getX()][part.getY()] = true;
        }

        int frogX = random.nextInt(GAME_SPACE_WIDTH);
        int frogY = random.nextInt(GAME_SPACE_HEIGHT);

        while (true) {
            if (used[frogX][frogY] == false) {
                break;
            }
            
            frogX++;
            
            if (frogX >= GAME_SPACE_WIDTH) {
                frogX = 0;
                frogY++;
                
                if (frogY >= GAME_SPACE_HEIGHT) {
                    frogY = 0;
                }
            }
        }

        frog = new Frog(frogX, frogY);
    }

    public void update(float deltaTime) {
        if (gameOver) {
            return;
        }

        if (isRunning) {
            tickTime += deltaTime;

            while (tickTime > tick) {
                tickTime -= tick;
                snake.move();
                
                if (snake.isBitten()) {
                    gameOver = true;
                    return;
                }

                SnakeElement head = snake.getElements().get(0);
                
                if (head.getX() == frog.getX() && head.getY() == frog.getY()) {
                    score += GAME_SCORE_INCREMENT;
                    snake.increase();

                    if (snake.getElements().size() == GAME_SPACE_HEIGHT * GAME_SPACE_WIDTH) {
                        gameOver = true;
                        return;
                    } else {
                        placeFrog();
                    }
                }
            }
        }
    }
    
}
