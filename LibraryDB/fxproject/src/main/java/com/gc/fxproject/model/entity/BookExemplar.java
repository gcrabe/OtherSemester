package com.gc.fxproject.model.entity;

public class BookExemplar {
    
    private int id;
    private BookEdition bookEdition;
    private boolean isFree;
    
    public BookExemplar(int id, BookEdition bookEdition, boolean isFree) {
        this.id = id;
        this.bookEdition = bookEdition;
        this.isFree = isFree;
    }
    
    public int getId() {
        return id;
    }
    
    public BookEdition getBookEdition() {
        return bookEdition;
    }
    
    public void setBookEdition(BookEdition bookEdition) {
        this.bookEdition = bookEdition;
    }
    
    public boolean getIsFree() {
        return isFree;
    }
    
    public void setIsFree(boolean isFree) {
        this.isFree = isFree;
    }
}
