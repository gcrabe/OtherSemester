/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ssu.egor_batyr.java.task2;

/**
 *
 * @author gc
 */
public class InvalidInputFormatException extends Exception {
    
    public void ShowMessage() {
        System.err.println("Некорректный формат входного файла");
    }
}
