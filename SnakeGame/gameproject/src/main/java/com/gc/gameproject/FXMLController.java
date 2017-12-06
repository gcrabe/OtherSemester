/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gc.gameproject;

import com.gc.gameproject.model.Frog;
import com.gc.gameproject.model.GameSpace;
import com.gc.gameproject.model.Snake;
import com.gc.gameproject.model.SnakeElement;

import javafx.animation.AnimationTimer;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;

/**
 *
 * @author gc
 */
public class FXMLController implements ConstantImmutable {

    private GraphicsContext graphicsContext;
    private Canvas canvas;
    private AnimationTimer timer;
    public static float gameSpeed; // Attention! don't use it ever

    private Image gameBackground;

    private GameSpace game;
    private int score;
    private Snake snake;

    @FXML
    private AnchorPane gamePart;
    @FXML
    private AnchorPane controlPart;
    @FXML
    private Button startButton;
    @FXML
    private Button pauseButton;
    @FXML
    private Label scoreLabel;

    public Label getScoreLabel() {
        return scoreLabel;
    }

    public AnchorPane getGamePart() {
        return gamePart;
    }

    public AnchorPane getControlPart() {
        return controlPart;
    }

    public Button getStartButton() {
        return startButton;
    }

    public Button getPauseButton() {
        return pauseButton;
    }

    @FXML
    protected void startButtonClicked() {
        if (startButton.getText().equals(TITLE_START)) {
            game = new GameSpace();
            snake = game.getSnake();
            game.placeFrog();
            score = game.getScore();
            timer.start();
            startButton.setText(TITLE_STOP);
            pauseButton.setDisable(false);
        } else {
            game.setGameOver(true);
            timer.stop();
            initializeStartScreen();
            startButton.setText(TITLE_START);
            pauseButton.setDisable(true);
            pauseButton.setText(TITLE_PAUSE);
        }
    }

    @FXML
    protected void pauseButtonClicked() {
        if (pauseButton.getText().equals(TITLE_PAUSE)) {
            snake.setRunning(false);
            game.setRunning(false);
            pauseButton.setText(TITLE_CONTINUE);
        } else {
            snake.setRunning(true);
            game.setRunning(true);
            pauseButton.setText(TITLE_PAUSE);
        }
    }

    @FXML
    public void initialize() {
        pauseButton.setDisable(true);
        canvas = new Canvas(GAME_SCREEN_SIZE, GAME_SCREEN_SIZE);
        graphicsContext = canvas.getGraphicsContext2D();
        gamePart.getChildren().add(canvas);
        gameBackground = new Image("images/gameBackground.png");
        initializeStartScreen();

        canvas.setOnKeyPressed(new EventHandler<KeyEvent>() {
            @Override
            public void handle(KeyEvent event) {
                keyPressed(event.getCode().toString());
            }
        });

        canvas.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                mouseClicked(event.getButton().toString());
            }
        });

        timer = new AnimationTimer() {
            public void handle(long currentNanoTime) {
                graphicsContext.clearRect(0, 0, GAME_SCREEN_SIZE, GAME_SCREEN_SIZE);
                graphicsContext.drawImage(gameBackground, 0, 0, GAME_SCREEN_SIZE, GAME_SCREEN_SIZE);
                renderSnake();
                renderFrog(game.getFrog());
                updateScoreLabel();
                game.update(gameSpeed);

                if (game.isGameOver()) {
                    timer.stop();
                    initializeStartScreen();
                    startButton.setText(TITLE_START);
                    pauseButton.setText(TITLE_PAUSE);
                    pauseButton.setDisable(true);
                }
            }
        };
    }

    public void renderSnake() {
        for (SnakeElement snakePart : snake.getElements()) {
            graphicsContext.drawImage(snakePart.getImage(),
                    snakePart.getX() * GAME_BOARD_CELL_SIZE, snakePart.getY() * GAME_BOARD_CELL_SIZE,
                    GAME_BOARD_CELL_SIZE, GAME_BOARD_CELL_SIZE);
        }
    }

    public void renderFrog(Frog frog) {
        graphicsContext.drawImage(frog.getImage(),
                frog.getX() * GAME_BOARD_CELL_SIZE, frog.getY() * GAME_BOARD_CELL_SIZE,
                GAME_BOARD_CELL_SIZE, GAME_BOARD_CELL_SIZE);
    }

    public void keyPressed(String code) {
        if (code.equals("LEFT")) {
            snake.turnLeft();
            System.out.println(code);
        }

        if (code.equals("RIGHT")) {
            snake.turnRight();
            System.out.println(code);
        }
    }

    public void mouseClicked(String button) {
        if (button.equals("PRIMARY")) {
            snake.turnLeft();
        }

        if (button.equals("SECONDARY")) {
            snake.turnRight();
        }
    }

    public void initializeStartScreen() {
        graphicsContext.drawImage(new Image("images/gameBackground.png"), 0, 0, GAME_SCREEN_SIZE, GAME_SCREEN_SIZE);
    }

    public void updateScoreLabel() {
        int newScore = game.getScore();
        
        if (newScore > score) {
            score = newScore;
        }
        
        scoreLabel.setText("Score: " + Integer.toString(score));
    }
}
