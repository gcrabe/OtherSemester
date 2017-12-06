/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gc.gameproject;

/**
 *
 * @author gc
 */
public interface ConstantImmutable {
    // This is ANTIpattern
    // I know it
    
    public static final int GAME_SPACE_WIDTH = 16;
    public static final int GAME_SPACE_HEIGHT = 16;
    
    public static final int GAME_SCORE_INCREMENT = 10;
    
    public static final float GAME_TICK_INITIAL = 0.5f;
    
    public static final int STATE_UP = 0;
    public static final int STATE_LEFT = 1;
    public static final int STATE_DOWN = 2;
    public static final int STATE_RIGHT = 3;
    
    public static final String TITLE_START = "Start";
    public static final String TITLE_STOP = "Stop";
    public static final String TITLE_PAUSE = "Pause";
    public static final String TITLE_CONTINUE = "Continue";
    
    public final int GAME_SCREEN_SIZE = 512;
    public final int GAME_BOARD_CELL_SIZE = 32;
    
    public final float GAME_SPEED_SLOW = 0.02f;
    public final float GAME_SPEED_MEDIUM = 0.03f;
    public final float GAME_SPEED_FAST = 0.04f;
}
