/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gc.gameproject;

import java.util.Scanner;
import javafx.application.Application;
import static javafx.application.Application.launch;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 *
 * @author gc
 */
public class MainApp extends Application implements ConstantImmutable {

    @Override
    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("/fxml/Scene.fxml"));
        
        System.out.println("Choose the game speed:");
        System.out.println("1. Slow\n2.Medium\n3.Fast\n");
        System.out.print("Enter the number (1 - 3): ");
        
        int modeValue = (new Scanner(System.in)).nextInt();
        
        switch (modeValue) {
            case 1: {
                FXMLController.gameSpeed = GAME_SPEED_SLOW;
                break;
            }
            case 2: {
                FXMLController.gameSpeed = GAME_SPEED_MEDIUM;
                break;
            }
            case 3: {
                FXMLController.gameSpeed = GAME_SPEED_FAST;
                break;
            }
        }
        
        Scene scene = new Scene(root);
        scene.getStylesheets().add("/styles/Styles.css");
        
        stage.setTitle("JavaFX and Maven");
        stage.resizableProperty().set(false);
        stage.setScene(scene);
        stage.show();
    }

    /**
     * The main() method is ignored in correctly deployed JavaFX application.
     * main() serves only as fallback in case the application can not be
     * launched through deployment artifacts, e.g., in IDEs with limited FX
     * support. NetBeans ignores main().
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }

}
